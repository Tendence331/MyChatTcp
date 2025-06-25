#include "Chat.h"
#include <iostream>
#include <string>
using namespace std;

void Chat::menu()
{
    while (true)
    {
        cout << "---------------------------------------\n";
        cout << "|     Войдите или авторизируйтесь     |\n";
        cout << "---------------------------------------\n";
        cout << "| 1. Регистрация - [ reg ]            |\n";
        cout << "| 2. Авторизация - [ auth ]           |\n";
        cout << "| Для выхода из приложения введите '0'|\n";
        cout << "---------------------------------------\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;

        // Очистка буфера
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0)
        {
            cout << "Выход из программы.\n";
            break;
        }
        User us;
        string name, login, password;

        switch (choice)
        {
        case 1:
            cout << "------------ Регистрация --------------\n";
            cout << "Введите имя: ";
            getline(cin, name);
            cout << "Введите логин: ";
            getline(cin, login);
            cout << "Введите пароль: ";
            getline(cin, password);
            registerUser(name, login, password);
            us.writeFile("USERS.txt", name, login, password);
            break;
        case 2:
            cout << "------------ Авторизация --------------\n";
            cout << "Введите логин: ";
            getline(cin, login);
            cout << "Введите пароль: ";
            getline(cin, password);
            if(loginUser(login, password))
            {
                userMenu();
            }
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }

    }
}

void Chat::userMenu()
{
    if (!_currentUser)
    {
        cout << "Вы не авторизированы!" << endl;
        return;
    }
    while (true)
    {
        cout << "---------------------------------------\n";
        activeUser();
        cout << "---------------------------------------\n";
        cout << "| 1. Отправить сообщение пользователю |\n";
        cout << "| 2. Отправить сообщение всем         |\n";
        cout << "| 3. Просмотр чата                    |\n";
        cout << "| 4. Просмотр личных сообщений        |\n";
        cout << "| 5. Список пользователей             |\n";
        cout << "| Выход из системы - нажмите 0        |\n";
        cout << "---------------------------------------\n";

        int choice;
        cin >> choice;

        // Очистка буфера
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0)
        {
            _currentUser = nullptr;
            cout << "Выход из системы.\n";
            break;
        }
        string text, recipient;

        switch (choice)
        {
        case 1:
            cout << "--------- Отправка сообщения ----------\n";
            cout << "Введите логин получателя: ";
            getline(cin, recipient);
            cout << "Введите текст сообщения: ";
            getline(cin, text);
            sendToUser(recipient, text);
            break;
        case 2:
            cout << "------------- Общий чат ---------------\n";
            cout << "Введите текст сообщения: ";
            getline(cin, text);
            sendToAll(text);
            break;
        case 3:
            cout << "------------- Просмотр чата -----------\n";
            viewMessages();
            break;
        case 4:
            cout << "----------- Личные сообщения ----------\n";
            messagePM();
            break;
        case 5:
            cout << "--- Зарегистрированные пользователи ---\n";
            displayUsers();
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }
    
}

void Chat::activeUser()
{
    for(const auto& user : _users)
    {
        if (_currentUser)
        {
            if (_currentUser->getLogin() == user->getLogin())
            {
                cout << "[ " << user->getName()<< " ] активный пользователь" << endl;
            }
        }
    }
}

void Chat::registerUser(const string &name, const string &login, const string &password)
{
    for (const auto& user : _users)
    {
        if (user->getLogin() == login)
        {
            cout << "Пользователь с логином " << login << " уже существует!" << endl;
        }
    }

    _users.push_back(make_shared<User>(name, login, password));
    cout << "Пользователь [" << name << "] зарегистрирован!" << endl;
}

bool Chat::loginUser(const string& login, const string& password)
{
    for (const auto& user : _users)
    {
        if (user->getLogin() == login && user->getPassword() == password)
        {
            _currentUser = user;
            cout << "Пользователь [" << user->getName() << "] успешно вошел" << endl;
            return true;
        }
    }

    cout << "Ошибка: неправильный логин или пароль." << endl;
    return false;
}

void Chat::sendToUser(const string& to, const string& text)
{
    if (!_currentUser)
    {
        cout << "Вы не авторизированы!" << endl;
        return;
    }
    
    Message msg(_currentUser->getLogin(), to, text);
    _messages.emplace_back(msg);
    cout << "Сообщение отправлено пользователю: " << to << endl;
}

void Chat::sendToAll(const string& text)
{
    if (!_currentUser)
    {
        cout << "Вы не авторизированы!" << endl;
        return;
    }

    Message msg(_currentUser->getLogin(), "all", text);
    _messages.push_back(msg);
    cout << "Сообщение отправлено всем" << endl;
}

std::string Chat::viewMessages() const
{
    if (!_currentUser)
    {
        return "Вы не авторизированы!";
    }
    if (_messages.empty())
    {
        return "Чат пустой.";
    }
    string result;
    for (const auto& msg : _messages)
    {
        if (_currentUser && (msg.getRecipient() == "all" ))
        {
            result += "[" + msg.getSender() + "] >> " + msg.getText() + '\n';
        }
    }
    return result;
}

std::string Chat::messagePM() const
{
    if (!_currentUser)
    {
        return "Вы не авторизированы!";
    }
    if (_messages.empty())
    {
        return "Сообщений нет.";
    }
    string result;
    for (const auto& msg : _messages)
    {
        if (_currentUser && (msg.getRecipient() == _currentUser->getLogin()))
        {
            result += "[" + msg.getSender() + "] >> " + msg.getText() + '\n';
        }
    }
    return result;
}


std::string Chat::displayUsers() const
{
    if (!_currentUser)
    {
        return "Вы не авторизированы!";

    }
    
    if (_users.empty())
    {
        return "Нет зарегистрированных пользователей.";
    }
    string result;
    for (const auto& user : _users)
    {
        result += "Пользователь: Имя: [ " + user->getName() + " ] Логин: [ " + user->getLogin() + " ]" + '\n';
    }
    return result;
}