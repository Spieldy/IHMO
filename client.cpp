#include "client.h"

int Client::GetId()
{
    return id;
}

void Client::SetId(int value)
{
    id = value;
}

QString Client::GetMail()
{
    return mail;
}

void Client::SetMail(QString value)
{
    mail = value;
}

QString Client::GetTel()
{
    return tel;
}

void Client::SetTel(QString value)
{
    tel = value;
}

QString Client::GetSurname()
{
    return surname;
}

void Client::SetSurname(QString value)
{
    surname = value;
}

QString Client::GetName()
{
    return name;
}

void Client::SetName(QString value)
{
    name = value;
}

Client::Client()
{

}

Client::Client(QString name, QString surname, QString tel, QString mail)
{
    this->name = name;
    this->surname = surname;
    this->tel = tel;
    this->mail = mail;
}
