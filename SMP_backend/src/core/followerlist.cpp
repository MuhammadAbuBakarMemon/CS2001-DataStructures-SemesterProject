
#include "P:/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"

// Follow a user
void FollowerSystem::follow(const string& self, const string& target) {
    if (self == target) return;
    if (isFollowing(target)) return;

    // Add target to following list
    FollowNode* f = new FollowNode(target);
    f->next = followingHead;
    followingHead = f;

    // Add self to followers list
    FollowNode* t = new FollowNode(self);
    t->next = followersHead;
    followersHead = t;
}

// Unfollow a user
void FollowerSystem::unfollow(const string& self, const string& target) {
    // Remove from following
    FollowNode* prev = nullptr;
    FollowNode* curr = followingHead;
    while (curr) {
        if (curr->username == target) {
            if (prev) prev->next = curr->next;
            else followingHead = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // Remove from followers
    prev = nullptr;
    curr = followersHead;
    while (curr) {
        if (curr->username == self) {
            if (prev) prev->next = curr->next;
            else followersHead = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Check following
bool FollowerSystem::isFollowing(const string& target) const {
    for (FollowNode* c = followingHead; c; c = c->next)
        if (c->username == target) return true;
    return false;
}

// Check follower
bool FollowerSystem::isFollower(const string& target) const {
    for (FollowNode* c = followersHead; c; c = c->next)
        if (c->username == target) return true;
    return false;
}

// Count followers/following
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

// Display lists
void FollowerSystem::displayFollowers() const {
    cout << "Followers:\n";
    for (FollowNode* c = followersHead; c; c = c->next)
        cout << " - " << c->username << "\n";
}

void FollowerSystem::displayFollowing() const {
    cout << "Following:\n";
    for (FollowNode* c = followingHead; c; c = c->next)
        cout << " - " << c->username << "\n";
}

