#pragma once
#include <iostream>
#include "core/user.hpp"
#include "ADT/linked_list.hpp"

using namespace std;

class RecommendationSystem {
public:
    static LinkedList<User*> getSuggestions(User* currentUser, LinkedList<User*>& allUsers) {
        LinkedList<User*> suggestions;
        
        if (!currentUser) return suggestions;

        Node<User*>* curr = allUsers.getHead();
        while (curr) {
            User* candidate = curr->data;

            bool isSelf = (candidate->getID() == currentUser->getID());
            bool alreadyFollowing = currentUser->getFollowerSystem().isFollowing(candidate->getID());

            if (!isSelf && !alreadyFollowing) {
                suggestions.append(candidate);
            }

            curr = curr->next;
        }

        return suggestions;
    }

    static void displaySuggestions(User* currentUser, LinkedList<User*>& allUsers) {
        LinkedList<User*> suggestions = getSuggestions(currentUser, allUsers);

        cout << "\n=== SUGGESTED USERS TO FOLLOW ===\n";
        
        if (suggestions.isEmpty()) {
            cout << "No new users to follow at the moment.\n";
            return;
        }

        Node<User*>* curr = suggestions.getHead();
        int count = 0;
        
        while (curr && count < 5) { 
            User* u = curr->data;
            cout << "ID: " << u->getID() << " | @" << u->getUsername() << "\n";
            curr = curr->next;
            count++;
        }
        cout << "--------------------------------\n";
    }
};
