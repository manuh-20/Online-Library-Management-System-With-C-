#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;

public:
    Book(const std::string& t, const std::string& a, const std::string& i)
        : title(t), author(a), isbn(i), isAvailable(true) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
    bool isAvailableNow() const { return isAvailable; }

    void setAvailability(bool status) { isAvailable = status; }
};

class Member {
private:
    std::string name;
    int memberID;
    std::vector<std::string> borrowedBooks;

public:
    Member(const std::string& n, int id) : name(n), memberID(id) {}

    std::string getName() const { return name; }
    int getMemberID() const { return memberID; }
    const std::vector<std::string>& getBorrowedBooks() const { return borrowedBooks; }

    bool hasBorrowed(const std::string& isbn) const {
        return std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn) != borrowedBooks.end();
    }

    void borrowBook(const std::string& isbn) {
        borrowedBooks.push_back(isbn);
    }

    void returnBook(const std::string& isbn) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    int nextMemberID = 1;

public:
    void addBook(const std::string& title, const std::string& author, const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
            [&isbn](const Book& b) { return b.getISBN() == isbn; });

        if (it != books.end()) {
            std::cout << "Book with this ISBN already exists.\n";
            return;
        }

        books.emplace_back(title, author, isbn);
        std::cout << "Book added successfully.\n";
    }

    void removeBook(const std::string& isbn) {
        auto it = std::find_if(books.begin(), books.end(),
            [&isbn](const Book& b) { return b.getISBN() == isbn; });

        if (it == books.end()) {
            std::cout << "Book not found.\n";
            return;
        }

        if (!it->isAvailableNow()) {
            std::cout << "Cannot remove a borrowed book.\n";
            return;
        }

        books.erase(it);
        std::cout << "Book removed successfully.\n";
    }

    void searchBook(const std::string& query) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle().find(query) != std::string::npos ||
                book.getAuthor().find(query) != std::string::npos ||
                book.getISBN() == query) {

                std::cout << "Title: " << book.getTitle()
                          << ", Author: " << book.getAuthor()
                          << ", ISBN: " << book.getISBN()
                          << ", Available: " << (book.isAvailableNow() ? "Yes" : "No") << '\n';
                found = true;
            }
        }
        if (!found) {
            std::cout << "No matching books found.\n";
        }
    }

    void addMember(const std::string& name) {
        members.emplace_back(name, nextMemberID);
        std::cout << "Member added. ID: " << nextMemberID << '\n';
        nextMemberID++;
    }

    void borrowBook(int memberID, const std::string& isbn) {
        auto memberIt = std::find_if(members.begin(), members.end(),
            [memberID](const Member& m) { return m.getMemberID() == memberID; });

        if (memberIt == members.end()) {
            std::cout << "Member not found.\n";
            return;
        }

        auto bookIt = std::find_if(books.begin(), books.end(),
            [&isbn](const Book& b) { return b.getISBN() == isbn; });

        if (bookIt == books.end()) {
            std::cout << "Book not found.\n";
            return;
        }

        if (!bookIt->isAvailableNow()) {
            std::cout << "Book is currently not available.\n";
            return;
        }

        if (memberIt->hasBorrowed(isbn)) {
            std::cout << "Member already borrowed this book.\n";
            return;
        }

        bookIt->setAvailability(false);
        memberIt->borrowBook(isbn);
        std::cout << "Book borrowed successfully.\n";
    }

    void returnBook(int memberID, const std::string& isbn) {
        auto memberIt = std::find_if(members.begin(), members.end(),
            [memberID](const Member& m) { return m.getMemberID() == memberID; });

        if (memberIt == members.end()) {
            std::cout << "Member not found.\n";
            return;
        }

        if (!memberIt->hasBorrowed(isbn)) {
            std::cout << "This member did not borrow that book.\n";
            return;
        }

        auto bookIt = std::find_if(books.begin(), books.end(),
            [&isbn](const Book& b) { return b.getISBN() == isbn; });

        if (bookIt == books.end()) {
            std::cout << "Book record not found.\n";
            return;
        }

        bookIt->setAvailability(true);
        memberIt->returnBook(isbn);
        std::cout << "Book returned successfully.\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }

        for (const auto& book : books) {
            std::cout << "Title: " << book.getTitle()
                      << ", Author: " << book.getAuthor()
                      << ", ISBN: " << book.getISBN()
                      << ", Available: " << (book.isAvailableNow() ? "Yes" : "No") << '\n';
        }
    }

    void displayMembers() const {
        if (members.empty()) {
            std::cout << "No members in the library.\n";
            return;
        }

        for (const auto& member : members) {
            std::cout << "Name: " << member.getName()
                      << ", ID: " << member.getMemberID() << '\n';

            std::cout << "Borrowed Books: ";
            if (member.getBorrowedBooks().empty()) {
                std::cout << "None";
            } else {
                for (const auto& isbn : member.getBorrowedBooks()) {
                    std::cout << isbn << " ";
                }
            }
            std::cout << '\n';
        }
    }
};

void showMenu() {
    std::cout << "\nLibrary Management System Menu\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Remove Book\n";
    std::cout << "3. Search Book\n";
    std::cout << "4. Add Member\n";
    std::cout << "5. Borrow Book\n";
    std::cout << "6. Return Book\n";
    std::cout << "7. Display All Books\n";
    std::cout << "8. Display All Members\n";
    std::cout << "9. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Library library;
    int choice;
    int memberID;
    std::string title, author, isbn, query, name;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                library.addBook(title, author, isbn);
                break;

            case 2:
                std::cout << "Enter ISBN to remove: ";
                std::getline(std::cin, isbn);
                library.removeBook(isbn);
                break;

            case 3:
                std::cout << "Enter search query: ";
                std::getline(std::cin, query);
                library.searchBook(query);
                break;

            case 4:
                std::cout << "Enter member name: ";
                std::getline(std::cin, name);
                library.addMember(name);
                break;

            case 5:
                std::cout << "Enter member ID: ";
                std::cin >> memberID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter ISBN to borrow: ";
                std::getline(std::cin, isbn);
                library.borrowBook(memberID, isbn);
                break;

            case 6:
                std::cout << "Enter member ID: ";
                std::cin >> memberID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter ISBN to return: ";
                std::getline(std::cin, isbn);
                library.returnBook(memberID, isbn);
                break;

            case 7:
                library.displayBooks();
                break;

            case 8:
                library.displayMembers();
                break;

            case 9:
                std::cout << "Exiting the system.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 9);

    
}
