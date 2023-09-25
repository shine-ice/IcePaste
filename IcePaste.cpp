//
// Created by Wsy on 2023/9/24.
//

#include <QMessageBox>
#include "IcePaste.h"

IcePaste::IcePaste(QWidget *parent) : QWidget(parent) {
    chooseImageBtn = new QPushButton(tr("选择图片"));
    connect(chooseImageBtn, SIGNAL(clicked()), this, SLOT(showImage()));
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(chooseImageBtn);
    this->setLayout(vLayout);
    this->resize(300, 400);
}

IcePaste::~IcePaste() {

}

void IcePaste::showImage() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    "",
                                                    tr("Images (*.png *.jpg *.jpeg)"));
    QPixmap pix;
    // 根据文件后缀加载图片
    if (pix.load(fileName))
    {
        // TODO 使用列表回收
        PasteImage *pasteImage = new PasteImage(nullptr, pix, QPoint(0, 0));
        pasteImage->show();
    }
    // 文件后缀不正确用下面方法加载
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, tr("提示"), tr("打开文件失败"));
            return;
        }
        pix.loadFromData(file.readAll());
        PasteImage *pasteImage = new PasteImage(nullptr, pix, QPoint(0, 0));
        pasteImage->show();
    }
}

