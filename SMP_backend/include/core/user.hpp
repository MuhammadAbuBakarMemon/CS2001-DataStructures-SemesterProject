#pragma once

#include <iostream>
#include <string>
using namespace std;

// =========================================================
// UserManagement Module
// Handles user registration, login, logout, and profile storage.
// Data Structures: Linked List, Hash Map
// Algorithms: Hashing (for username lookup), Linear Search
// =========================================================

class User
{
private:
    unsigned long long u_id;

    string username;
    string password;
    string city;
    string status;
    User *next;

    static unsigned long long nextUID;

public:
    User(const string &uname, const string &pwd, const string &cty);

    unsigned long long getID() const;
    string getUsername() const;
    string getCity() const;
    string getStatus() const;
    User *getNext() const;

    void setID(unsigned long long newID);
    void setUsername(const string &u);
    void setPassword(const string &p);
    void setCity(const string &c);
    void setStatus(const string &s);
    void setNext(User *n);

    void verifyPassword(const string &input) const;

    void display() const;
};

class UserManagement
{
private:
    static const int TABLE_SIZE = 100;
    User *hashTable[TABLE_SIZE];

    // Hash function for username lookup
    // Converts username characters into a hash index
    int hashFunction(const string &username) const;

    User *searchUserInList(User *head, const string &username) const;

public:
    UserManagement();
    ~UserManagement();

    bool registerUser(const string &username, const string &password, const string &city);
    bool loginUser(const string &username, const string &password);
    bool logoutUser(const string &username);
    bool resetPassword(const string &username, const string &newPassword);

    void displayAllUsers() const;
    void displayUserProfile(const string &username) const;

    bool deleteUser(const string &username);
    bool updateProfile(const string &username, const string newCity, const string newStatus);
};
