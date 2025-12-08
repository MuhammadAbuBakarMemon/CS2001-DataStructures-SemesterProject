#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "core/user.hpp" 

using namespace std;


class RelationshipGraph
{
public:
    // --------------------- Mutual Friends Graph ---------------------

    vector<User*> getMutualFriends(User* user1, User* user2);


    void BFS(User* startUser);

    // DFS traversal 
    void DFS(User* startUser);

    // --------------------- City Graph ---------------------

    vector<User*> getUsersInSameCity(const vector<User*>& allUsers, const string& city);

    // Returns common city users
    vector<User*> getCommonCityUsers(User* user1, User* user2, const vector<User*>& allUsers);

private:
    
    void DFS_Helper(User* user, set<unsigned long long>& visited);
};
