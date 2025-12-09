#pragma once
#include <iostream>
#include <string>  
#include <chrono>
using namespace std;





// ------------------------------------------------------------
// FollowerSystem class using fixed-size arrays (no linked list, no vector)

class FollowerSystem {
public:

   
    string followers[500];
    int followersCount;

    string following[500];
    int followingCount;

    FollowerSystem();

    void follow(const string& self, const string& target);
    void unfollow(const string& self, const string& target);

    bool isFollowing(const string& target) const;
    bool isFollower(const string& target) const;

    void displayFollowers() const;
    void displayFollowing() const;

    int totalFollowers() const;
    int totalFollowing() const;
};

//------------------------------------------------------------
// //Linked list node storing usernames
// struct FollowNode {
//     string username;
//     FollowNode* next;
//     FollowNode(const string& name) : username(name), next(nullptr) {}
// };

// // ------------------------------------------------------------
// // FollowerSystem class using only usernames
// class FollowerSystem {
// public:
//     FollowNode* followersHead;  // List of usernames who follow this user
//     FollowNode* followingHead;  // List of usernames this user follows

//     FollowerSystem() : followersHead(nullptr), followingHead(nullptr) {}

//     // Add a follow relationship
//     void follow(const string& self, const string& target);

//     // Remove a follow relationship
//     void unfollow(const string& self, const string& target);

//     // Check if following
//     bool isFollowing(const string& target) const;

//     // Check if follower
//     bool isFollower(const string& target) const;

//     // Display followers
//     void displayFollowers() const;

//     // Display following
//     void displayFollowing() const;

//     // Count total followers
//     int totalFollowers() const;

//     // Count total following
//     int totalFollowing() const;

//     // Getters for internal lists (optional)
//     FollowNode* getFollowingHead() const { return followingHead; }
//     FollowNode* getFollowersHead() const { return followersHead; }
// };




