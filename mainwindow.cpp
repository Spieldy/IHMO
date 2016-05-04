#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "advert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMessageBox msgBox;
    if (Charge()) {
        UpdateTab();
        ui->setupUi(this);
        ui->rdb_last_first->setChecked(true);

        model = new QStandardItemModel(advert_tab.count(),8,this);
        if (FillAllAdvert(advert_tab)) {
            ui->tableView->setModel(model);
            ui->tableView->resizeRowsToContents();
            ui->tableView->resizeColumnsToContents();
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
            msgBox.critical(this, "Erreur", "Problème rencontré lors du remplissage du tableau");
    } else
        msgBox.critical(this, "Erreur", "Problème rencontré lors du chargement des données");
}

MainWindow::~MainWindow()
{
    if(Save()) {
        delete ui;
    }
    else {
        QMessageBox msgBox;
        msgBox.critical(this, "Erreur", "Problème rencontré lors de la sauvegarde");
    }
}

bool MainWindow::FillAllAdvert(QList<Advert*> tab) {
    int i;
    model->clear();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Type")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Prix")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Adresse")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Taille (m2)")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Pièce(s)")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Description")));
    for(i=0; i<tab.count(); ++i )
    {
        QStandardItem *photo = new QStandardItem();
        if (!tab[i]->GetPhotoPrinc().isEmpty()) {
            QPixmap p(tab[i]->GetPhotoPrinc());
            photo->setData(QVariant(p.scaled(75, 75, Qt::KeepAspectRatio)), Qt::DecorationRole);
        }
        model->setItem(i, 0, photo);

        int saleRent  = tab[i]->GetIsSaleRent();
        QStandardItem *isSaleRent = new QStandardItem();
        if (saleRent == 0)
            isSaleRent->setText("Vente");
        else if (saleRent == 1)
            isSaleRent->setText("Location");
        model->setItem(i,1,isSaleRent);

        QStandardItem *type = new QStandardItem(QString(tab[i]->GetType()));
        model->setItem(i,2,type);
        QStandardItem *price = new QStandardItem(QString::number(tab[i]->GetPrice()));
        model->setItem(i,3,price);
        QStandardItem *address = new QStandardItem(QString(tab[i]->GetNum()+", "+tab[i]->GetStreet()+", "+tab[i]->GetCity()+", "+tab[i]->GetZip()));
        model->setItem(i,4,address);
        QStandardItem *size = new QStandardItem(QString::number(tab[i]->GetSize()));
        model->setItem(i,5,size);
        QStandardItem *rooms = new QStandardItem(QString::number(tab[i]->GetRooms()));
        model->setItem(i,6,rooms);
        QStandardItem *description = new QStandardItem(tab[i]->GetDescription());
        model->setItem(i,7,description);
    }

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    return true;
}

bool MainWindow::Charge() {
    QXmlStreamReader reader; // Objet servant à la lecture du fichier Xml
    QString fileXmlName = QDir::currentPath() +"/saves.xml";
    QFile fileXml(fileXmlName);

    // Ouverture du fichier XML en lecture seule et en mode texte (Sort de la fonction si le fichier ne peut etre ouvert).
    if (!fileXml.open(QFile::ReadOnly | QFile::Text))
        return false;

    // Initialise l'instance reader avec le flux XML venant de file
    reader.setDevice(&fileXml);

    QString element = "immobilier";
    bool ok;
    QMessageBox msg;
    Advert* advert;
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isStartElement())
        {
            //Si l'element est celui recherché
            if(reader.name() == element)
            {
                //Si nous venont de trouver un contributeur, il faut chercher son nom.
                if (element == "immobilier") {
                    advert = new Advert();
                    element = "new_id";
                }

                else if (element == "new_id")
                {
                    new_advert_id = reader.readElementText().toInt(&ok, 10);
                    element = "id";
                }

                //Si nous venant de trouvez le nom du contributeur, il faut chercher son age aprés avoir renségné le fichier texte.
                else if (element == "id")
                {
                    advert->SetId(reader.readElementText().toInt(&ok, 10));
                    element = "id_client";
                }

                else if (element == "id_client")
                {
                    advert->SetIdClient(reader.readElementText().toInt(&ok, 10));
                    element = "salerent";
                }

                else if (element == "salerent")
                {
                    advert->SetIsSaleRent(reader.readElementText().toInt(&ok, 10));
                    element = "datecreation";
                }

                else if (element == "datecreation")
                {
                    advert->SetDateCreation(QDate::fromString(reader.readElementText()));
                    element = "type";
                }

                else if (element == "type")
                {
                    advert->SetType(reader.readElementText());
                    element = "size";
                }

                else if (element == "size")
                {
                    advert->SetSize(reader.readElementText().toInt(&ok, 10));
                    element = "room";
                }

                else if (element == "room")
                {
                    advert->SetRooms(reader.readElementText().toInt(&ok, 10));
                    element = "num";
                }

                else if (element == "num")
                {
                    advert->SetNum(reader.readElementText());
                    element = "street";
                }

                else if (element == "street")
                {
                    advert->SetStreet(reader.readElementText());
                    element = "city";
                }

                else if (element == "city")
                {
                    advert->SetCity(reader.readElementText());
                    element = "zip";
                }

                else if (element == "zip")
                {
                    advert->SetZip(reader.readElementText());
                    element = "description";
                }

                else if (element == "description") {
                    advert->SetDescription(reader.readElementText());
                    element = "price";
                }

                else if (element == "price") {
                    advert->SetPrice(reader.readElementText().toInt(&ok, 10));
                    element = "principal";
                }

                else if (element == "principal") {
                    advert->SetPhotoPrinc(reader.readElementText());
                    element = "sup1";
                }

                else if (element == "sup1") {
                    advert->SetPhotoSup1(reader.readElementText());
                    element = "sup2";
                }

                else if (element == "sup2") {
                    advert->SetPhotoSup2(reader.readElementText());
                    element = "sup3";
                }

                else if (element == "sup3") {
                    advert->SetPhotoSup3(reader.readElementText());
                    advert_tab.append(advert);
                    element = "immobilier";
                }
            }
        }
        reader.readNext(); // On va au prochain élément
    }
    fileXml.close();
    return true;
}

bool MainWindow::Save() {

    QString fileXmlName = QDir::currentPath() + "/saves.xml";

    QFile fileXml(fileXmlName);

    // Ouverture du fichier en écriture et en texte. (sort de la fonction si le fichier ne s'ouvre pas)
    if(!fileXml.open(QFile::WriteOnly | QFile::Text))
        return false;
    QXmlStreamWriter writer(&fileXml);

    // Active l'indentation automatique du fichier XML pour une meilleur visibilité
    writer.setAutoFormatting(true);

    // Insert la norme de codification du fichier XML :
    writer.writeStartDocument();

    // Élément racine du fichier XML
    writer.writeStartElement("IHMO");

    writer.writeStartElement("advert");

    // Parcours tableau d'annonce pour sauvegarde
    for(int i = 0; i < advert_tab.count() && advert_tab.count() != 0; i++) {
        writer.writeStartElement("immobilier");

        writer.writeTextElement("new_id", QString::number(new_advert_id));
        writer.writeTextElement("id", QString::number(advert_tab[i]->GetId()));
        writer.writeTextElement("id_client", QString::number(advert_tab[i]->GetIdClient()));
        writer.writeTextElement("salerent", QString::number(advert_tab[i]->GetIsSaleRent()));
        writer.writeTextElement("datecreation", advert_tab[i]->GetDateCreation().toString());
        writer.writeTextElement("type", advert_tab[i]->GetType());
        writer.writeTextElement("size", QString::number(advert_tab[i]->GetSize()));
        writer.writeTextElement("room", QString::number(advert_tab[i]->GetRooms()));

        writer.writeStartElement("address");
        writer.writeTextElement("num", advert_tab[i]->GetNum());
        writer.writeTextElement("street", advert_tab[i]->GetStreet());
        writer.writeTextElement("city", advert_tab[i]->GetCity());
        writer.writeTextElement("zip", advert_tab[i]->GetZip());
        writer.writeEndElement();


        writer.writeTextElement("description", advert_tab[i]->GetDescription());
        writer.writeTextElement("price", QString::number(advert_tab[i]->GetPrice()));

        writer.writeStartElement("photo");
        writer.writeTextElement("principal", advert_tab[i]->GetPhotoPrinc());
        writer.writeTextElement("sup1", advert_tab[i]->GetPhotoSup1());
        writer.writeTextElement("sup2", advert_tab[i]->GetPhotoSup2());
        writer.writeTextElement("sup3", advert_tab[i]->GetPhotoSup3());
        writer.writeEndElement();

        writer.writeEndElement();

    }
    // Fermer l'ecriture de l'element <advert>
    writer.writeEndElement();

    // Finalise le document XML
    writer.writeEndDocument();

    // Fermer le fichier pour bien enregistrer le document et ferme l'élément root
    fileXml.close();
    return true;
}

void MainWindow::UpdateTab() {
    int i;
    saled_tab.clear();
    rented_tab.clear();
    for (i = 0; i < advert_tab.count(); ++i) {
        if (advert_tab[i]->GetIsSaleRent() == 0) {
            sale_tab.append(advert_tab[i]);
            if (advert_tab[i]->GetIdClient() != -1) {
                saled_tab.append(advert_tab[i]);
            }
        }
        else if (advert_tab[i]->GetIsSaleRent() == 1) {
            rent_tab.append(advert_tab[i]);
            if (advert_tab[i]->GetIdClient() != -1) {
                rented_tab.append(advert_tab[i]);
            }
        }
    }

    QMessageBox msg;
    msg.setText("NB Saled: "+QString::number(saled_tab.count()));
    msg.exec();
    msg.setText("NB Rented: "+QString::number(rented_tab.count()));
    msg.exec();
}

void MainWindow::on_btn_add_advert_clicked()
{
    Advert_Dialog *advert_dlg = new Advert_Dialog(this, new_advert_id);
    Advert *advert;
    if (advert_dlg->exec() == QDialog::Accepted) {
        advert = advert_dlg->GetAdvert();
        new_advert_id++;
        if (advert_dlg->hasClient()) {
            Client* client;
            if (!isKnownClient(advert_dlg->GetClient())) {
                client = advert_dlg->GetClient();
                client->SetId(new_client_id);
                client_tab.append(client);
                advert->SetIdClient(client->GetId());
                new_client_id++;
            } else {
                client = client_tab[GetIndexClient(advert_dlg->GetAdvert()->GetId())];
                advert->SetIdClient(client->GetId());
            }
        }
        advert_tab.append(advert);
        UpdateTab();
        FillAllAdvert(advert_tab);
    }
    delete advert_dlg;
}

bool MainWindow::isKnownClient(Client* client) {
    int test = false;
    int i;
    for(i = 0; i < client_tab.count() && !test;i++) {
        if(client->GetName() == client_tab[i]->GetName() && client->GetSurname() == client_tab[i]->GetSurname())
            test = true;
    }
    return test;
}

int MainWindow::GetIndexClient(int id_client) {
    int indice = 0;
    int i;
    for(i = 0; i < client_tab.count();i++) {
        if(id_client == client_tab[i]->GetId())
            indice = i;
    }
    return indice;
}

void MainWindow::on_btn_search_clicked()
{
    if (CheckLE()) {
        QString sprice_min = ui->le_price_min->text();
        QString sprice_max = ui->le_price_max->text();
        QString srooms_min = ui->le_rooms_min->text();
        QString srooms_max = ui->le_rooms_max->text();
        QString ssize_min = ui->le_size_min->text();
        QString ssize_max = ui->le_size_max->text();
        QString type = ui->cbx_type->currentText().toLower();
        QString city = ui->le_city->text().toLower();
        QString num = ui->le_num->text().toLower();
        QString street = ui->le_street->text().toLower();
        QString zip = ui->le_zip->text().toLower();


        bool isPhoto = ui->chx_photo->isChecked();
        bool isPriceMin = sprice_min.isEmpty();
        bool isPriceMax = sprice_max.isEmpty();
        bool isRoomsMin = srooms_min.isEmpty();
        bool isRoomsMax = srooms_max.isEmpty();
        bool isSizeMin = ssize_min.isEmpty();
        bool isSizeMax = ssize_max.isEmpty();
        bool isType = type.isEmpty();
        bool isCity = city.isEmpty();
        bool isNum = num.isEmpty();
        bool isStreet = street.isEmpty();
        bool isZip = zip.isEmpty();
        bool isSale = ui->chx_sale->isChecked();
        bool isRent = ui->chx_rent->isChecked();

        int price_min;
        int price_max;
        int rooms_min;
        int rooms_max;
        int size_min;
        int size_max;

        bool ok;
        int i;

        QList<Advert*> working_tab;
        search_tab.clear();

        QMessageBox msg;

        if (isSale && !isRent)
            working_tab = sale_tab;
        else if (!isSale && isRent)
            working_tab = rent_tab;
        else
            working_tab = advert_tab;

        if (isPriceMin)
            price_min = 0;
        else
            price_min = sprice_min.toInt(&ok, 10);
        if (isPriceMax)
            price_max = std::numeric_limits<int>::max();
        else
            price_max = sprice_max.toInt(&ok, 10);

        if (isRoomsMin)
            rooms_min = 0;
        else
            rooms_min = srooms_min.toInt(&ok, 10);
        if (isRoomsMax)
            rooms_max = std::numeric_limits<int>::max();
        else
            rooms_max = srooms_max.toInt(&ok, 10);

        if (isSizeMin)
            size_min = 0;
        else
            size_min = ssize_min.toInt(&ok, 10);
        if (isSizeMax)
            size_max = std::numeric_limits<int>::max();
        else
            size_max = ssize_max.toInt(&ok, 10);

        for(i=0; i<working_tab.count(); ++i )
        {
            QString a_type = working_tab[i]->GetType().toLower();
            int a_size = working_tab[i]->GetSize();
            int a_rooms = working_tab[i]->GetRooms();
            int a_price = working_tab[i]->GetPrice();
            QString a_city = working_tab[i]->GetCity().toLower();
            QString a_num = working_tab[i]->GetNum().toLower();
            QString a_street = working_tab[i]->GetStreet().toLower();
            QString a_zip = working_tab[i]->GetZip().toLower();
            QString a_photo = working_tab[i]->GetPhotoPrinc().toLower();

            if (isPhoto) {
                if (!isType && (!isCity || !isZip)) {
                    if (!isStreet) {
                        if (!isNum) {
                            if (a_type == type && (a_city == city || a_zip == zip) && a_street == street && a_num == num && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        } else {
                            if (a_type == type && (a_city == city || a_zip == zip) && a_street == street && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        }
                    } else {
                        if (a_type == type && (a_city == city || a_zip == zip) && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                            search_tab.append(working_tab[i]);
                        }
                    }
                } else if (isType && (!isCity || !isZip)) {
                    if (!isStreet) {
                        if (!isNum) {
                            if ((a_city == city || a_zip == zip) && a_street == street && a_num == num && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        } else {
                            if ((a_city == city || a_zip == zip) && a_street == street && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        }
                    } else {
                        if ((a_city == city || a_zip == zip) && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                            search_tab.append(working_tab[i]);
                        }
                    }
                } else if (!isType && isCity) {
                    if (a_type == type && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max  && a_photo != "") {
                        search_tab.append(working_tab[i]);
                    }
                } else {
                    if (a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max  && a_photo != "") {
                        search_tab.append(working_tab[i]);
                    }
                }
            } else {
                if (!isType && (!isCity || !isZip)) {
                    if (!isStreet) {
                        if (!isNum) {
                            if (a_type == type && (a_city == city || a_zip == zip) && a_street == street && a_num == num && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        } else {
                            if (a_type == type && (a_city == city || a_zip == zip) && a_street == street && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        }
                    } else {
                        if (a_type == type && (a_city == city || a_zip == zip) && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                            search_tab.append(working_tab[i]);
                        }
                    }
                } else if (isType && (!isCity || !isZip)) {
                    if (!isStreet) {
                        if (!isNum) {
                            if ((a_city == city || a_zip == zip) && a_street == street && a_num == num && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        } else {
                            if ((a_city == city || a_zip == zip) && a_street == street && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                                search_tab.append(working_tab[i]);
                            }
                        }
                    } else {
                        if ((a_city == city || a_zip == zip) && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                            search_tab.append(working_tab[i]);
                        }
                    }
                } else if (!isType && isCity) {
                    if (a_type == type && a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                        search_tab.append(working_tab[i]);
                    }
                } else {
                    if (a_size >= size_min && a_size <= size_max && a_rooms >= rooms_min && a_rooms <= rooms_max && a_price >= price_min && a_price <= price_max) {
                        search_tab.append(working_tab[i]);
                    }
                }
            }
        }
        FillAllAdvert(search_tab);
    }
}

bool MainWindow::isLEValide(QLineEdit *le) {
    bool test = true;
    int i;
    for(i=0; i<le->text().length(); i++) {
        if(! le->text()[i].isDigit())
            test = false;
    }
    return test;
}

bool MainWindow::CheckLE() {

    bool test = true;
    bool test_valide = false;

    QMessageBox msgBox;
    QString error = "";
    QString error_valide = "";

    if (!test_valide) {
        error_valide.append("Champ(s) invalide(s):\n");
        if (!isLEValide(ui->le_price_min)) {
            error_valide.append("       Prix min\n");
            test_valide = true;
        }
        if (!isLEValide(ui->le_price_max)) {
            error_valide.append("       Prix max\n");
            test_valide = true;
        }
        if (!isLEValide(ui->le_rooms_min)) {
            error_valide.append("       Pièces min\n");
            test_valide = true;
        }
        if (!isLEValide(ui->le_rooms_max)) {
            error_valide.append("       Pièces max\n");
            test_valide = true;
        }
        if (!ui->le_street->text().isEmpty() && (ui->le_city->text().isEmpty() && ui->le_zip->text().isEmpty())) {
            error_valide.append("\nDonner une ville ou un code\n");
            test_valide = true;
        }
        if (!ui->le_num->text().isEmpty() && ui->le_street->text().isEmpty()) {
            error_valide.append("\nDonner une rue\n");
            test_valide = true;
        }
    }

    if (test_valide) {
        error.append(error_valide);
        test = false;
    }
    if (!test) {
        msgBox.critical(this, "Erreur", error);
        return false;
    }
    else
        return true;
}

void MainWindow::on_le_price_min_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_price_min->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_price_min->setText(tmp);
            }
        }
    }
}

void MainWindow::on_le_price_max_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_price_max->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_price_max->setText(tmp);
            }
        }
    }
}

void MainWindow::on_le_rooms_min_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_rooms_min->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_rooms_min->setText(tmp);
            }
        }
    }
}

void MainWindow::on_le_rooms_max_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_rooms_max->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_rooms_max->setText(tmp);
            }
        }
    }
}

void MainWindow::on_le_size_min_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_size_min->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_size_min->setText(tmp);
            }
        }
    }
}

void MainWindow::on_le_size_max_textEdited(const QString &arg1)
{
    int i;
    for(i=0; i<arg1.length(); i++)
    {
        if(! arg1[i].isDigit())
        {
            if(ui->le_size_max->isUndoAvailable()) {
                QString tmp = arg1;
                tmp.remove(arg1.length()-1, 1);
                ui->le_size_max->setText(tmp);
            }
        }
    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QMessageBox msg;
    int i;
    int indexClient = 0;
    bool findClient = false;
    Client* client;
    for (i = 0; i < client_tab.count() && !findClient; i++) {
        if (client_tab[i]->GetId() == advert_tab[index.row()]->GetIdClient()) {
            findClient = true;
            indexClient = i;
        }
    }
    if (findClient) {
        msg.setText("Index client trouvée: "+QString::number(indexClient) + "id " +QString::number(client_tab[indexClient]->GetId()));
        msg.exec();
       Advert_Dialog *advert_dlg = new Advert_Dialog(this, client_tab[indexClient], advert_tab[index.row()]);
       if (advert_dlg->exec() == QDialog::Accepted){
           advert_tab[index.row()] = advert_dlg->GetAdvert();
           UpdateTab();
           if (advert_dlg->hasClient()) {
               if (!isKnownClient(advert_dlg->GetClient())) {
                   client = advert_dlg->GetClient();
                   client->SetId(new_client_id);
                   client_tab.append(client);
                   advert_tab[index.row()]->SetIdClient(client->GetId());
                   new_client_id++;
               } else {
                   client = client_tab[GetIndexClient(advert_dlg->GetAdvert()->GetId())];
                   advert_tab[index.row()]->SetIdClient(client->GetId());
               }
           } else {
               advert_tab[index.row()]->SetIdClient(-1);
           }
           UpdateTab();
           FillAllAdvert(advert_tab);
       }
       delete advert_dlg;
    } else {
       Advert_Dialog *advert_dlg = new Advert_Dialog(this, advert_tab[index.row()]);
       if (advert_dlg->exec() == QDialog::Accepted){
           advert_tab[index.row()] = advert_dlg->GetAdvert();
           UpdateTab();
           if (advert_dlg->hasClient()) {
               if (!isKnownClient(advert_dlg->GetClient())) {
                   client = advert_dlg->GetClient();
                   client->SetId(new_client_id);
                   client_tab.append(client);
                   advert_tab[index.row()]->SetIdClient(client->GetId());
                   new_client_id++;
               } else {
                   client = client_tab[GetIndexClient(advert_dlg->GetAdvert()->GetId())];
                   advert_tab[index.row()]->SetIdClient(client->GetId());
               }
           } else {
               advert_tab[index.row()]->SetIdClient(-1);
           }
           UpdateTab();
           FillAllAdvert(advert_tab);
       }
       delete advert_dlg;
    }

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void MainWindow::on_btn_suppress_add_clicked()
{
    QModelIndexList rowToSuppress = ui->tableView->selectionModel()->selectedRows();
        int max = rowToSuppress.count();
        for (int i = 0; i < max ; i++){
            advert_tab.removeAt(rowToSuppress.at(i).row());
        }
        FillAllAdvert(advert_tab);
}

void MainWindow::on_btn_statistic_clicked()
{
    //Statistic_Dialog* stat_dlg = new Statistic_Dialog(this);
    //stat_dlg->exec();
    //delete stat_dlg;
}
