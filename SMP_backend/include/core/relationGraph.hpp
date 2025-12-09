#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "user.hpp"
#include "followerList.hpp"

using namespace std;

class RelationshipGraph {
public:

    // --------------------- Mutual Friends Graph ---------------------
    // Returns vector of mutual friends (common usernames converted to User* via allUsers map)
    vector<User*> getMutualFriends(User* user1, User* user2, const vector<User*>& allUsers);

    // Simple BFS starting from a user (prints usernames)
    void BFS(User* startUser, const vector<User*>& allUsers);

    // --------------------- City Graph ---------------------
    // Returns users in the same city as given city
    vector<User*> getUsersInSameCity(const vector<User*>& allUsers, const string& city);

    // Returns users in same city as both user1 and user2 (intersection)
    vector<User*> getCommonCityUsers(User* user1, User* user2, const vector<User*>& allUsers);

private:
    // Helper: find User* by username from allUsers vector
    User* findUserByUsername(const vector<User*>& allUsers, const string& username) const;
};
