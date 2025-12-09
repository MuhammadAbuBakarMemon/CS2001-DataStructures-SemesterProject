// make no changes to code im connecting the classes of status and user it require some work
//will upload status as well 
#include <iostream>
#include <string>
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/user.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/followerList.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/status.hpp"
#include "/home/mushaf-ali-mir/Documents/Github/Repos/CS2001-DataStructures-SemesterProject/SMP_backend/include/core/relationGraph.hpp"

unsigned long long User::nextUID = 10101;


User :: User (const string &uname, const string &pwd, const string &cty){
    
    username = uname;
    password = pwd;
    city = cty;
    
    u_id = nextUID++; //basiclly we start from  (1st user) and as user are ccreated it moves to next ID for the future new user

}

unsigned long long User::getID() const {
    return u_id;
}

string User::getUsername() const {
    return username;
}

string User::getCity() const {
    return city;
}

string User::getStatus() const {
    return status;
}

User* User::getNext() const {
    return next;
}

string User::getPassword () const{
    return password;
}

bool User::verifyPassword(const string& inputpassword) const{

    if (password == inputpassword){
        return true;
       }
    return false;

}

void User::display() const
{
    int width = 80;

    auto printCyanCentered  = [width](const string& text){
        string padding ((width - text.length())/2 , ' ');
        cout << "\033[36m" << padding << text << "\033[0m" << endl;
    };

      printCyanCentered("-----------------------------------");
    printCyanCentered("User ID: " + to_string(u_id));
    printCyanCentered("Username: " + username);
    printCyanCentered("City: " + city);
    printCyanCentered("Status: " + status);
    printCyanCentered("-----------------------------------");
}

 void User::setID(unsigned long long newID){
    u_id = newID;
 }
    void User :: setUsername(const string &u){
        username = u;
    }
    void User :: setPassword(const string &p){
        password = p;
    }
    void User :: setCity(const string &c){
        city = c;
    }
    void User :: setStatus(const string &s){
        status = s;
    }
    void User :: setNext(User *n){
        next = n;
    }


UserManagement::UserManagement() {
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = nullptr;
}


UserManagement :: ~UserManagement (){

    User* current = hashTable [0];

    for (int i = 0 ; i < TABLE_SIZE ; i++){

        current = hashTable[i];

        while(current){
         User* tmp = current;
         current = current->getNext();
         delete tmp;
    }
    hashTable [i] = 0;
}

}

int UserManagement ::  hashFunction(const string &key) const{//following hashing fucntion is java library prebuilt func which perofrm well on string chars and give otimized performance

     unsigned int hash = 0;
      for (char ch : key ){
            hash = (hash * 31  +static_cast<unsigned int>(ch));//though static cast not required but AI recommended and was also a refresher of an PF subject so i used it, same for unsigned(which maybe be used for exception handling so hash can never be negative)
      }

      return hash;

}

User* UserManagement :: searchUserInList (User* head , const string& username) const {

    User* current = head;

    while (current){

        if (current -> getUsername() == username){
            return current;
        }
        current = current -> getNext();
 }
    return nullptr;
}


bool UserManagement :: registerUser (const string &username, const string &password, const string &city){

    int index = hashFunction (username);

    if (searchUserInList(hashTable[index] , username)){
        return false;
    }
    User* newUser = new User (username , password, city);

    newUser->setNext (hashTable[index]);
    hashTable[index] = newUser;        //bascilly hashtanle[index] head is made made to have a new ptr whcih points to prevoius head
                                      //thus new user is inserted at the head ot index i bcz our sense is when a user cretaes account he might also 
      return true;                    //want login that moment so there login is optimized
    
}

bool UserManagement :: loginUser (const string& username , const string& password){
    int index = hashFunction(username);

    User* user = searchUserInList (hashTable[index],username);

    if (!user)
     return false;

     else if (password == user -> getPassword() ){
        user-> setStatus ("online");



        return true;
     }

     return false;
}

bool UserManagement :: logoutUser (const string& username ){
    int index = hashFunction (username);

    User* user = searchUserInList(hashTable[index],username);

    if (!user)
        return false;

    user -> setStatus ("offline");

    return true;
}

  bool UserManagement::resetPassword(const string &username, const string &newPassword){

    int index = hashFunction (username);

    User* user = searchUserInList (hashTable[index] , username);

    if (!user)
        return false;

    user -> setPassword (newPassword);

    return true;

  }

void UserManagement :: displayAllUsers () const{

    User* curr;

    for (int i =  0; i < TABLE_SIZE ; i++){
      curr = hashTable[i];

      while (curr){
        curr -> display ();
        curr = curr -> getNext();
      }
    }

}
/////////////////////////////////////////////////////////////////////////////////
void UserManagement::displayUserProfile(const string &username) const
{
    int index = hashFunction(username);
    User *user = searchUserInList(hashTable[index], username);

    if (!user)
    {
        cout << "User not found.\n";
        return;
    }

    user->display();
}

bool UserManagement::deleteUser(const string &username)
{
    int index = hashFunction(username);
    User *curr = hashTable[index];
    User *prev = nullptr;

    while (curr)
    {
        if (curr->getUsername() == username)
        {
            if (prev)
                prev->setNext(curr->getNext());
            else
                hashTable[index] = curr->getNext();

            delete curr;
            return true;
        }

        prev = curr;
        curr = curr->getNext();
    }

    return false;
}

bool UserManagement::updateProfile(const string &username, const string newCity, const string newStatus)
{
    int index = hashFunction(username);
    User *user = searchUserInList(hashTable[index], username);
    if (!user) return false;

    user->setCity(newCity);
    user->setStatus(newStatus);
    return true;
}

string UserManagement :: getStatusforclass(const string& username)const{
    int index = hashFunction(username);

    User* user  =searchUserInList (hashTable[index] , username);

    if (!user){
        return "User Deleted Account";
    }

    return user -> getStatus();
}

