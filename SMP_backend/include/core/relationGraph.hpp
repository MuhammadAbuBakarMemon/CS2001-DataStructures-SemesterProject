#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/user.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/status.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/relationGraph.hpp"

using namespace std;


class RelationshipGraph
{
public:
    // --------------------- Mutual Friends Graph ---------------------

    vector<User*> getMutualFriends(User* user1, User* user2);


    void BFS(User* startUser);


    // --------------------- City Graph ---------------------

    vector<User*> getUsersInSameCity(const vector<User*>& allUsers, const string& city);

    // Returns common city users
    vector<User*> getCommonCityUsers(User* user1, User* user2, const vector<User*>& allUsers);


};
