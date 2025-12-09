#pragma once
#include <iostream>
#include <vector>
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

    // ----------------- CHECK IF USER EXIST IN VECTOR -----------------
    static bool contains(const vector<User*>& vec, User* user)
    {
        for (User* u : vec)
            if (u == user)
                return true;
        return false;
    }

    // ----------------- MUTUAL FRIENDS -----------------
    static vector<User*> getMutualFriends(User* u1, User* u2)
    {
        vector<User*> mutual;
        vector<User*> u1Following;

        // store u1 following
        for (FollowNode* t = u1->getFollowerSystem().getFollowingHead(); t; t = t->next)
            u1Following.push_back(t->user);

        // compare with u2 following
        for (FollowNode* t = u2->getFollowerSystem().getFollowingHead(); t; t = t->next)
            if (contains(u1Following, t->user))
                mutual.push_back(t->user);

        return mutual;
    }

    // ----------------- BFS -----------------
    static void BFS(User* start)
    {
        if (!start) return;

        vector<User*> visited;
        queue<User*> q;

        visited.push_back(start);
        q.push(start);

        cout << "BFS Start: " << start->getUsername() << endl;

        while (!q.empty())
        {
            User* cur = q.front(); q.pop();
            cout << cur->getUsername() << " ";

            for (FollowNode* t = cur->getFollowerSystem().getFollowingHead(); t; t = t->next)
            {
                if (!contains(visited, t->user))
                {
                    visited.push_back(t->user);
                    q.push(t->user);
                }
            }
        }
        cout << endl;
    }

    // ----------------- USERS IN SAME CITY -----------------
    static vector<User*> getUsersInSameCity(const vector<User*>& allUsers, const string& city)
    {
        vector<User*> result;
        for (User* u : allUsers)
            if (u->getCity() == city)
                result.push_back(u);
        return result;
    }

    // ----------------- PRINT CONNECTIONS -----------------
    static void printConnections(User* u)
    {
        cout << u->getUsername() << " follows: ";
        for (FollowNode* t = u->getFollowerSystem().getFollowingHead(); t; t = t->next)
            cout << t->user->getUsername() << " ";
        cout << endl;
    }

    // ============================================================
    // ----------- ACTIVE USER GRAPH (status-based graph) ----------
    // ============================================================

    // Active graph nodes
    static vector<User*> getActiveUsers(const vector<User*>& allUsers)
    {
        vector<User*> active;
        for (User* u : allUsers)
        {
            // status stored in User class: "Online" / "Offline"
            if (u->getStatus() == "Online")
                active.push_back(u);
        }
        return active;
    }

    // Active graph edges (A follows B and both are active)
    static vector<pair<User*, User*>> getActiveEdges(const vector<User*>& allUsers)
    {
        vector<pair<User*, User*>> edges;

        for (User* u : allUsers)
        {
            if (u->getStatus() != "Online")
                continue;

            for (FollowNode* t = u->getFollowerSystem().getFollowingHead(); t; t = t->next)
            {
                if (t->user->getStatus() == "Online")
                    edges.push_back({u, t->user});
            }
        }
        return edges;
    }

    static void printActiveGraph(const vector<User*>& allUsers)
    {
        cout << "\nACTIVE USER GRAPH\n";

        vector<User*> active = getActiveUsers(allUsers);

        cout << "Active Users: ";
        for (User* u : active)
            cout << u->getUsername() << " ";
        cout << endl;

        cout << "Active Edges:\n";
        vector<pair<User*, User*>> edges = getActiveEdges(allUsers);

        for (auto& e : edges)
            cout << e.first->getUsername() << " → " << e.second->getUsername() << endl;

        cout << endl;
    }
};
