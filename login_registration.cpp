#include "login_registration.h"

void LoginRegistration::loadUsers() {
    std::ifstream file(usersFile);
    std::string username, password;
    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
}

void LoginRegistration::saveUser(const std::string& username, const std::string& password) {
    std::ofstream file(usersFile, std::ios::app);
    file << username << " " << password << std::endl;
    file.close();
}

void LoginRegistration::registerUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (users.find(username) == users.end()) {
        users[username] = password;
        saveUser(username, password);
        std::cout << "Registration successful!\n";
    } else {
        std::cout << "Username already exists. Please try again.\n";
    }
}

bool LoginRegistration::loginUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (users.find(username) != users.end() && users[username] == password) {
        std::cout << "Login successful!\n";
        return true;
    } else {
        std::cout << "Invalid username or password. Please try again.\n";
        return false;
    }
}

void LoginRegistration::start() {
    loadUsers();
    int choice;
    while (true) {
        std::cout << "1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) return;
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    LoginRegistration system;
    system.start();
    return 0;
}
