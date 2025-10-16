#pragma once

#include <string>
#include <ctime>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Message
{
private:
    unsigned long long m_id;

    std::string sender;
    std::string reciever;
    std::string text;
    std::time_t timeStamp;
    bool isRead;

    static unsigned long long nextMID;
public:
    Message();
    Message(const std::string &s, const std::string &r, const std::string &t);

    unsigned long long getID() const;
    std::string getSender() const;
    std::string getReciever() const;
    std::string getText() const;
    std::time_t getTimeStamp() const;
    bool getIsRead() const;

    void setID(unsigned long long newID);
    void setSender(std::string &s);
    void setReciever(std::string &r);
    void setText(std::string &t);
    void setTimeStamp(std::time_t ts);
    void setIsRead(bool ir);

    void markIsRead();

    json toJSON() const;
    static Message fromJSON(const json &j);

    std::string format() const;

    bool operator==(const Message &other) const { return this->m_id == other.m_id; }
};
