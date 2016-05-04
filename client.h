#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
   QString name;
   QString surname;
   QString tel;
   QString mail;
   int id;

public:
    Client();
    Client(QString name, QString surname, QString tel, QString mail);
    int GetId();
    void SetId(int value);
    QString GetMail();
    void SetMail(QString value);
    QString GetTel();
    void SetTel(QString value);
    QString GetSurname();
    void SetSurname(QString value);
    QString GetName();
    void SetName(QString value);
};

#endif // CLIENT_H
