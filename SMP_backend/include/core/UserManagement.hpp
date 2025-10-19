#ifndef USER_MANAGEMENT_HPP
#define USER_MANAGEMENT_HPP

#include <iostream>
#include <string>

using namespace std;

// =========================================================
// UserManagement Module
// Handles user registration, login, logout, and profile storage.
// Data Structures: Linked List, Hash Map
// Algorithms: Hashing (for username lookup), Linear Search
// =========================================================

class User {
public:
    string username;
    string password;
    string city;
    string posts;
    string status;
    User* next;

    User(const string& uname, const string& pwd, const string& cty)
        : username(uname), password(pwd), city(cty),
          posts(""), status("offline"), next(nullptr) {}
};

class UserManagement {
private:
    static const int TABLE_SIZE = 100;
    User* hashTable[TABLE_SIZE];

    // Hash function for username lookup
    // Converts username characters into a hash index
    int hashFunction(const string& username) const;

    User* searchUserInList(User* head, const string& username) const;

public:
    UserManagement();
    ~UserManagement();

    bool registerUser(const string& username, const string& password, const string& city);
    bool loginUser(const string& username, const string& password);
    bool logoutUser(const string& username);
    bool resetPassword(const string& username, const string& newPassword);

    void displayAllUsers() const;
    void displayUserProfile(const string& username) const;
};

#endif 
