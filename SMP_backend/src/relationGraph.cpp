
#include "P:/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/relationGraph.hpp"
using namespace std;

// --------------------- Helper ---------------------
User* RelationshipGraph::findUserByUsername(const vector<User*>& allUsers, const string& username) const {
    for (User* u : allUsers) {
        if (u->getUsername() == username) return u;
    }
    return nullptr;
}

// --------------------- Mutual Friends ---------------------
vector<User*> RelationshipGraph::getMutualFriends(User* user1, User* user2, const vector<User*>& allUsers) {
    set<string> user1Following;
    vector<User*> mutualFriends;

    // Fill user1 following set
    for (FollowNode* f = user1->followerSystem.getFollowingHead(); f; f = f->next)
        user1Following.insert(f->username);

    // Check user2 following against user1
    for (FollowNode* f = user2->followerSystem.getFollowingHead(); f; f = f->next) {
        if (user1Following.count(f->username)) {
            User* u = findUserByUsername(allUsers, f->username);
            if (u) mutualFriends.push_back(u);
        }
    }

    return mutualFriends;
}

// --------------------- BFS ---------------------
void RelationshipGraph::BFS(User* startUser, const vector<User*>& allUsers) {
    if (!startUser) return;

    set<string> visited;
    queue<User*> q;

    visited.insert(startUser->getUsername());
    q.push(startUser);

    while (!q.empty()) {
        User* curr = q.front(); q.pop();
        cout << curr->getUsername() << " ";

        for (FollowNode* f = curr->followerSystem.getFollowingHead(); f; f = f->next) {
            if (!visited.count(f->username)) {
                User* nextUser = findUserByUsername(allUsers, f->username);
                if (nextUser) {
                    visited.insert(nextUser->getUsername());
                    q.push(nextUser);
                }
            }
        }
    }
    cout << endl;
}

// --------------------- Users in same city ---------------------
vector<User*> RelationshipGraph::getUsersInSameCity(const vector<User*>& allUsers, const string& city) {
    vector<User*> result;
    for (User* u : allUsers) {
        if (u->getCity() == city)
            result.push_back(u);
    }
    return result;
}

// --------------------- Common city users ---------------------
vector<User*> RelationshipGraph::getCommonCityUsers(User* user1, User* user2, const vector<User*>& allUsers) {
    vector<User*> city1 = getUsersInSameCity(allUsers, user1->getCity());
    vector<User*> city2 = getUsersInSameCity(allUsers, user2->getCity());

    set<User*> s1(city1.begin(), city1.end());
    vector<User*> common;

    for (User* u : city2) {
        if (s1.count(u)) common.push_back(u);
    }

    return common;
}
