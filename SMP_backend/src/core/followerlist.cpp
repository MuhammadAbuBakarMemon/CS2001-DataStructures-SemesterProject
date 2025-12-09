#pragma once
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/user.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/status.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/relationGraph.hpp"


void FollowerSystem::follow(User* self, User* target) {
    if (!self || !target || self == target) return;

    if (isFollowing(target)) return;

    // add to following 
    FollowNode* f = new FollowNode(target);
    f->next = followingHead;
    followingHead = f;

    // Add self to target's followers list
    FollowNode* t = new FollowNode(self);
    t->next = target->followerSystem.followersHead;
    target->followerSystem.followersHead = t;
}

// ------------------------------------------------------------
void FollowerSystem::unfollow(User* self, User* target) {
    if (!self || !target) return;

    // Remove from following list
    FollowNode* prev = nullptr;
    FollowNode* curr = followingHead;

    while (curr) {
        if (curr->user == target) {
            if (prev) prev->next = curr->next;
            else followingHead = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // Remove self from target's followers list
    prev = nullptr;
    curr = target->followerSystem.followersHead;

    while (curr) {
        if (curr->user == self) {
            if (prev) prev->next = curr->next;
            else target->followerSystem.followersHead = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

// ------------------------------------------------------------
bool FollowerSystem::isFollowing(User* target) const {
    FollowNode* curr = followingHead;
    while (curr) {
        if (curr->user == target) return true;
        curr = curr->next;
    }
    return false;
}


bool FollowerSystem::isFollower(User* target) const {
    FollowNode* curr = followersHead;
    while (curr) {
        if (curr->user == target) return true;
        curr = curr->next;
    }
    return false;
}

// ------------------------------------------------------------
int FollowerSystem::totalFollowers() const {
    int count = 0;
    for (FollowNode* c = followersHead; c; c = c->next) count++;
    return count;
}


int FollowerSystem::totalFollowing() const {
    int count = 0;
    for (FollowNode* c = followingHead; c; c = c->next) count++;
    return count;
}

// ------------------------------------------------------------
void FollowerSystem::displayFollowers() const {
    cout << "Followers:\n";
    FollowNode* curr = followersHead;
    while (curr) {
        cout << " - " << curr->user->getUsername() << "\n";
        curr = curr->next;
    }
}


void FollowerSystem::displayFollowing() const {
    cout << "Following:\n";
    FollowNode* curr = followingHead;
    while (curr) {
        cout << " - " << curr->user->getUsername() << "\n";
        curr = curr->next;
    }
}


void FollowerSystem::displayMutual(const FollowerSystem& other) const {
    cout << "Mutual Connections:\n";

    FollowNode* curr = followingHead;

    while (curr) {
        if (other.isFollowing(curr->user)) {
            cout << " - " << curr->user->getUsername() << "\n";
        }
        curr = curr->next;
    }
}
