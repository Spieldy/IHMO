#ifndef STATISTIC_DIALOG_H
#define STATISTIC_DIALOG_H

#include "advert.h"
#include "ui_statistic.h"
#include <QString>
#include <string>
#include "client.h"
#include "mainwindow.h"

namespace Ui {
class Statistic_Dialog;
}

class Statistic_Dialog : public QDialog
{
public:
    Statistic_Dialog(QMainWindow *parent = 0, int saled = 0, int rented = 0, int sale = 0, int rent = 0, int nb_client = 0);
    ~Statistic_Dialog();

    Ui::StatisticDialog *ui;

private slots:
    void on_btn_close_clicked();
};

#endif // STATISTIC_DIALOG_H
