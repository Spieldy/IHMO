#include "clients_dialog.h"

Clients_Dialog::Clients_Dialog(QMainWindow *parent, QList<Client*> client_tab) : QDialog(parent), ui(new Ui::ClientDialog)
{
    ui->setupUi(this);

    model = new QStandardItemModel(client_tab.count(),5,this);
    if (FillAllClients(client_tab)) {
        ui->table_clients->setModel(model);
        ui->table_clients->resizeRowsToContents();
        ui->table_clients->resizeColumnsToContents();
        ui->table_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

Clients_Dialog::~Clients_Dialog()
{
    delete ui;
}

bool Clients_Dialog::FillAllClients(QList<Client*> tab) {
    int i;
    model->clear();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Id")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Nom")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Prénom")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Téléphone")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Mail")));
    for(i=0; i<tab.count(); ++i )
    {
        QStandardItem *id = new QStandardItem(QString(tab[i]->GetId()));
        model->setItem(i,0,id);
        QStandardItem *name = new QStandardItem(tab[i]->GetName());
        model->setItem(i,1,name);
        QStandardItem *surname = new QStandardItem(tab[i]->GetSurname());
        model->setItem(i,2,surname);
        QStandardItem *telephone = new QStandardItem(tab[i]->GetTel());
        model->setItem(i,3,telephone);
        QStandardItem *mail = new QStandardItem(tab[i]->GetMail());
        model->setItem(i,4,mail);
    }

    ui->table_clients->resizeRowsToContents();
    ui->table_clients->resizeColumnsToContents();
    ui->table_clients->horizontalHeader()->setStretchLastSection(true);
    ui->table_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    return true;
}
