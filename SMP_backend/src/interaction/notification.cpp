#include "interaction/notification.hpp"

unsigned long long Notification::nextNID = 1;

Notification::Notification()
    : n_id(nextNID++), r_id(0), s_id(0), type(NotificationType::System), desc(""), timeStamp(std::time(nullptr)), isRead(false) {}

Notification::Notification(unsigned long long rid, unsigned long long sid, NotificationType t, const std::string &d)
    : n_id(nextNID++), r_id(rid), s_id(sid), type(t), desc(d), timeStamp(std::time(nullptr)), isRead(false) {}

std::string Notification::typetostring(NotificationType t)
{
    switch (t)
    {
    case NotificationType::Like:
        return "like";
    case NotificationType::Comment:
        return "comment";
    case NotificationType::Follow:
        return "follow";
    case NotificationType::Message:
        return "message";
    case NotificationType::Mention:
        return "mention";
    case NotificationType::System:
        return "system";
    }
    return "system";
}

NotificationType Notification::stringtotype(const std::string &s)
{
    if (s == "like")
    {
        return NotificationType::Like;
    }
    else if (s == "comment")
    {
        return NotificationType::Comment;
    }
    else if (s == "message")
    {
        return NotificationType::Message;
    }
    else if (s == "mention")
    {
        return NotificationType::Mention;
    }
    else if (s == "follow")
    {
        return NotificationType::Follow;
    }
    else if (s == "system")
    {
        return NotificationType::System;
    }
    return NotificationType::System;
}

unsigned long long Notification::getID() const { return n_id; }
unsigned long long Notification::getReciever() const { return r_id; }
unsigned long long Notification::getSender() const { return s_id; }
NotificationType Notification::getType() const { return type; }
std::string Notification::getDescription() const { return desc; }
std::time_t Notification::getTimeStamp() const { return timeStamp; }
bool Notification::getReadStatus() const { return isRead; }

void Notification::markAsRead() { isRead = true; }

json Notification::toJSON() const
{
    return json{
        {"id", n_id},
        {"reciever", r_id},
        {"sender", s_id},
        {"type", typetostring(type)},
        {"description", desc},
        {"timestamp", timeStamp},
        {"readstatus", isRead}};
}

Notification Notification::fromJSON(const json &j)
{
    Notification n;
    n.n_id = j.at("id").get<unsigned long long>();
    n.r_id = j.at("reciever").get<unsigned long long>();
    n.s_id = j.at("sender").get<unsigned long long>();
    n.type = stringtotype(j.at("type").get<std::string>());
    n.desc = j.at("description").get<std::string>();
    n.timeStamp = j.at("timestamp").get<std::time_t>();
    n.isRead = j.at("readstatus").get<bool>();

    if (n.n_id >= nextNID)
    {
        nextNID = n.n_id + 1;
    }

    return n;
}

// Notification Manager class defination

