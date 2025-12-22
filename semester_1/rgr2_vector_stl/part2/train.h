#pragma once

#include <cctype>
#include <ctime>
#include <iomanip>
#include <iosfwd>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "time_utility.h"

enum class TrainType {
    PASSENGER,
    FREIGHT,
    HIGH_SPEED,
    SUBWAY,
    SPECIALIZED
};

class Train {
private:
    size_t id_ = 0;
    TrainType type_ = TrainType::PASSENGER;
    std::string destination_;
    std::time_t dispatch_time_ = time_utility::SetTime(0, 0);
    std::time_t travelling_time_ = time_utility::SetTime(0, 0);

    static std::string Normalize(const std::string& text) {
        std::string result;
        result.reserve(text.size());
        for (char ch : text) {
            if (!std::isspace(static_cast<unsigned char>(ch))) {
                result.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(ch))));
            }
        }
        return result;
    }

    static std::string FormatTime(const std::time_t& time_value) {
        std::tm tm_value = *std::localtime(&time_value);
        std::ostringstream oss;
        oss << std::put_time(&tm_value, "%H:%M");
        return oss.str();
    }

    long long TravellingMinutes() const {
        std::tm tm_value = *std::localtime(&travelling_time_);
        return static_cast<long long>(tm_value.tm_hour) * 60 + tm_value.tm_min;
    }

public:
    Train() = default;

    Train(size_t id, TrainType type, std::string destination,
          std::time_t dispatch_time, std::time_t travelling_time)
        : id_(id),
          type_(type),
          destination_(std::move(destination)),
          dispatch_time_(dispatch_time),
          travelling_time_(travelling_time) {
    }

    size_t GetId() const {
        return id_;
    }

    TrainType GetType() const {
        return type_;
    }

    const std::string& GetDestination() const {
        return destination_;
    }

    std::time_t GetDispatchTime() const {
        return dispatch_time_;
    }

    std::time_t GetTravellingTime() const {
        return travelling_time_;
    }

    std::time_t GetArrivalTime() const {
        return dispatch_time_ + TravellingMinutes() * 60;
    }

    void Print(std::ostream& out) const {
        out << "Train #" << id_ << " [" << TrainTypeToString(type_) << "]\n"
            << "  Destination : " << destination_ << '\n'
            << "  Dispatch    : " << FormatTime(dispatch_time_) << '\n'
            << "  Travelling  : " << FormatTime(travelling_time_) << '\n'
            << "  Arrival ETA : " << FormatTime(GetArrivalTime()) << '\n';
    }

    bool operator<(const Train& other) const {
        return dispatch_time_ < other.dispatch_time_;
    }

    static TrainType TrainTypeFromString(const std::string& value) {
        const std::string normalized = Normalize(value);
        if (normalized == "PASSENGER") {
            return TrainType::PASSENGER;
        }
        if (normalized == "FREIGHT") {
            return TrainType::FREIGHT;
        }
        if (normalized == "HIGH_SPEED" || normalized == "HIGHSPEED") {
            return TrainType::HIGH_SPEED;
        }
        if (normalized == "SUBWAY") {
            return TrainType::SUBWAY;
        }
        if (normalized == "SPECIALIZED") {
            return TrainType::SPECIALIZED;
        }
        throw std::invalid_argument("Unknown train type: " + value);
    }

    static std::string TrainTypeToString(TrainType type) {
        switch (type) {
            case TrainType::PASSENGER:
                return "PASSENGER";
            case TrainType::FREIGHT:
                return "FREIGHT";
            case TrainType::HIGH_SPEED:
                return "HIGH_SPEED";
            case TrainType::SUBWAY:
                return "SUBWAY";
            case TrainType::SPECIALIZED:
                return "SPECIALIZED";
        }
        return "UNKNOWN";
    }
};
