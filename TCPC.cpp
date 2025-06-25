#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Chat.h"
using namespace std;
 
#define MESSAGE_LENGTH 1024
#define PORT 50000
 
int socket_file_descriptor, connection;
struct sockaddr_in serveraddress, client;
char buff[MESSAGE_LENGTH];
string name, login, password, recipient, text;

void print_menu()
{
    cout << "-----------------------------------------\n";
    cout << "|     Войдите или авторизируйтесь       |\n";
    cout << "-----------------------------------------\n";
    cout << "| 1. Регистрация                        |\n";
    cout << "| 2. Авторизация                        |\n";
    cout << "| 3. Отправить сообщение пользователю   |\n";
    cout << "| 4. Отправить сообщение всем           |\n";
    cout << "| 5. Просмотр чата                      |\n";
    cout << "| 6. Просмотр личных сообщений          |\n";
    cout << "| 7. Список пользователей               |\n";
    cout << "| Для выхода из приложения введите 'q'. |\n";
    cout << "-----------------------------------------\n";
    cout << "Выберите действие: ";
}

int main()
{
    Chat chat;
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1)
    {
        cout << "Не удалось создать сокет!" << endl;
        exit(1);
    }
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1)
    {
        cout << "Соединение с сервером не удалось.!" << endl;
        exit(1);
    }
    cout << "Соединение с севрером по порту: " << PORT << endl;
    // Взаимодействие с сервером.
    while(1)
    {
        memset(buff, 0, sizeof(buff));      // очистка буффера
        print_menu();                       // осносное меню

        string command;
        cin >> command;
        cin.ignore();
        if (command == "1")                 // регистрация
        {
            cout << "Введите имя: ";
            getline(cin, name);
            cout << "Введите логин: ";
            getline(cin, login);
            cout << "Введите пароль: ";
            getline(cin, password);
            string message = "reg:" + name + ":" + login + ":" + password;
            write(socket_file_descriptor, message.c_str(), message.size());
            memset(buff, 0, sizeof(buff));
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "2")            // авторизация
        {
            cout << "Введите логин: ";
            getline(cin, login);
            cout << "Введите пароль: ";
            getline(cin, password);
            string message = "auth:" + login + ":" + password;
            write(socket_file_descriptor, message.c_str(), message.size());
            memset(buff, 0, sizeof(buff));
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "3")            // сообщение пользователю
        {
            cout << "Введите логин получателя: ";
            getline(cin, recipient);
            cout << "Введите текст сообщения: ";
            getline(cin, text);
            string message = "text:" + recipient + ":" + text;
            write(socket_file_descriptor, message.c_str(), message.size());
            memset(buff, 0, sizeof(buff));
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "4")            // сообщение всем
        {
            cout << "Введите текст сообщения: ";
            getline(cin, text);
            string message = "teto:" + text;
            write(socket_file_descriptor, message.c_str(), message.size());
            memset(buff, 0, sizeof(buff));
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "5")            // просмотр чата
        {
            string message = "chat";
            write(socket_file_descriptor, message.c_str(), message.size());
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "6")            // личные сообщения
        {
            string message = "pm";
            write(socket_file_descriptor, message.c_str(), message.size());
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "7")            // просмотр пользователей
        {
            string message = "allUser";
            write(socket_file_descriptor, message.c_str(), message.size());
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
        }
        else if (command == "q")            // выход
        {
            string message = "quit";
            write(socket_file_descriptor, message.c_str(), message.size());
            read(socket_file_descriptor, buff, sizeof(buff));
            cout << buff << endl;
            break;
        }
        else
        {
            cout << "Неизвестная команда" << endl;
        }

    }
    close(socket_file_descriptor);
    return 0;
}