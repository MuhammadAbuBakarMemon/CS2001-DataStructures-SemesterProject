#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

struct Post {
    unsigned long long id;
    unsigned long long authorID;
    string authorUsername;
    string content;
    time_t timestamp;

    static unsigned long long nextPostID;

    
