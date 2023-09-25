//
// Created by Wsy on 2023/9/24.
//

#include "PasteImage.h"

PasteImage::PasteImage(QWidget *parent) : QWidget(parent) {

}

PasteImage::PasteImage(QWidget *parent, QPixmap image, QPoint topLeftPoint) : QWidget(parent) {
    initData();
    setImagePixmap(image);
    this->topLeftPoint = topLeftPoint;
    initWindow();
}

PasteImage::~PasteImage() {

}

void PasteImage::initData() {
    topLeftPoint = QPoint(0, 0);
    beginMovePoint = QPoint(0, 0);
    endMovePoint = QPoint(0, 0);

    painter = new QPainter();
    scaleStep = 0.0;

    curImageState = NONE;

    scaleTimer = new QTimer();
    connect(scaleTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void PasteImage::initWindow() {
    // 设置贴图区大小和位置
    this->resize(imagePixmap.width() + 2 * SHADOW_WIDTH, imagePixmap.height() + 2 * SHADOW_WIDTH);
    this->move(topLeftPoint.x() - SHADOW_WIDTH, topLeftPoint.y() - SHADOW_WIDTH);

    // 背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    // 显示、无边框、置顶
    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    // 激活
    this->setWindowState(Qt::WindowActive);

    // 绘图子widget
    paintArea = new QWidget(this);
    // 设置大小和位置，与截图位置一致
    paintArea->resize(imagePixmap.width(), imagePixmap.height());
    this->paintArea->move(SHADOW_WIDTH, SHADOW_WIDTH);
    // 添加事件过滤，将图片绘制到子widget
    paintArea->installEventFilter(this);

    // 提升为nativeWidget，设置句柄，截图时可以排除阴影被直接选中
    paintArea->winId();

    //为绘图子widget设置阴影边框;
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::red);
    shadow->setBlurRadius(SHADOW_WIDTH);
    this->paintArea->setGraphicsEffect(shadow);
}

void PasteImage::setImagePixmap(QPixmap image) {
    imagePixmap = image;
    imagePixmapCopy = image;
}

void PasteImage::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (!isPressLeftBtn)
        {
            beginMovePoint = event->pos();
            isPressLeftBtn = true;
        }
    }

    QWidget::mousePressEvent(event);
}

void PasteImage::mouseMoveEvent(QMouseEvent *event) {
    if (isPressLeftBtn)
    {
        endMovePoint = event->pos();
        moveWindow();
    }

    QWidget::mouseMoveEvent(event);
}

void PasteImage::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (isPressLeftBtn)
        {
            endMovePoint = event->pos();
            isPressLeftBtn = false;
            // 设置左上顶点位置
            topLeftPoint.setX(topLeftPoint.x() + (endMovePoint.x() - beginMovePoint.x()));
            topLeftPoint.setY(topLeftPoint.y() + (endMovePoint.y() - beginMovePoint.y()));
            moveWindow();
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void PasteImage::keyPressEvent(QKeyEvent *event) {
    // Esc键关闭此截图
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }

    QWidget::keyPressEvent(event);
}

void PasteImage::wheelEvent(QWheelEvent *event) {
    // 进行图片缩放
    if (curImageState == NONE || curImageState == BEGIN_SCALE)
    {
        QPoint numDegrees = event->angleDelta();
        if (!numDegrees.isNull())
        {
            curImageState = BEGIN_SCALE;
            if (numDegrees.y() > 0)
            {
                scaleStep += 0.1;
                if (scaleStep > 15)
                {
                    scaleStep = 15;
                }
            }
            else
            {

                scaleStep -= 0.1;
                if (scaleStep <= -0.9)
                {
                    scaleStep = -0.9;
                }
            }
            scaleImage();
        }
    }

    QWidget::wheelEvent(event);
}

void PasteImage::moveWindow() {
    // 不限制边界
    int x = this->pos().x() + (endMovePoint.x() - beginMovePoint.x());
    int y = this->pos().y() + (endMovePoint.y() - beginMovePoint.y());
    this->move(x, y);
}

bool PasteImage::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this->paintArea && event->type() == QEvent::Paint)
    {
        paintWidget();
    }

    return QObject::eventFilter(watched, event);
}

void PasteImage::paintWidget() {
    painter->begin(this->paintArea);

    // 抗锯齿效果
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    painter->drawPixmap(0, 0, imagePixmap);

    if (curImageState == BEGIN_SCALE)
    {
        showScaleInfo();
        curImageState = NONE;
        // 刷新定时器时间，用于隐藏缩放信息
        // qDebug() << "remainTime: " << scaleTimer->remainingTime();
        scaleTimer->start(1500);
    }

    painter->end();
}

void PasteImage::scaleImage() {
    // 计算当前图片大小
    float currentWidth = imagePixmapCopy.width() * (1 + scaleStep);
    float currentHeight = imagePixmapCopy.height() * (1 + scaleStep);

    //    if(scaleStep > 0){
    //        qDebug() << QString("图像放大，尺寸为：%1 * %2").arg(currentWidth).arg(currentHeight);
    //    }else{
    //        qDebug() << QString("图像缩小，尺寸为：%1 * %2").arg(currentWidth).arg(currentHeight);
    //    }

        // 调整图片、窗口、绘图区宽高
    //    int tWidth = imagePixmapCopy.width() * 4;
    //    int tHeight = imagePixmapCopy.height() * 4;
    //    imagePixmap = imagePixmapCopy.scaled(tWidth, tHeight).scaled(currentWidth, currentHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imagePixmap = imagePixmapCopy.scaled(currentWidth, currentHeight, Qt::KeepAspectRatio);
    this->resize(imagePixmap.width() + 2 * SHADOW_WIDTH, imagePixmap.height() + 2 * SHADOW_WIDTH);
    this->paintArea->resize(imagePixmap.width(), imagePixmap.height());

    update();
}

void PasteImage::showScaleInfo() {
    // 信息框边框
    int BORDER_WIDTH = 1;
    // 内宽边距
    int BOX_STRETCH_WIDTH = 5;
    // 内高边距
    int BOX_STRETCH_HEIGHT = 3;

    int posX, posY;

    posX = 3;
    posY = 3;

    // 计算字体宽高
    int scale = qCeil((1 + scaleStep) * 100);
    QString scaleInfo = QString("大小: %1%").arg(scale);
    int fontWidth = this->fontMetrics().horizontalAdvance(scaleInfo);
    int fontHeight = this->fontMetrics().height();

    // 设置信息框宽高
    int width = fontWidth + BOX_STRETCH_WIDTH * 2;
    int height = fontHeight + BOX_STRETCH_HEIGHT * 2;

    // 计算缩放信息框左上角位置，避免超出屏幕
    QPoint topLeft = this->pos();

    if (topLeft.x() < 0)
    {
        posX -= topLeft.x() + SHADOW_WIDTH;
    }

    if (topLeft.y() < 0)
    {
        posY -= topLeft.y() + SHADOW_WIDTH;
    }

    // 绘制背景框
    painter->setPen(QPen(QColor("#767676"), BORDER_WIDTH, Qt::SolidLine));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(QRect(QPoint(posX, posY), QSize(width, height)));

    painter->setPen(QPen(Qt::black));
    painter->drawText(QPoint(posX + BORDER_WIDTH + BOX_STRETCH_WIDTH, posY + BORDER_WIDTH + BOX_STRETCH_HEIGHT + 14), scaleInfo);
}
