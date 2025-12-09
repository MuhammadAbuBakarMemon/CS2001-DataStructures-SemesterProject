#include "P:/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"


FollowerSystem::FollowerSystem() : followersCount(0), followingCount(0) {}

// Follow a user
void FollowerSystem::follow(const string& self, const string& target) {
    for (int i = 0; i < followingCount; ++i)
        if (following[i] == target) return; // Already following

    if (followingCount < 500)
        following[followingCount++] = target;
}

// Unfollow a user
void FollowerSystem::unfollow(const string& self, const string& target) {
    for (int i = 0; i < followingCount; ++i) {
        if (following[i] == target) {
            for (int j = i; j < followingCount - 1; ++j)
                following[j] = following[j + 1];
            --followingCount;
            break;
        }
    }
}

// Check if following
bool FollowerSystem::isFollowing(const string& target) const {
    for (int i = 0; i < followingCount; ++i)
        if (following[i] == target) return true;
    return false;
}

// Check if target is a follower
bool FollowerSystem::isFollower(const string& target) const {
    for (int i = 0; i < followersCount; ++i)
        if (followers[i] == target) return true;
    return false;
}

// Display followers
void FollowerSystem::displayFollowers() const {
    cout << "Followers:\n";
    for (int i = 0; i < followersCount; ++i)
        cout << " - " << followers[i] << "\n";
}

// Display following
void FollowerSystem::displayFollowing() const {
    cout << "Following:\n";
    for (int i = 0; i < followingCount; ++i)
        cout << " - " << following[i] << "\n";
}

// Count total followers
int FollowerSystem::totalFollowers() const { return followersCount; }

// Count total following
int FollowerSystem::totalFollowing() const { return followingCount; }
