
#include "P:/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/status.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

StatusManager::StatusManager(UserManagement* table) {
    userTable = table;
}

string StatusManager::getStatus(const string& username) {
    return userTable->getStatusforclass(username);
}


static string timestampToString(time_t t) {
    if (t == 0) return "Never";

    tm* timeInfo = localtime(&t);  
    stringstream ss;

    ss << setfill('0')
       << setw(2) << timeInfo->tm_mday << "/"
       << setw(2) << timeInfo->tm_mon + 1 << "/"
       << setw(4) << timeInfo->tm_year + 1900 << "  "
       << setw(2) << timeInfo->tm_hour << ":"
       << setw(2) << timeInfo->tm_min  << ":"
       << setw(2) << timeInfo->tm_sec;

    return ss.str();
}

string StatusManager::getLastSeen(const string& username) {
    User* u = userTable->search(username);   
                                        

    if (!u) return "User not found.";

    if (u->getStatus() == "Online")
        return "Online now";

    return timestampToString(u->lastLogoutTime);
}

void StatusManager::markLogin(const string& username) {
    User* u = userTable->search(username);
    if (!u) return;

    u->setStatus("Online");
    u->lastLoginTime = time(nullptr);  
}   

void StatusManager::markLogout(const string& username) {
    User* u = userTable->search(username);
    if (!u) return;

    u->setStatus("Offline");
    u->lastLogoutTime = time(nullptr); 
}

bool StatusManager::isActive(const string& username, int minutesThreshold) {
    User* u = userTable->search(username);
    if (!u) return false;

    time_t now = time(nullptr);

    if (u->lastLoginTime == 0)
        return false;

    double diffMinutes = difftime(now, u->lastLoginTime) / 60.0;

    return diffMinutes <= minutesThreshold;
}

void StatusManager::printAllStatuses() const {
    cout << "=== USER STATUS REPORT ===\n";
    userTable->displayAllUsers();
}
