#ifndef CLIENTS_DIALOG_H
#define CLIENTS_DIALOG_H

#include "ui_clients.h"
#include <QString>
#include <string>
#include "client.h"
#include "mainwindow.h"

namespace Ui {
class Clients_Dialog;
}

class Clients_Dialog : public QDialog
{
public:
    Clients_Dialog(QMainWindow *parent = 0, QList<Client*> client_tab = QList<Client*>());
    ~Clients_Dialog();

    Ui::ClientDialog *ui;

private:
    QStandardItemModel* model;
    bool FillAllClients(QList<Client*> tab) ;

};

#endif // CLIENTS_DIALOG_H
