#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "core/user.hpp"
#include "ADT/linked_list.hpp"
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
    }

    string getFormattedTime() const {
        char buffer[80];
        struct tm* timeinfo = localtime(&timestamp);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }
};

unsigned long long Post::nextPostID = 1;

class FeedManager {
private:
    LinkedList<Post> allPosts;
    string filePath;

public:
    FeedManager(const string& path = "data/posts.json") : filePath(path) {
        loadPosts();
    }

    void addPost(User* author, const string& content) {
        if (!author) return;
        Post newPost(author->getID(), author->getUsername(), content);
        allPosts.prepend(newPost);
        savePosts();
    }

    LinkedList<Post*> getFeedForUser(User* viewer) {
        LinkedList<Post*> feed;
        Node<Post>* curr = allPosts.getHead();
        
        while (curr) {
            bool isRelevant = false;
            
            if (curr->data.authorID == viewer->getID()) {
                isRelevant = true;
            } else {
                FollowNode* fNode = viewer->getFollowerSystem().getFollowingHead();
                while (fNode) {
                    if (fNode->user->getID() == curr->data.authorID) {
                        isRelevant = true;
                        break;
                    }
                    fNode = fNode->next;
                }
            }

            if (isRelevant) {
                feed.append(&curr->data);
            }

            curr = curr->next;
        }
        return feed;
    }

    void displayFeed(User* viewer) {
        LinkedList<Post*> feed = getFeedForUser(viewer);
        
        if (feed.isEmpty()) {
            cout << "\nNo posts to show.\n";
            return;
        }

        cout << "\n=== FEED ===\n";
        Node<Post*>* curr = feed.getHead();
        while (curr) {
            Post* p = curr->data;
            cout << "--------------------------------\n";
            cout << "@" << p->authorUsername << " (" << p->getFormattedTime() << ")";
            cout << "\n" << p->content << "\n";
            curr = curr->next;
        }
        cout << "--------------------------------\n";
    }

    bool savePosts() const {
        json jArray = json::array();
        
        Node<Post>* curr = allPosts.getHead();
        while (curr) {
            jArray.push_back(curr->data.toJSON());
            curr = curr->next;
        }

        json j;
        j["posts"] = jArray;

        ofstream out(filePath);
        if (!out.is_open()) return false;
        
        out << setw(4) << j;
        return true;
    }

    bool loadPosts() {
        ifstream in(filePath);
        if (!in.is_open()) return false;

        json j;
        try {
            in >> j;
        } catch (...) { return false; }

        allPosts.clear();
        
        if (j.contains("posts") && j["posts"].is_array()) {
            for (const auto& item : j["posts"]) {
                allPosts.append(Post::fromJSON(item));
            }
        }
        return true;
    }
};
