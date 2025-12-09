#include "../include/core/user.hpp"
#include "../include/core/followerList.hpp"
#include "../include/core/status.hpp"
// #include "../include/core/relationGraph.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    UserManagement systemUser;
    StatusManager statusMgr(&systemUser);
    // RelationshipGraph graph;

    // Load users from file
    ifstream fin("users.txt");
    if (!fin.is_open()) {
        cout << "Cannot open file!\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        int p1 = line.find('/');
        int p2 = line.find('/', p1 + 1);
        if (p1 == -1 || p2 == -1) continue;

        string username = line.substr(0, p1);
        string password = line.substr(p1 + 1, p2 - (p1 + 1));
        string city     = line.substr(p2 + 1);

        systemUser.registerUser(username, password, city);
    }
    fin.close();

    User* loggedInUser = nullptr;
    bool run = true;

    while (run) {
        if (!loggedInUser) {
            // ===== LOGIN / REGISTER MENU =====
            cout << "\n1. Login\n2. Register\n3. Exit\nChoice: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string uname, pwd;
                cout << "Username: ";
                cin >> uname;
                cout << "Password: ";
                cin >> pwd;
                if (systemUser.loginUser(uname, pwd)) {
                    loggedInUser = systemUser.search(uname);
                    statusMgr.markLogin(uname);
                    cout << "Logged in as " << uname << "\n";
                } else {
                    cout << "Invalid credentials.\n";
                }
            } else if (choice == 2) {
                string uname, pwd, city;
                cout << "Username: "; cin >> uname;
                cout << "Password: "; cin >> pwd;
                cout << "City: "; cin >> city;
                if (systemUser.registerUser(uname, pwd, city))
                    cout << "User registered!\n";
                else
                    cout << "Registration failed.\n";
            } else {
                run = false;
            }
        } else {
            // ===== USER MENU =====
            cout << "\n1. Update Status\n2. Follow User\n3. Unfollow User\n"
                 << "4. Show Followers\n5. Show Following\n6. Logout\nChoice: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string newStatus;
                cout << "Enter new status: ";
                getline(cin, newStatus);
                loggedInUser->setStatus(newStatus);
                cout << "Status updated!\n";
            } else if (choice == 2) {
                string target;
                // cout << "Enter username to follow: ";

                // cin >> target;

                //----------------------------------------------
 ifstream fin("users.txt");
    if (!fin.is_open()) {
        cout << "Cannot open file!\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        int p1 = line.find('/');
        int p2 = line.find('/', p1 + 1);
        if (p1 == -1 || p2 == -1) continue;

        string username = line.substr(0, p1);
        string password = line.substr(p1 + 1, p2 - (p1 + 1));
        string city     = line.substr(p2 + 1);

        target = username;

         User* targetUser = systemUser.search(username);
                if (targetUser)
                    loggedInUser->followerSystem.follow(loggedInUser->username, targetUser->username);
                else
                    cout << "User not found.\n";
        
    }
    fin.close();
                //--------------------------------------------



                // User* targetUser = systemUser.search(target);
                // if (targetUser)
                //     loggedInUser->followerSystem.follow(loggedInUser->username, targetUser->username);
                // else
                //     cout << "User not found.\n";
            } else if (choice == 3) {
                string target;
                cout << "Enter username to unfollow: ";
                cin >> target;
                User* targetUser = systemUser.search(target);
                if (targetUser)
                    loggedInUser->followerSystem.unfollow(loggedInUser->username, targetUser->username);
                else
                    cout << "User not found.\n";
            } else if (choice == 4) {
                loggedInUser->followerSystem.displayFollowers();
                cout << "Total Followers: " << loggedInUser->followerSystem.totalFollowers() << "\n";
            } else if (choice == 5) {
                 using clock = chrono::high_resolution_clock;

                  auto start = clock::now(); 
                loggedInUser->followerSystem.displayFollowing();

                  auto end = clock::now();     // End stopwatch

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

   
                cout << "Total Following: " << loggedInUser->followerSystem.totalFollowing() << "\n";

                   cout << "Loop took " << duration.count() << " microseconds\n";
            } else if (choice == 6) {
                statusMgr.markLogout(loggedInUser->getUsername());
                loggedInUser = nullptr;
                cout << "Logged out.\n";
            }
        }
    }

    return 0;
}
