#include <iostream>
#include <cstring>
#include <algorithm>

class Book {
public:
    char* title;
    char* author;
    int publicationYear;
    bool isAvailable;

    Book() : title(nullptr), author(nullptr), publicationYear(0), isAvailable(false) {}

    Book(const char* t, const char* a, int year, bool avail = true) {
        title = new char[std::strlen(t) + 1];
        std::strcpy(title, t);

        author = new char[std::strlen(a) + 1];
        std::strcpy(author, a);

        publicationYear = year;
        isAvailable = avail;
    }

    Book(const Book& other) {
        title = new char[std::strlen(other.title) + 1];
        std::strcpy(title, other.title);

        author = new char[std::strlen(other.author) + 1];
        std::strcpy(author, other.author);

        publicationYear = other.publicationYear;
        isAvailable = other.isAvailable;
    }

    Book& operator=(const Book& other) {
        if (this == &other) {
            return *this;
        }

        delete[] title;
        delete[] author;

        title = new char[std::strlen(other.title) + 1];
        std::strcpy(title, other.title);

        author = new char[std::strlen(other.author) + 1];
        std::strcpy(author, other.author);

        publicationYear = other.publicationYear;
        isAvailable = other.isAvailable;

        return *this;
    }

    ~Book() {
        delete[] title;
        delete[] author;
    }

    void display() const {
        std::cout << "  Title: " << title
                  << ", Author: " << author
                  << ", Year: " << publicationYear
                  << ", Available: " << (isAvailable ? "Yes" : "No")
                  << std::endl;
    }
};

void addBook(Book**& library, int& bookCount, int& capacity) {
    if (bookCount == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        Book** newLibrary = new Book*[newCapacity];
        for (int i = 0; i < bookCount; ++i) {
            newLibrary[i] = library[i];
        }
        delete[] library;
        library = newLibrary;
        capacity = newCapacity;
    }

    char title[256];
    char author[256];
    int year;

    std::cout << "Enter title: ";
    std::cin >> title;
    std::cout << "Enter author: ";
    std::cin >> author;
    std::cout << "Enter publication year: ";
    std::cin >> year;

    library[bookCount] = new Book(title, author, year, true);
    bookCount++;
    std::cout << "Book added." << std::endl;
}

void displayBooks(Book** library, int bookCount) {
    if (bookCount == 0) {
        std::cout << "Library is empty." << std::endl;
        return;
    }
    std::cout << "--- Library Books ---" << std::endl;
    for (int i = 0; i < bookCount; ++i) {
        std::cout << i + 1 << ".";
        library[i]->display();
    }
    std::cout << "---------------------" << std::endl;
}

void deleteBook(Book** library, int& bookCount) {
    char title[256];
    std::cout << "Enter title of book to delete: ";
    std::cin >> title;

    int foundIndex = -1;
    for (int i = 0; i < bookCount; ++i) {
        if (std::strcmp(library[i]->title, title) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        std::cout << "Book not found." << std::endl;
    } else {
        delete library[foundIndex];
        
        for (int i = foundIndex; i < bookCount - 1; ++i) {
            library[i] = library[i + 1];
        }
        library[bookCount - 1] = nullptr;
        bookCount--;
        std::cout << "Book deleted." << std::endl;
    }
}

bool compareByTitle(const Book* a, const Book* b) {
    return std::strcmp(a->title, b->title) < 0;
}

bool compareByYear(const Book* a, const Book* b) {
    return a->publicationYear < b->publicationYear;
}

void sortBooks(Book** library, int bookCount, bool (*compareFunc)(const Book*, const Book*)) {
    if (bookCount < 2) return;

    for (int i = 0; i < bookCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < bookCount; ++j) {
            if (compareFunc(library[j], library[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(library[i], library[minIndex]);
        }
    }
}

int main() {
    Book** library = nullptr;
    int bookCount = 0;
    int capacity = 0;
    int choice;

    do {
        std::cout << "\nLibrary Management System" << std::endl;
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. Display All Books" << std::endl;
        std::cout << "3. Delete Book" << std::endl;
        std::cout << "4. Sort by Title" << std::endl;
        std::cout << "5. Sort by Year" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            addBook(library, bookCount, capacity);
        } else if (choice == 2) {
            displayBooks(library, bookCount);
        } else if (choice == 3) {
            deleteBook(library, bookCount);
        } else if (choice == 4) {
            sortBooks(library, bookCount, compareByTitle);
            std::cout << "Books sorted by title." << std::endl;
            displayBooks(library, bookCount);
        } else if (choice == 5) {
            sortBooks(library, bookCount, compareByYear);
            std::cout << "Books sorted by year." << std::endl;
            displayBooks(library, bookCount);
        } else if (choice == 6) {
            std::cout << "Exiting." << std::endl;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    for (int i = 0; i < bookCount; ++i) {
        delete library[i];
    }
    delete[] library;

    return 0;
}