#ifndef LOGIN_REGISTRATION_H
#define LOGIN_REGISTRATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class LoginRegistration {
public:
    void registerUser();
    bool loginUser();
    void start();

private:
    std::unordered_map<std::string, std::string> users;
    const std::string usersFile = "users.txt";
    void loadUsers();
    void saveUser(const std::string& username, const std::string& password);
};

#endif // LOGIN_REGISTRATION_H
