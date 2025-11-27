#ifndef STATUS_MANAGER_HPP
#define STATUS_MANAGER_HPP

#include <string>
#include <ctime>
using namespace std;

// Forward declare your User and UserManagement classes
class User;
class UserManagement;

class StatusManager {
private:
    UserManagement* userTable;  // Reference to existing UserManagement

public:
    StatusManager(UserManagement* table);

    // Returns "Online", "Offline", "Inactive"
    string getStatus(const string& username);

    // Returns human-readable last login timestamp
    string getLastSeen(const string& username);

    // Updates last-login and sets active state
    void markLogin(const string& username);

    // Updates last-logout and sets inactive state
    void markLogout(const string& username);

    // Optional helpers
    bool isActive(const string& username, int minutesThreshold = 10); // online in last X minutes
    void printAllStatuses() const; // Print all users and their status
};

#endif
