#include "advert_dialog.h"
#include "ui_advert.h"
#include "mainwindow.h"
#include <QLineEdit>


Advert_Dialog::Advert_Dialog(QMainWindow *parent, int id) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    advert = new Advert();
    this->id = id;
}

Advert_Dialog::Advert_Dialog(QMainWindow *parent, Advert* advert, int id) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->advert = advert;
    this->id = id;
}

Advert_Dialog::~Advert_Dialog()
{
    delete ui;
}

Advert* Advert_Dialog::GetAdvert() {
    if (ui->rdb_sale->isChecked())
        advert->SetIsSaleRent(0);
    else if (ui->rdb_rent->isChecked())
        advert->SetIsSaleRent(1);

    QString type = ui->cbx_type->currentText();
    type.toLower();
    type[0].toUpper();
    advert->SetId(id);
    advert->SetDateCreation(QDate::currentDate());
    advert->SetType(type);
    advert->SetNum(ui->le_num->text());
    advert->SetStreet(ui->le_street->text());
    advert->SetCity(ui->le_city->text());
    advert->SetZip(ui->le_zip->text());

    advert->SetDescription(ui->te_description->toPlainText());

    advert->SetPrice(ui->le_price->text().toInt());
    advert->SetRooms(ui->spb_rooms->value());
    advert->SetSize(ui->le_size->text().toInt());

    return advert;
}

void Advert_Dialog::on_le_size_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_size->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_size->setText(tmp);
            }
        }
    }
}

void Advert_Dialog::on_le_price_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_price->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_price->setText(tmp);
            }
        }
    }
}

void Advert_Dialog::on_btn_ok_clicked()
{
    bool test = true;
    bool test_empty = false;
    bool test_valide = false;

    QMessageBox msgBox;
    QString error = "";
    QString error_empty = "";
    QString error_valide = "";

    if (!test_empty) {
        error_empty.append("Champ(s) vide(s):\n");
        if (ui->rdb_sale->isChecked() == false && ui->rdb_rent->isChecked() == false) {
            error_empty.append("        Vente ou location\n");
            test_empty = true;
        }
        if (ui->cbx_type->currentText().isEmpty()) {
            error_empty.append("        Type\n");
            test_empty = true;
        }
        if (ui->le_size->text().isEmpty()) {
            error_empty.append("        Surface/Superficie\n");
            test_empty = true;
        }
        if (ui->te_description->toPlainText().isEmpty()) {
            error_empty.append("        Description\n");
            test_empty = true;
        }
        if (ui->le_num->text().isEmpty()) {
            error_empty.append("        Numéro\n");
            test_empty = true;
        }
        if (ui->le_street->text().isEmpty()) {
            error_empty.append("        Rue\n");
            test_empty = true;
        }
        if (ui->le_city->text().isEmpty()) {
            error_empty.append("        Ville\n");
            test_empty = true;
        }
        if (ui->le_zip->text().isEmpty()) {
            error_empty.append("        Code\n");
            test_empty = true;
        }
    }

    if (!test_valide) {
        error_valide.append("Champ(s) invalide(s):\n");
        if (!isLEValide(ui->le_size)) {
            error_valide.append("       Superficie/Surface\n");
            test_valide = true;
        }
        if (ui->spb_rooms->value() == 0) {
            error_valide.append("       Nombre de pièces\n");
            test_valide = true;
        }
        if (!isLEValide(ui->le_price)) {
            error_valide.append("       Prix\n");
            test_valide = true;
        }
    }


    if (test_empty) {
        error.append(error_empty+"\n");
        test = false;
    }
    if (test_valide) {
        error.append(error_valide);
        test = false;
    }
    if (!test)
        msgBox.critical(this, "Erreur", error);
    else
        this->accept();
}

bool Advert_Dialog::isLEValide(QLineEdit *le) {
    bool test = true;
    int i;
    for(i=0; i<le->text().length(); i++) {
        if(! le->text()[i].isDigit())
            test = false;
    }
    return test;
}

void Advert_Dialog::on_btn_cancel_clicked()
{
    this->reject();
}

void Advert_Dialog::on_btn_photo_princ_clicked()
{
    if (nb_photo_princ < 1) {
        QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir image ..."),QDir::homePath(),tr("Image (*.png | *.jpg | *.jpeg)"));
        QMessageBox msg;
        if(file.isEmpty()) {
            return;
        }

        QFileInfo fileInfo(file);
        QFile::copy(fileInfo.filePath(), QDir::currentPath()+"/images/"+fileInfo.fileName());
        advert->SetPhotoPrinc(QDir::currentPath()+"/images/"+fileInfo.fileName());

        nb_photo_princ = nb_photo_princ + 1;

        QPixmap p(advert->GetPhotoPrinc());
        // get label dimensions

        QLabel* label_photo = new QLabel();
        label_photo->resize(75, 75);
        label_photo->setPixmap(p.scaled(label_photo->width(),label_photo->height(),Qt::KeepAspectRatio));
        ui->hl_photo_princ->addWidget(label_photo);
    } else
        return;

}

void Advert_Dialog::on_btn_photo_sup_clicked()
{
    if (nb_photo_supp < 3) {
        QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir image ..."),QDir::homePath(),tr("Image (*.png | *.jpg | *.jpeg)"));
        QMessageBox msg;
        if(file.isEmpty()) {
            return;
        }

        QPixmap* p;
        QFileInfo fileInfo(file);
        QFile::copy(fileInfo.filePath(), QDir::currentPath()+"/images/"+fileInfo.fileName());
        if (nb_photo_supp == 0) {
            advert->SetPhotoSup1(QDir::currentPath()+"/images/"+fileInfo.fileName());
            p = new QPixmap(advert->GetPhotoSup1());
        } else if (nb_photo_supp == 1) {
            advert->SetPhotoSup2(QDir::currentPath()+"/images/"+fileInfo.fileName());
            p = new QPixmap(advert->GetPhotoSup2());
        } else if (nb_photo_supp == 2) {
            advert->SetPhotoSup3(QDir::currentPath()+"/images/"+fileInfo.fileName());
            p = new QPixmap(advert->GetPhotoSup3());
        }

        nb_photo_supp = nb_photo_supp + 1;

        // get label dimensions

        QLabel* label_photo = new QLabel();
        label_photo->resize(75, 75);
        label_photo->setPixmap(p->scaled(label_photo->width(),label_photo->height(),Qt::KeepAspectRatio));
        ui->hl_photo_sup->addWidget(label_photo);
    } else
        return;
}
