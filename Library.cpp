#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    string category;
    bool available;

public:
    Book(int i, const string& t, const string& a, const string& c)
        : id(i), title(t), author(a), category(c), available(true) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    bool isAvailable() const { return available; }

    void borrowBook() {
        if (available) {
            available = false;
            cout << title << " has been borrowed.\n";
        } else {
            cout << title << " is currently not available.\n";
        }
    }

    void returnBook() {
        available = true;
        cout << title << " has been returned.\n";
    }

    void display() const {
        cout << id << " | " << title << " | " << author
             << " | " << category << " | "
             << (available ? "available" : "not available") << endl;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& b) { books.push_back(b); }

    void displayBooks() const {
        cout << "\n----- BOOKS IN LIBRARY -----\n";
        for (size_t i = 0; i < books.size(); i++)
            books[i].display();
    }

    void borrowBook(int id) {
        if (id > 0 && id <= books.size())
            books[id-1].borrowBook();
        else
            cout << "Invalid book ID!\n";
    }

    void returnBook(int id) {
        if (id > 0 && id <= books.size())
            books[id-1].returnBook();
        else
            cout << "Invalid book ID!\n";
    }
};

int main() {
    Library lib;
    lib.addBook(Book(1, "C++ Basics", "Emmanuel", "Programming"));
    lib.addBook(Book(2, "1984", "George Orwell", "Fiction"));
    lib.addBook(Book(3, "Data Structures", "Robert Lafore", "Programming"));

    int choice;
    do {
        cout << "\n--- LIBRARY MENU ---\n";
        cout << "1. Display all books\n";
        cout << "2. Borrow a book\n";
        cout << "3. Return a book\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                lib.displayBooks();
                break;

            case 2: {
                int id;
                cout << "Enter book ID to borrow: ";
                cin >> id;
                lib.borrowBook(id);
                break;
            }

            case 3: {
                int id;
                cout << "Enter book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            }

            case 4:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 4);

    return 0;
}
