#pragma once
#include <string>

class Message
{
private:
    std::string _from;
    std::string _to;
    std::string _text;
public:
    Message(const std::string& from, const std::string& to, const std::string& text);

    std::string getSender() const;
    std::string getRecipient() const;
    std::string getText() const;
};