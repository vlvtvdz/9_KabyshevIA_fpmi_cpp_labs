#include "time_utility.h"
#include "train.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void SwapTrains(Train& first, Train& second) {
    Train temp = first;
    first = second;
    second = temp;
}

std::string Trim(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

bool EqualsIgnoreCase(const std::string& lhs, const std::string& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        char left = static_cast<char>(std::toupper(static_cast<unsigned char>(lhs[i])));
        char right = static_cast<char>(std::toupper(static_cast<unsigned char>(rhs[i])));
        if (left != right) {
            return false;
        }
    }
    return true;
}

bool ContainsIgnoreCase(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) {
        return true;
    }
    const size_t n = text.size();
    const size_t m = pattern.size();
    if (m > n) {
        return false;
    }
    for (size_t i = 0; i + m <= n; ++i) {
        bool match = true;
        for (size_t j = 0; j < m; ++j) {
            char left = static_cast<char>(std::toupper(static_cast<unsigned char>(text[i + j])));
            char right =
                static_cast<char>(std::toupper(static_cast<unsigned char>(pattern[j])));
            if (left != right) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> Split(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::string current;
    for (char ch : line) {
        if (ch == delimiter) {
            tokens.push_back(Trim(current));
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    tokens.push_back(Trim(current));
    return tokens;
}

std::time_t ParseClockTime(const std::string& value) {
    const auto delimiter = value.find(':');
    if (delimiter == std::string::npos) {
        throw std::invalid_argument("Invalid time format: " + value);
    }

    size_t hours = std::stoul(value.substr(0, delimiter));
    size_t minutes = std::stoul(value.substr(delimiter + 1));

    return time_utility::SetTime(hours, minutes);
}

bool ParseTrainRecord(const std::string& line, Train& train) {
    if (line.empty() || line[0] == '#') {
        return false;
    }
    std::vector<std::string> tokens = Split(line, ';');
    if (tokens.size() != 5) {
        std::cerr << "Invalid record format: " << line << '\n';
        return false;
    }
    try {
        TrainId id = static_cast<TrainId>(std::stoul(tokens[0]));
        TrainType type = Train::TrainTypeFromString(tokens[1]);
        std::string destination = tokens[2];
        std::time_t dispatch_time = ParseClockTime(tokens[3]);
        std::time_t travelling_time = ParseClockTime(tokens[4]);
        train = Train(id, type, destination, dispatch_time, travelling_time);
        return true;
    } catch (const std::exception& err) {
        std::cerr << "Failed to parse record \"" << line << "\": " << err.what() << '\n';
        return false;
    }
}

std::vector<Train> LoadTrains(const std::string& file_path) {
    std::ifstream input(file_path);
    if (!input) {
        throw std::runtime_error("Unable to open file: " + file_path);
    }
    std::vector<Train> trains;
    std::string line;
    while (std::getline(input, line)) {
        line = Trim(line);
        Train train;
        if (ParseTrainRecord(line, train)) {
            trains.push_back(train);
        }
    }
    return trains;
}

void PrintTrainList(const std::vector<Train>& trains, const std::string& header) {
    std::cout << "\n" << header << '\n';
    if (trains.empty()) {
        std::cout << "  (no trains)\n";
        return;
    }
    for (const Train& train : trains) {
        train.Print(std::cout);
    }
}

std::vector<Train> FilterByTimeRange(const std::vector<Train>& trains,
                                     std::time_t from, std::time_t to) {
    if (from > to) {
        std::time_t temp = from;
        from = to;
        to = temp;
    }
    std::vector<Train> filtered;
    for (const Train& train : trains) {
        if (train.GetDispatchTime() >= from && train.GetDispatchTime() <= to) {
            filtered.push_back(train);
        }
    }
    return filtered;
}

std::vector<Train> FilterByDestination(const std::vector<Train>& trains,
                                       const std::string& destination) {
    std::vector<Train> filtered;
    for (const Train& train : trains) {
        if (ContainsIgnoreCase(train.GetDestination(), destination)) {
            filtered.push_back(train);
        }
    }
    return filtered;
}

std::vector<Train> FilterByTypeAndDestination(const std::vector<Train>& trains,
                                              TrainType type,
                                              const std::string& destination) {
    std::vector<Train> filtered;
    for (const Train& train : trains) {
        if (train.GetType() == type &&
            EqualsIgnoreCase(train.GetDestination(), destination)) {
            filtered.push_back(train);
        }
    }
    return filtered;
}

bool FindFastestTrain(const std::vector<Train>& trains,
                      const std::string& destination,
                      Train& result) {
    bool found = false;
    for (const Train& train : trains) {
        if (!ContainsIgnoreCase(train.GetDestination(), destination)) {
            continue;
        }
        if (!found || train.GetTravellingTime() < result.GetTravellingTime()) {
            result = train;
            found = true;
        }
    }
    return found;
}

void SortTrainsByDispatch(std::vector<Train>& trains) {
    for (size_t i = 0; i < trains.size(); ++i) {
        size_t best_index = i;
        for (size_t j = i + 1; j < trains.size(); ++j) {
            if (trains[j] < trains[best_index]) {
                best_index = j;
            }
        }
        if (best_index != i) {
            SwapTrains(trains[i], trains[best_index]);
        }
    }
}

std::string RequestLine(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return Trim(input);
}

std::time_t RequestTime(const std::string& prompt) {
    while (true) {
        const std::string input = RequestLine(prompt);
        try {
            return ParseClockTime(input);
        } catch (const std::exception& err) {
            std::cout << err.what() << '\n';
        }
    }
}

TrainType RequestTrainType(const std::string& prompt) {
    while (true) {
        const std::string input = RequestLine(prompt);
        try {
            return Train::TrainTypeFromString(input);
        } catch (const std::exception& err) {
            std::cout << err.what() << '\n';
        }
    }
}

int main() {
    try {
        const std::string file_path =
            RequestLine("Enter path to the train data file (records with ';'): ");
        if (file_path.empty()) {
            std::cout << "No file provided. Exiting.\n";
            return 0;
        }

        std::vector<Train> trains = LoadTrains(file_path);
        if (trains.empty()) {
            std::cout << "File \"" << file_path << "\" does not contain train records.\n";
            return 0;
        }

        PrintTrainList(trains, "Loaded trains:");

        std::vector<Train> sorted_trains = trains;
        SortTrainsByDispatch(sorted_trains);
        PrintTrainList(sorted_trains, "Trains sorted by dispatch time:");

        std::time_t range_start = RequestTime("Enter start of time range (HH:MM): ");
        std::time_t range_end = RequestTime("Enter end of time range (HH:MM): ");
        std::vector<Train> range_trains =
            FilterByTimeRange(sorted_trains, range_start, range_end);
        PrintTrainList(range_trains, "Trains departing within the specified range:");

        const std::string destination = RequestLine("Enter destination to filter: ");
        PrintTrainList(FilterByDestination(sorted_trains, destination),
                       "Trains heading to \"" + destination + "\":");

        const std::string typed_destination =
            RequestLine("Enter destination for type filter: ");
        TrainType requested_type = RequestTrainType(
            "Enter train type (PASSENGER/FREIGHT/HIGH_SPEED/SUBWAY/SPECIALIZED): ");
        PrintTrainList(
            FilterByTypeAndDestination(sorted_trains, requested_type, typed_destination),
            "Trains of requested type and destination:");

        const std::string fastest_destination =
            RequestLine("Enter destination to find the fastest train: ");
        Train fastest_train;
        if (FindFastestTrain(sorted_trains, fastest_destination, fastest_train)) {
            std::cout << "\nFastest train for \"" << fastest_destination << "\":\n";
            fastest_train.Print(std::cout);
        } else {
            std::cout << "No trains heading to \"" << fastest_destination << "\" were found.\n";
        }

    } catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << '\n';
        return 1;
    }

    return 0;
}
