#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Author {
    std::string surname;
    std::string name;
    std::string patronymic;
};

struct Book {
    int udk = 0;
    std::string title;
    int year = 0;
    std::list<Author> authors;
};

typedef std::list<Book> Library;

std::string Trim(const std::string& text) {
    const size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

std::string ToLower(const std::string& text) {
    std::string result = text;
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] =
            static_cast<char>(std::tolower(static_cast<unsigned char>(result[i])));
    }
    return result;
}

int CompareIgnoreCase(const std::string& lhs, const std::string& rhs) {
    std::string l = ToLower(lhs);
    std::string r = ToLower(rhs);
    if (l < r) return -1;
    if (l > r) return 1;
    return 0;
}

bool ContainsIgnoreCase(const std::string& text, const std::string& pattern) {
    std::string lower_text = ToLower(text);
    std::string lower_pattern = ToLower(pattern);
    return lower_text.find(lower_pattern) != std::string::npos;
}

int CompareAuthors(const Author& lhs, const Author& rhs) {
    int surname_cmp = CompareIgnoreCase(lhs.surname, rhs.surname);
    if (surname_cmp != 0) {
        return surname_cmp;
    }
    int name_cmp = CompareIgnoreCase(lhs.name, rhs.name);
    if (name_cmp != 0) {
        return name_cmp;
    }
    return CompareIgnoreCase(lhs.patronymic, rhs.patronymic);
}

void InsertAuthorSorted(std::list<Author>& authors, const Author& author) {
    std::list<Author>::iterator position = authors.begin();
    while (position != authors.end() && CompareAuthors(author, *position) >= 0) {
        ++position;
    }
    authors.insert(position, author);
}

void InsertBookSorted(Library& library, const Book& book) {
    Library::iterator position = library.begin();
    while (position != library.end() &&
           CompareIgnoreCase(book.title, position->title) >= 0) {
        ++position;
    }
    library.insert(position, book);
}

std::vector<std::string> Split(const std::string& text, char separator) {
    std::vector<std::string> parts;
    std::string current;
    for (char ch : text) {
        if (ch == separator) {
            parts.push_back(Trim(current));
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    parts.push_back(Trim(current));
    return parts;
}

Author ParseAuthor(const std::string& value) {
    std::istringstream iss(value);
    Author author;
    if (!(iss >> author.surname >> author.name)) {
        throw std::runtime_error("Author must have at least surname and name: " + value);
    }
    std::getline(iss, author.patronymic);
    author.patronymic = Trim(author.patronymic);
    return author;
}

Book ParseBookLine(const std::string& line) {
    const std::vector<std::string> tokens = Split(line, ';');
    if (tokens.size() != 4) {
        throw std::runtime_error("Book format must contain 4 fields separated by ';': " + line);
    }

    Book book;
    book.udk = std::stoi(tokens[0]);
    book.title = tokens[1];
    book.year = std::stoi(tokens[2]);

    const std::vector<std::string> author_tokens = Split(tokens[3], '|');
    for (const std::string& author_token : author_tokens) {
        if (author_token.empty()) {
            continue;
        }
        InsertAuthorSorted(book.authors, ParseAuthor(author_token));
    }
    return book;
}

Library LoadLibrary(const std::string& file_path) {
    std::ifstream input(file_path);
    if (!input) {
        throw std::runtime_error("Unable to open file: " + file_path);
    }

    Library library;
    std::string line;
    while (std::getline(input, line)) {
        line = Trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        try {
            Book book = ParseBookLine(line);
            InsertBookSorted(library, book);
        } catch (const std::exception& err) {
            std::cerr << "Skipping invalid entry: " << err.what() << '\n';
        }
    }
    return library;
}

std::string ReadLine(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return Trim(input);
}

int ReadInt(const std::string& prompt, int min_value = INT_MIN, int max_value = INT_MAX) {
    while (true) {
        const std::string line = ReadLine(prompt);
        try {
            int value = std::stoi(line);
            if (value < min_value || value > max_value) {
                throw std::out_of_range("value out of range");
            }
            return value;
        } catch (const std::exception&) {
            std::cout << "Please enter a valid integer";
            if (min_value != INT_MIN || max_value != INT_MAX) {
                std::cout << " in [" << min_value << ", " << max_value << "]";
            }
            std::cout << ".\n";
        }
    }
}

void PrintAuthor(const Author& author) {
    std::cout << author.surname << ' ' << author.name;
    if (!author.patronymic.empty()) {
        std::cout << ' ' << author.patronymic;
    }
}

void PrintBook(const Book& book) {
    std::cout << "Title   : " << book.title << '\n'
              << "UDK     : " << book.udk << '\n'
              << "Year    : " << book.year << '\n'
              << "Authors : ";
    if (book.authors.empty()) {
        std::cout << "(none)";
    } else {
        bool first = true;
        for (const Author& author : book.authors) {
            if (!first) std::cout << "; ";
            PrintAuthor(author);
            first = false;
        }
    }
    std::cout << "\n-----------------------------\n";
}

void PrintLibrary(const Library& library) {
    if (library.empty()) {
        std::cout << "Library is empty.\n";
        return;
    }
    for (const Book& book : library) {
        PrintBook(book);
    }
}

Library::iterator FindBook(Library& library, const std::string& title) {
    Library::iterator it = library.begin();
    while (it != library.end()) {
        if (CompareIgnoreCase(it->title, title) == 0) {
            return it;
        }
        ++it;
    }
    return library.end();
}

std::vector<const Book*> SearchByTitle(const Library& library,
                                       const std::string& query) {
    std::vector<const Book*> result;
    for (Library::const_iterator it = library.begin(); it != library.end(); ++it) {
        if (ContainsIgnoreCase(it->title, query)) {
            result.push_back(&(*it));
        }
    }
    return result;
}

bool AuthorMatches(const Author& author, const Author& query) {
    if (CompareIgnoreCase(author.surname, query.surname) != 0) {
        return false;
    }
    if (!query.name.empty() && CompareIgnoreCase(author.name, query.name) != 0) {
        return false;
    }
    if (!query.patronymic.empty() &&
        CompareIgnoreCase(author.patronymic, query.patronymic) != 0) {
        return false;
    }
    return true;
}

std::vector<const Book*> SearchByAuthor(const Library& library,
                                        const Author& author_query) {
    std::vector<const Book*> result;
    for (Library::const_iterator book_it = library.begin(); book_it != library.end();
         ++book_it) {
        std::list<Author>::const_iterator auth_it = book_it->authors.begin();
        while (auth_it != book_it->authors.end()) {
            if (AuthorMatches(*auth_it, author_query)) {
                result.push_back(&(*book_it));
                break;
            }
            ++auth_it;
        }
    }
    return result;
}

Author ReadAuthorFromUser(const std::string& prompt) {
    while (true) {
        const std::string line = ReadLine(prompt);
        try {
            return ParseAuthor(line);
        } catch (const std::exception& err) {
            std::cout << err.what() << '\n';
        }
    }
}

void AddBook(Library& library) {
    Book book;
    book.udk = ReadInt("Enter UDK number: ");
    book.title = ReadLine("Enter title: ");
    book.year = ReadInt("Enter publication year: ");

    const int author_count = ReadInt("Enter number of authors (>=1): ", 1);
    for (int i = 0; i < author_count; ++i) {
        Author author = ReadAuthorFromUser("Enter author #" + std::to_string(i + 1) +
                                           " (Surname Name Patronymic?): ");
        InsertAuthorSorted(book.authors, author);
    }

    InsertBookSorted(library, book);
    std::cout << "Book \"" << book.title << "\" added.\n";
}

void RemoveBook(Library& library) {
    const std::string title = ReadLine("Enter title of the book to remove: ");
    auto it = FindBook(library, title);
    if (it == library.end()) {
        std::cout << "Book \"" << title << "\" not found.\n";
        return;
    }
    library.erase(it);
    std::cout << "Book removed.\n";
}

void SearchBooksByTitle(const Library& library) {
    const std::string query = ReadLine("Enter title (or part of it): ");
    auto matches = SearchByTitle(library, query);
    if (matches.empty()) {
        std::cout << "No books match the query.\n";
        return;
    }
    for (size_t i = 0; i < matches.size(); ++i) {
        PrintBook(*matches[i]);
    }
}

void SearchBooksByAuthor(const Library& library) {
    Author author_query = ReadAuthorFromUser(
        "Enter author to search (Surname Name Patronymic?): ");
    auto matches = SearchByAuthor(library, author_query);
    if (matches.empty()) {
        std::cout << "No books found for the specified author.\n";
        return;
    }
    for (size_t i = 0; i < matches.size(); ++i) {
        PrintBook(*matches[i]);
    }
}

void AddAuthorToBook(Library& library) {
    const std::string title = ReadLine("Enter title of the book to expand: ");
    auto it = FindBook(library, title);
    if (it == library.end()) {
        std::cout << "Book \"" << title << "\" not found.\n";
        return;
    }
    Author author = ReadAuthorFromUser("Enter new author (Surname Name Patronymic?): ");
    InsertAuthorSorted(it->authors, author);
    std::cout << "Author added to the book.\n";
}

void RemoveAuthorFromBook(Library& library) {
    const std::string title = ReadLine("Enter title of the book to modify: ");
    auto it = FindBook(library, title);
    if (it == library.end()) {
        std::cout << "Book \"" << title << "\" not found.\n";
        return;
    }
    Author author_query = ReadAuthorFromUser(
        "Enter author to remove (Surname Name Patronymic?): ");
    std::list<Author>::iterator author_it = it->authors.begin();
    while (author_it != it->authors.end() && !AuthorMatches(*author_it, author_query)) {
        ++author_it;
    }
    if (author_it == it->authors.end()) {
        std::cout << "The specified author is not in the book.\n";
        return;
    }
    it->authors.erase(author_it);
    std::cout << "Author removed.\n";
}

void PrintMenu() {
    std::cout << "\nLibrary Menu:\n"
              << "1. Show all books\n"
              << "2. Add book\n"
              << "3. Remove book\n"
              << "4. Search books by title\n"
              << "5. Search books by author\n"
              << "6. Add author to book\n"
              << "7. Remove author from book\n"
              << "0. Exit\n";
}
int main() {
    try {
        std::string path = ReadLine(
            "Enter path to the book data file "
            "(format: UDK;Title;Year;Author1|Author2|...): ");
        if (path.empty()) {
            std::cout << "No file specified. Exiting.\n";
            return 0;
        }

        Library library = LoadLibrary(path);
        std::cout << "Loaded " << library.size() << " books.\n";

        bool running = true;
        while (running) {
            PrintMenu();
            const int command = ReadInt("Choose action: ");
            switch (command) {
                case 1:
                    PrintLibrary(library);
                    break;
                case 2:
                    AddBook(library);
                    break;
                case 3:
                    RemoveBook(library);
                    break;
                case 4:
                    SearchBooksByTitle(library);
                    break;
                case 5:
                    SearchBooksByAuthor(library);
                    break;
                case 6:
                    AddAuthorToBook(library);
                    break;
                case 7:
                    RemoveAuthorFromBook(library);
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    std::cout << "Unknown command.\n";
            }
        }
    } catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << '\n';
        return 1;
    }

    return 0;
}
