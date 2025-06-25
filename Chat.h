#pragma once
#include <list>
#include <string>
#include "User.h"
#include "Message.h"

class Chat
{
private:
    std::list<std::shared_ptr<User>> _users;
    std::list<Message> _messages;
    std::shared_ptr<User> _currentUser;
public:
    Chat() = default;
    ~Chat() = default;
    void menu();                                                                                            // Меню регистрации и авторизации
    void userMenu();                                                                                        // Пользовательское меню
    void activeUser();                                                                                      // Показывает активного пользователя
    void registerUser(const std::string& name, const std::string& login, const std::string& password);      // Регистрация
    bool loginUser(const std::string& login, const std::string& password);                                  // Авторизация
    void sendToUser(const std::string& to, const std::string& text);                                        // Отправка сообщения пользователю
    void sendToAll(const std::string& text);                                                                // Отправка сообщения всем в чат
    std::string viewMessages() const;                                                                       // Просмотр общего чата
    std::string messagePM() const;                                                                          // Просмотр личного сообщения
    std::string displayUsers() const;                                                                       // Просмотр пользователей

};