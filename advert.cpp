#include "advert.h"

Advert::Advert() {}

Advert::Advert(QString type, QString num, QString street, QString city, QString zip, QString description, int size, int rooms, int price)
{
    this->type = type;
    this->num = num;
    this->street = street;
    this->city = city;
    this->zip = zip;
    this->description = description;
    this->size = size;
    this->rooms = rooms;
    this->price = price;
}

int Advert::GetId() {
    return id;
}

void Advert::SetId(int id) {
    this->id = id;
}

QString Advert::GetType() {
    return type;
}

void Advert::SetType(QString type) {
    this->type = type;
}

QString Advert::GetNum() {
    return num;
}

void Advert::SetNum(QString num) {
    this->num = num;
}

QString Advert::GetStreet() {
    return street;
}

void Advert::SetStreet(QString street) {
    this->street = street;
}

QString Advert::GetCity() {
    return city;
}

void Advert::SetCity(QString city) {
    this->city = city;
}

QString Advert::GetZip() {
    return zip;
}

void Advert::SetZip(QString zip) {
    this->zip = zip;
}

QString Advert::GetDescription() {
    return description;
}

void Advert::SetDescription(QString description) {
    this->description = description;
}

int Advert::GetSize() {
    return size;
}

void Advert::SetSize(int size) {
    this->size = size;
}

int Advert::GetRooms() {
    return rooms;
}

void Advert::SetRooms(int rooms) {
    this->rooms = rooms;
}

int Advert::GetPrice() {
    return price;
}

void Advert::SetPrice(int price) {
    this->price = price;
}
