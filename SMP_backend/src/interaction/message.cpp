#include "interaction/message.hpp"

Message::Message()
    : m_id(nextMID++), timeStamp(std::time(nullptr)), isRead(false) {}
Message::Message(const std::string &s, const std::string &r, const std::string &t)
    : m_id(nextMID++), sender(s), reciever(r), text(t), timeStamp(std::time(nullptr)), isRead(false) {}

unsigned long long Message::getID() const { return m_id; }
std::string Message::getSender() const { return sender; }
std::string Message::getReciever() const { return reciever; }
std::string Message::getText() const { return text; }
std::time_t Message::getTimeStamp() const { return timeStamp; }
bool Message::getIsRead() const { return isRead; }

void Message::setID(unsigned long long newID) { m_id = newID; }
void Message::setSender(std::string &s) { sender = s; }
void Message::setReciever(std::string &r) { reciever = r; }
void Message::setText(std::string &t) { text = t; }
void Message::setTimeStamp(std::time_t ts) { timeStamp = ts; }
void Message::setIsRead(bool ir) { isRead = ir; }

void Message::markIsRead() { isRead = true; }

json Message::toJSON() const
{
    return json{
        {"ID", m_id},
        {"sender", sender},
        {"reciever", reciever},
        {"text", text},
        {"timestamp", timeStamp},
        {"isRead", isRead}};
}

Message Message::fromJSON(const json &j)
{
    Message m;
    m.setID(j.at("ID").get<unsigned long long>());
    m.setSender(j.at("sender").get<std::string>());
    m.setReciever(j.at("reciever").get<std::string>());
    m.setText(j.at("text").get<std::string>());
    m.setTimeStamp(j.at("timestamp").get<std::time_t>());
    m.setIsRead(j.at("isRead").get<bool>());

    if (m.getID() >= nextMID)
    {
        nextMID = m.getID() + 1;
    }

    return m;
}

std::string Message::format() const
{
    char buff[26];
    std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", std::localtime(&timeStamp));
    return "[" + std::string(buff) + "] " + sender + " -> " + reciever + ": " + text;
}

bool Message::operator==(const Message &other) const { return this->m_id == other.m_id; }