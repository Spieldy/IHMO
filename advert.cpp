#include "advert.h"
#include "ui_advert.h"

Advert::Advert(QMainWindow *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Advert::~Advert()
{
    delete ui;
}
