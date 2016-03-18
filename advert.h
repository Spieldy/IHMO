#ifndef ADVERT_H
#define ADVERT_H

#include <QtWidgets>
#include "ui_advert.h"

namespace Ui {
class Advert;
}

class Advert : public QDialog
{
    Q_OBJECT
public:
    explicit Advert(QMainWindow *parent = 0);
    ~Advert();

    Ui::Dialog *ui;

signals:

public slots:
};

#endif // ADVERT_H
