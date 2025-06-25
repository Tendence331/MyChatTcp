#include "User.h"
#include <string>
#include <iostream>
using namespace std;

User::User(const string& name, const string& login, const string& password)
    : _name(name), _login(login), _password(password) {}

void User::setName(const string& name) {
    _name = name;
}

void User::setLogin(const string& login) {
    _login = login;
}

void User::setPassword(const string& password) {
    _password = password;
}

string User::getName() const {
    return _name;
}

string User::getLogin() const {
    return _login;
}

string User::getPassword() const {
    return _password;
}

void User::writeFile(const std::string& filename, const std::string& name, const std::string& login, const std::string& password)
{
    std::fstream file; 

    file.open(filename, std::ios::app | std::ios::out | std::ios::binary);     // открываем файл с аргументами на запись, запись конец файла без удаления, биннарый ввод
    if (!file.is_open())                                        // проверка существует ли файл    
    {
        cout << "Невозможно открыть файл!" << '\n';
        return;
    }
    if (file)
    {
        file << "Имя: " << name << '\n';
        file << "Логин: " << login << '\n'; 
        file << "Пароль: " << password << '\n';
        file << "---------------------------"<< '\n';
        file.close();
    }
}

void User::writeFileUS(const std::string& filename, const std::string& login, const std::string& password)
{

    std::fstream file; 

    file.open(filename, std::ios::app | std::ios::out | std::ios::binary);     // открываем файл с аргументами на запись, запись конец файла без удаления, биннарый ввод
    if (!file.is_open())                                        // проверка существует ли файл    
    {
        cout << "Невозможно открыть файл!" << '\n';
        return;
    }
    if (file)
    {
        file << "Логин: " << login << '\n'; 
        file << "Пароль: " << password << '\n';
        file << "---------------------------"<< '\n';
        file.close();
    }
}