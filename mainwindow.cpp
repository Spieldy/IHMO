#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "advert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QMessageBox msgBox;
    if (Charge()) {
        ui->setupUi(this);
        ui->rdb_last_first->setChecked(true);

        model = new QStandardItemModel(1,7,this); //2 Rows and 5 Columns
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("")));
        model->setHorizontalHeaderItem(2, new QStandardItem(QString("Type")));
        model->setHorizontalHeaderItem(3, new QStandardItem(QString("Prix")));
        model->setHorizontalHeaderItem(4, new QStandardItem(QString("Adresse")));
        model->setHorizontalHeaderItem(5, new QStandardItem(QString("Taille (m2)")));
        model->setHorizontalHeaderItem(6, new QStandardItem(QString("Pièce(s)")));
        if (FillAllAdvert())
            ui->tableView->setModel(model);
        else
            msgBox.critical(this, "Erreur", "Problème rencontré lors du remplissage du tableau");
    } else
        msgBox.critical(this, "Erreur", "Problème rencontré lors du chargement des données");
}

MainWindow::~MainWindow()
{
    if(Save())
        delete ui;
    else {
        QMessageBox msgBox;
        msgBox.critical(this, "Erreur", "Problème rencontré lors de la sauvegarde");
    }
}

bool MainWindow::FillAllAdvert() {
    int i;
    for(i=0; i<advert_tab.count(); ++i )
    {
        QStandardItem *photo = new QStandardItem();
        QPixmap p(advert_tab[i]->GetPhotoPrinc());;
        photo->setData(QVariant(p.scaled(75, 75, Qt::KeepAspectRatio)), Qt::DecorationRole);
        model->setItem(i, 0, photo);

        int saleRent  = advert_tab[i]->GetIsSaleRent();
        QStandardItem *isSaleRent = new QStandardItem();
        if (saleRent == 0)
            isSaleRent->setText("Vente");
        else if (saleRent == 1)
            isSaleRent->setText("Location");
        model->setItem(i,1,isSaleRent);

        QStandardItem *type = new QStandardItem(QString(advert_tab[i]->GetType()));
        model->setItem(i,2,type);
        QStandardItem *price = new QStandardItem(QString::number(advert_tab[i]->GetPrice()));
        model->setItem(i,3,price);
        QStandardItem *address = new QStandardItem(QString(advert_tab[i]->GetNum()+", "+advert_tab[i]->GetStreet()+", "+advert_tab[i]->GetCity()+", "+advert_tab[i]->GetZip()));
        model->setItem(i,4,address);
        QStandardItem *size = new QStandardItem(QString::number(advert_tab[i]->GetSize()));
        model->setItem(i,5,size);
        QStandardItem *rooms = new QStandardItem(QString::number(advert_tab[i]->GetRooms()));
        model->setItem(i,6,rooms);
    }

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
                    element = "id";
                }

                //Si nous venant de trouvez le nom du contributeur, il faut chercher son age aprés avoir renségné le fichier texte.
                else if (element == "id")
                {
                    advert->SetId(reader.readElementText().toInt(&ok, 10));
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
                    nb_advert = nb_advert + 1;
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
    for(int i = 0; i < nb_advert && nb_advert != 0; i++) {
        writer.writeStartElement("immobilier");

        writer.writeTextElement("id", QString::number(advert_tab[i]->GetId()));
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

void MainWindow::on_btn_add_advert_clicked()
{
    Advert_Dialog *advert_dlg = new Advert_Dialog(this, new_id);
    Advert *advert;
    if (advert_dlg->exec() == QDialog::Accepted) {
        advert = advert_dlg->GetAdvert();
        new_id = new_id + 1;
        advert_tab.append(advert);
        nb_advert = nb_advert + 1;
        FillAllAdvert();
    }
    delete advert_dlg;
}

void MainWindow::on_btn_search_sale_clicked()
{

}

void MainWindow::on_btn_search_rent_clicked()
{

}
