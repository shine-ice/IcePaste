//
// Created by Wsy on 2023/9/24.
//

#ifndef ICEPASTE_ICEPASTE_H
#define ICEPASTE_ICEPASTE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>
#include <QImage>
#include <QFileDialog>
#include "PasteImage.h"
#include <QDebug>

class IcePaste : public QWidget {
    Q_OBJECT

public:
    IcePaste(QWidget *parent = NULL);
    ~IcePaste();

private slots:
    void showImage();

private:
    QPushButton *chooseImageBtn;

};


#endif //ICEPASTE_ICEPASTE_H
