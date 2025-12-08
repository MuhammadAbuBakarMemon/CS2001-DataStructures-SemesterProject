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

    Post() : id(0), authorID(0), timestamp(0) {}

    Post(unsigned long long uid, string uname, string text) 
        : id(nextPostID++), authorID(uid), authorUsername(uname), content(text), timestamp(time(nullptr)) {}

    json toJSON() const {
        return json{
            {"id", id},
            {"authorID", authorID},
            {"authorUsername", authorUsername},
            {"content", content},
            {"timestamp", timestamp}
        };
    }

    static Post fromJSON(const json& j) {
        Post p;
        p.id = j.at("id").get<unsigned long long>();
        p.authorID = j.at("authorID").get<unsigned long long>();
        p.authorUsername = j.at("authorUsername").get<string>();
        p.content = j.at("content").get<string>();
        p.timestamp = j.at("timestamp").get<time_t>();
        
        if (p.id >= nextPostID) {
            nextPostID = p.id + 1;
        }
        return p;
stID = 1;
