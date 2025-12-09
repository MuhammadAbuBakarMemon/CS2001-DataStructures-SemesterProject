#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/user.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/status.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/relationGraph.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

   UserManagement systemUser;


    //500 users data input form file and into system
    ifstream fin("users.txt");
    if (!fin.is_open()) {
        cout << "Cannot open file!\n";
        return 1;
    }

    string line;

    while (getline(fin, line)) {

        int p1 = line.find('/');     // first slash
        int p2 = line.find('/', p1 + 1);  // second slash

        if (p1 == -1 || p2 == -1) {
            cout << "Invalid line: " << line << "\n";
            continue; 
        }

        string username = line.substr(0, p1);
        string password = line.substr(p1 + 1, p2 - (p1 + 1));
        string city     = line.substr(p2 + 1);

    //    systemUser.registerUser(username,password,city);
       cout << username << endl;
    }

    // systemUser.displayAllUsers();

    fin.close();
    return 0;
}