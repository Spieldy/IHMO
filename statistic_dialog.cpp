#include "statistic_dialog.h"
#include "ui_statistic.h"
#include "mainwindow.h"

Statistic_Dialog::Statistic_Dialog(QMainWindow *parent, int saled, int rented, int sale, int rent, int nb_client) : QDialog(parent), ui(new Ui::StatisticDialog)
{
    ui->setupUi(this);
    ui->lbl_current_sale->setText(QString::number(sale));
    ui->lbl_current_rent->setText(QString::number(rent));
    ui->lbl_current_advert->setText(QString::number(rent+sale));
    ui->lbl_last_sale->setText(QString::number(saled));
    ui->lbl_last_rent->setText(QString::number(rented));
    ui->lbl_last_advert->setText(QString::number(rented+saled));
    ui->lbl_nb_client->setText(QString::number(nb_client));
}

Statistic_Dialog::~Statistic_Dialog()
{
    delete ui;
}
