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

int main() {
    vector<Book> books;
    books.push_back(Book(1, "C++ Basics", "Emmanuel", "Programming"));
    books.push_back(Book(2, "1984", "George Orwell", "Fiction"));
    books.push_back(Book(3, "Data Structures", "Robert Lafore", "Programming"));

    int choice;
    do {
        cout << "\n--- BOOK MENU ---\n";
        cout << "1. Display all books\n";
        cout << "2. Borrow a book\n";
        cout << "3. Return a book\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\n----- BOOKS -----\n";
                for (size_t i = 0; i < books.size(); i++) {
                    books[i].display();
                }
                break;

            case 2: {
                int id;
                cout << "Enter book ID to borrow: ";
                cin >> id;
                if (id > 0 && id <= books.size())
                    books[id-1].borrowBook();
                else
                    cout << "Invalid book ID!\n";
                break;
            }

            case 3: {
                int id;
                cout << "Enter book ID to return: ";
                cin >> id;
                if (id > 0 && id <= books.size())
                    books[id-1].returnBook();
                else
                    cout << "Invalid book ID!\n";
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
