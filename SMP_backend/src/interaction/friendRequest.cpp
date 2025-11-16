#include "interaction/friendRequest.hpp"

FriendRequest::FriendRequest() : r_id(0), s_id(0), s(RequestStatus::PENDING), timeStamp((std::time(nullptr))) {}
FriendRequest::FriendRequest(unsigned long long sid, unsigned long long rid)
    : r_id(rid), s_id(sid), s(RequestStatus::PENDING), timeStamp((std::time(nullptr))) {}

unsigned long long FriendRequest::getSenderID() const
{
    return s_id;
}

unsigned long long FriendRequest::getRecieverID() const
{
    return r_id;
}

RequestStatus FriendRequest::getStatus() const
{
    return s;
}

std::time_t FriendRequest::getTimeStamp() const
{
    return timeStamp;
}

void FriendRequest::accept()
{
    s = RequestStatus::ACCEPTED;
}
void FriendRequest::reject()
{
    s = RequestStatus::REJECTED;
}
void FriendRequest::cancel()
{
    s = RequestStatus::CANCELLED;
}

json FriendRequest::toJSON() const
{
    return json{
        {"sender", s_id},
        {"reciever", r_id},
        {"status", statusToString(s)},
        {"timestamp", timeStamp}};
}

FriendRequest FriendRequest::fromJSON(const json &j)
{
    FriendRequest fr;
    fr.s_id = j.at("sender").get<unsigned long long>();
    fr.r_id = j.at("reciever").get<unsigned long long>();
    fr.s = stringToType(j.at("status").get<std::string>());
    fr.timeStamp = j.at("timestamp").get<std::time_t>();

    return fr;
}

// Friend Request Manager implementation