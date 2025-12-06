#pragma once
#include <iostream>
#include <string>
using namespace std;

class User;


struct FollowNode {
    User* user;
    FollowNode* next;
    FollowNode(User* u) : user(u), next(nullptr) {}
};

class FollowerSystem {
private:
    //follower and following lists
    FollowNode* followersHead;
    FollowNode* followingHead;

public:
    FollowerSystem() : followersHead(nullptr), followingHead(nullptr) {}

    //operations
    void follow(User* self, User* target);
    void unfollow(User* self, User* target);

    bool isFollowing(User* target) const;
    bool isFollower(User* target) const;

    void displayFollowers() const;
    void displayFollowing() const;

    int totalFollowers() const;
    int totalFollowing() const;

    void displayMutual(const FollowerSystem& other) const;

    //
    // Getters for graph usage
    FollowNode* getFollowersHead() const { return followersHead; }
    FollowNode* getFollowingHead() const { return followingHead; }
};
