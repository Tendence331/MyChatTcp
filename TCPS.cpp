#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Chat.h"
using namespace std;
 
#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 50000 // Будем использовать этот номер порта
 
struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;
char buff[MESSAGE_LENGTH];
string name, login, password, recipient, text;
 
int main()
{
    Chat chat;
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sockert_file_descriptor == -1)
    {
        cout << "Не удалось создать сокет.!" << endl;
        exit(1);
    }
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    bind_status = ::bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(bind_status == -1)
    {
        cout << "Привязка сокета не удалась.!" << endl;
        exit(1);
    }
    connection_status = listen(sockert_file_descriptor, 5);
    if(connection_status == -1)
    {
        cout << "Сокет не может прослушивать новые соединения.!" << endl;
        exit(1);
    }
    else
    {
        cout << "Сервер ожидает нового соединения: " << endl;
    }
    cout << "Сервер работает на порту: " << PORT << endl;
    // Взаимодействие с клиентом.
    while(1)
    {
        length = sizeof(client);
        connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
        if(connection == -1)
        {
            cout << "Сервер не может принять данные от клиента.!" << endl;
            exit(1);
        }
        bool client_connect = true;
        while (client_connect)
        {
            memset(buff, 0, sizeof(buff));              // чистим буффер перед новым запросом
            read(connection, buff, sizeof(buff));       // читаем сообщение от клиента
            cout << "Данные полученные от клиента: " <<  buff << endl;
            string mess(buff);                          // приведение к строке
            string reply;
            if (mess == "quit")
            {
                cout << "Клиент вышел" << endl;
                reply = "Выход с сервера";
                write(connection, reply.c_str(), reply.size());
                close(connection);
                client_connect = false;
            }
            else if (mess.substr(0, 4) == "reg:")
            {
                size_t pos1 = mess.find(':');
                size_t pos2 = mess.find(':', pos1 + 1);
                size_t pos3 = mess.find(':', pos2 + 1);

                name = mess.substr(pos1 + 1, pos2 - pos1 - 1);
                login = mess.substr(pos2 + 1, pos3 - pos2 - 1);
                password = mess.substr(pos3 + 1);
                chat.registerUser(name, login, password);
                reply = "Пользователь [" + login + "] зарегистрирован!";
                write(connection, reply.c_str(), reply.size());
            }
            else if (mess.substr(0, 5) == "auth:")
            {
                size_t pos1 = mess.find(':');
                size_t pos2 = mess.find(':', pos1 + 1);
                login = mess.substr(pos1 + 1, pos2 - pos1 - 1);
                password = mess.substr(pos2 + 1);
                if (chat.loginUser(login, password))
                {
                    reply = "Пользователь [" + login + "] успешно вошел";
                }
                else
                {
                    reply = "Авторизация пользователя: " + login + " не удалась!";
                }
                write(connection, reply.c_str(), reply.size());
            }
            else if (mess.substr(0, 5) == "text:")
            {
                size_t pos1 = mess.find(':');
                size_t pos2 = mess.find(':', pos1 + 1);
                recipient = mess.substr(pos1 + 1, pos2 - pos1 - 1);
                text = mess.substr(pos2 + 1);
                chat.sendToUser(recipient, text);
                reply = "Сообщение отправлено пользователю: " + recipient;
                write(connection, reply.c_str(), reply.size());
            }
            else if (mess.substr(0, 5) == "teto:")
            {
                size_t pos1 = mess.find(':');
                text = mess.substr(pos1 + 1);
                chat.sendToAll(text);
                reply = "Сообщение всем: " + text;
                write(connection, reply.c_str(), reply.size());
            }
            else if (mess == "chat")
            {
                reply = chat.viewMessages();
                write(connection, reply.c_str(), reply.size());
            }
            else if (mess == "pm")
            {
                reply = chat.messagePM();
                write(connection, reply.c_str(), reply.size());
            }
            else if (mess == "allUser")
            {
                reply = chat.displayUsers();
                write(connection, reply.c_str(), reply.size());
            }
        }
    }
    close(sockert_file_descriptor);
    return 0;
}