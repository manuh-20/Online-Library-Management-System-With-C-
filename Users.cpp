#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User {
private:
    int userId;
    string name;

public:
    User(int id, const string& n) : userId(id), name(n) {}

    int getUserId() const { return userId; }
    string getName() const { return name; }

    void display() const {
        cout << userId << " | " << name << endl;
    }
};

int main() {
    vector<User> users;
    users.push_back(User(101, "Emmanuel"));
    users.push_back(User(102, "Manuh"));
    users.push_back(User(103, "Alice"));

    int choice;
    do {
        cout << "\n--- USER MENU ---\n";
        cout << "1. Display all users\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\n----- USERS -----\n";
                for (size_t i = 0; i < users.size(); i++) {
                    users[i].display();
                }
                break;
            case 2:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 2);

    return 0;
}
