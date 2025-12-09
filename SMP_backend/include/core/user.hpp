#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/user.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/status.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/relationGraph.hpp"

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
    time_t lastLoginTime;
    time_t lastLogoutTime;
    FollowerSystem followerSystem;

    User(const string &uname, const string &pwd, const string &cty);

    unsigned long long getID() const;
    string getUsername() const;
    string getCity() const;
    string getStatus() const;
    User *getNext() const;
    string getPassword() const;


    void setID(unsigned long long newID);
    void setUsername(const string &u);
    void setPassword(const string &p);
    void setCity(const string &c);
    void setStatus(const string &s);
    void setNext(User *n);

    bool verifyPassword(const string &input) const; // set to bool so other class can check if required

    void display() const;

      //for grapgh
    // Access follower system
    FollowerSystem& getFollowerSystem() { return followerSystem; }
};

class UserManagement
{
private: // size taken large as the platform is for social media
          // we are using seprate chaining for hasing which is convineent, as user can increasse
          // at abnormal rates thus latency can be high when alot of user try creating account 
          // so open adressing wil l fail
          //size could have been taken 31 like java's prebuilt but due to platform size 103 was 
          //considered ideal
    static const int TABLE_SIZE = 103; // setting prime number for efficient hashing 
    User *hashTable[TABLE_SIZE];

    // Hash function for username lookup
    // Converts username characters into a hash index
    int hashFunction(const string &username) const;
    User *searchUserInList(User *head, const string &username) const;

public:
    UserManagement();
    ~UserManagement();

    string getStatusforclass(const string& username)const;
    User* search (const string& username)const;
   

    bool registerUser(const string &username, const string &password, const string &city);
    bool loginUser(const string &username, const string &password);
    bool logoutUser(const string &username);
    bool resetPassword(const string &username, const string &newPassword);

    void displayAllUsers() const;
    void displayUserProfile(const string &username) const;

    bool deleteUser(const string &username);
    bool updateProfile(const string &username, const string newCity, const string newStatus);

  

};
