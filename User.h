#pragma once
#include <string>
#include <fstream>


class User
{
private:
    std::string _login;
    std::string _name;
    std::string _password;
public:
    User() = default;
    User(const std::string& name, const std::string& login, const std::string& password);

    void setName(const std::string& name);
    void setLogin(const std::string& login);
    void setPassword(const std::string& password);
    void writeFile(const std::string& filename, const std::string& name, const std::string& login, const std::string& password);
    void writeFileUS(const std::string& filename, const std::string& login, const std::string& password);

    std::string getName() const;
    std::string getLogin() const;
    std::string getPassword() const;

    ~User() = default;
};