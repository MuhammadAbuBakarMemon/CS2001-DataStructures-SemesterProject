#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include "core/user.hpp"
#include "core/followerList.hpp"


class RelationshipGraph
{
public:
    // --------------------- Mutual Friends ---------------------
    static vector<User*> getMutualFriends(User* user1, User* user2)
    {
        set<User*> user1Following;
        vector<User*> mutual;

        // Collect user1's following
        for (FollowNode* temp = user1->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
            user1Following.insert(temp->user);

        // Compare with user2's following
        for (FollowNode* temp = user2->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
        {
            if (user1Following.find(temp->user) != user1Following.end())
                mutual.push_back(temp->user);
        }

        return mutual;
    }

    // --------------------- BFS ---------------------
    static void BFS(User* startUser)
    {
        if (!startUser) return;
        set<User*> visited;
        queue<User*> q;
        q.push(startUser);
        visited.insert(startUser);

        while (!q.empty())
        {
            User* current = q.front(); q.pop();
            cout << current->getUsername() << " ";

            for (FollowNode* temp = current->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
            {
                if (visited.find(temp->user) == visited.end())
                {
                    visited.insert(temp->user);
                    q.push(temp->user);
                }
            }
        }
        cout << endl;
    }

    // --------------------- DFS ---------------------
    static void DFS(User* startUser)
    {
        set<User*> visited;
        DFS_Helper(startUser, visited);
        cout << endl;
    }

    // --------------------- City Graph ---------------------
    static vector<User*> getUsersInSameCity(const vector<User*>& allUsers, const string& city)
    {
        vector<User*> sameCity;
        for (auto u : allUsers)
            if (u->getCity() == city)
                sameCity.push_back(u);
        return sameCity;
    }

    static vector<User*> getCommonCityUsers(User* user1, User* user2, const vector<User*>& allUsers)
    {
        vector<User*> commonCity;
        for (auto u : allUsers)
            if (u->getCity() == user1->getCity() && u->getCity() == user2->getCity())
                commonCity.push_back(u);
        return commonCity;
    }

    // --------------------- Social Helpers ---------------------
    static int countFollowing(User* user)
    {
        int count = 0;
        for (FollowNode* temp = user->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
            count++;
        return count;
    }

    static int countFollowers(User* target, const vector<User*>& allUsers)
    {
        int count = 0;
        for (auto u : allUsers)
            for (FollowNode* temp = u->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
                if (temp->user == target) { count++; break; }
        return count;
    }

    static vector<User*> suggestFriends(User* user, const vector<User*>& allUsers)
    {
        set<User*> yourFollowing;
        vector<User*> suggestions;

        for (FollowNode* temp = user->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
            yourFollowing.insert(temp->user);

        // Friends-of-friends
        for (FollowNode* temp = user->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
        {
            User* friendNode = temp->user;
            for (FollowNode* ftemp = friendNode->getFollowerSystem().getFollowingHead(); ftemp; ftemp = ftemp->next)
            {
                if (yourFollowing.find(ftemp->user) == yourFollowing.end() && ftemp->user != user)
                {
                    suggestions.push_back(ftemp->user);
                    yourFollowing.insert(ftemp->user);
                }
            }
        }
        return suggestions;
    }

    static void printConnections(User* user)
    {
        cout << user->getUsername() << " follows: ";
        for (FollowNode* temp = user->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
            cout << temp->user->getUsername() << " ";
        cout << endl;
    }

private:
    static void DFS_Helper(User* user, set<User*>& visited)
    {
        if (!user || visited.find(user) != visited.end()) return;
        visited.insert(user);
        cout << user->getUsername() << " ";

        for (FollowNode* temp = user->getFollowerSystem().getFollowingHead(); temp; temp = temp->next)
            DFS_Helper(temp->user, visited);
    }
};
