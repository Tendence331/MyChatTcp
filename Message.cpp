#include "Message.h"
#include <string>

using namespace std;

Message::Message(const string& from, const string& to, const string& text)
    : _from(from), _to(to), _text(text) {}

string Message::getSender() const {
    return _from;
}

string Message::getRecipient() const {
    return _to;
}

string Message::getText() const {
    return _text;
}
