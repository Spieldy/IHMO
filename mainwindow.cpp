#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "advert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if (Charge()) {
        ui->setupUi(this);
        QMessageBox msg;
        msg.setText(advert_tab[0]->GetType());
        msg.exec();
    } else {
        QMessageBox msgBox;
        msgBox.critical(this, "Erreur", "Problème rencontré lors du chargement des données");
    }
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
    Advert* advert = new Advert();
    bool ok;
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isStartElement())
        {
            //Si l'element est celui recherché
            if(reader.name() == element)
            {
                //Si nous venont de trouver un contributeur, il faut chercher son nom.
                if (element == "immobilier")
                    element = "id";

                //Si nous venant de trouvez le nom du contributeur, il faut chercher son age aprés avoir renségné le fichier texte.
                else if (element == "id")
                {
                    advert->SetId(reader.readElementText().toInt(&ok, 10));
                    element = "type";
                }

                //Si nous avons trouvez l'age du contributeur, Nous pouvons chercher l'existence d'une autre contributeur aprés avoir renseigné le fichier texte
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
                    element = "address";
                }

                else if (reader.isStartElement()) {
                    if (element == "address")
                        element = "num";

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
                }

                else if (element == "description") {
                    advert->SetDescription(reader.readElementText());
                    element = "price";
                }

                else if (element == "price") {
                    advert->SetPrice(reader.readElementText().toInt(&ok, 10));
                    element = "immobilier";
                }
            }
        }
        else if (reader.isEndElement())
        {
            // Permet d'éviter de chercher des informations manquantes au detriments de la recherche de contributeur
            if(reader.name() == "contributeur")
            {

            }
        }
        reader.readNext(); // On va au prochain élément
    }
    advert_tab.append(advert);
    fileXml.close();
    return true;
}

bool MainWindow::Save() {
    QString fileXmlName = QDir::currentPath() + "/saves.xml";
    QMessageBox msg;
    msg.setText(fileXmlName);
    msg.exec();
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
    for(int i = 0; i < nb_advert; i++) {
        writer.writeStartElement("immobilier");

        writer.writeTextElement("id", QString::number(advert_tab[i]->GetId()));
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
        writer.writeTextElement("principal", "chemin");
        writer.writeTextElement("sup1", "chemin");
        writer.writeTextElement("sup2", "chemin");
        writer.writeTextElement("sup3", "chemin");
        writer.writeTextElement("sup4", "chemin");
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
    Advert_Dialog *advert_dlg = new Advert_Dialog(this);
    Advert *advert;
    if (advert_dlg->exec() == QDialog::Accepted) {
        advert = advert_dlg->GetAdvert();
        advert->SetId(nb_advert);
        advert_tab.append(advert);
        nb_advert = nb_advert + 1;
    }
    delete advert_dlg;
}
