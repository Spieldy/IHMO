#ifndef ADVERT_DIALOG_H
#define ADVERT_DIALOG_H

#include <QtWidgets>
#include "ui_advert.h"
#include "advert.h"
#include <QString>
#include <string>
#include "client.h"

using namespace std;

namespace Ui {
class Advert_Dialog;
}

class Advert_Dialog : public QDialog
{
    Q_OBJECT

    Advert *advert;
    Client* client;
    bool isLEDigitValide(QLineEdit *le);
    bool isLECharValide(QLineEdit *le);
    int id_advert;
    int id_client;
    int nb_photo_supp = 0;
    int nb_photo_princ = 0;
    QLabel* photo_princ;
    QLabel* photo_sup1;
    QLabel* photo_sup2;
    QLabel* photo_sup3;
public:
    Advert_Dialog(QMainWindow *parent = 0, int id_advert = 0);
    Advert_Dialog(QMainWindow *parent = 0, Advert* advert = new Advert());
    Advert_Dialog(QMainWindow *parent = 0, Client* client = new Client(), Advert* advert = new Advert());

    ~Advert_Dialog();

    Advert* GetAdvert();
    Client* GetClient();
    bool hasClient();

    Ui::AdvertDialog *ui;

signals:

public slots:
private slots:
    void on_le_size_textEdited(const QString &arg1);
    void on_le_price_textEdited(const QString &arg1);
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();
    void on_btn_photo_princ_clicked();
    void on_btn_photo_sup_clicked();
    void on_btn_suppr_princ_clicked();
    void on_btn_suppr_sup_clicked();
    void on_le_client_name_textEdited(const QString &arg1);
    void on_le_client_surname_textEdited(const QString &arg1);
    void on_le_client_tel_textEdited(const QString &arg1);
};

#endif // ADVERT_DIALOG_H
