#ifndef ADVERT_DIALOG_H
#define ADVERT_DIALOG_H

#include <QtWidgets>
#include "ui_advert.h"
#include "advert.h"
#include <QString>
#include <string>

using namespace std;

namespace Ui {
class Advert_Dialog;
}

class Advert_Dialog : public QDialog
{
    Q_OBJECT

    Advert *advert;
    bool isLEValide(QLineEdit *le);
public:
    Advert_Dialog(QMainWindow *parent = 0, int id = 0);
    Advert_Dialog(QMainWindow *parent = 0, Advert* advert = new Advert(), int id = 0);
    ~Advert_Dialog();

    Advert* GetAdvert();

    Ui::Dialog *ui;

private:
    int id;
    int nb_photo_supp = 0;
    int nb_photo_princ = 0;

signals:

public slots:
private slots:
    void on_le_size_textEdited(const QString &arg1);
    void on_le_price_textEdited(const QString &arg1);
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();
    void on_btn_photo_princ_clicked();
    void on_btn_photo_sup_clicked();
};

#endif // ADVERT_DIALOG_H
