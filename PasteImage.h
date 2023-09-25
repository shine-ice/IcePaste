//
// Created by Wsy on 2023/9/24.
//

#ifndef ICEPASTE_PASTEIMAGE_H
#define ICEPASTE_PASTEIMAGE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QTimer>
#include <QDialog>
#include <QtMath>
#include <QGuiApplication>
#include <QScreen>

#define SHADOW_WIDTH 15                 // 阴影大小

// 图片状态
enum ImageState {
    NONE,
    BEGIN_SCALE,
    BEGIN_EDIT
};

class PasteImage : public QWidget {
    Q_OBJECT
public:
    PasteImage(QWidget *parent = NULL);
    PasteImage(QWidget *parent = nullptr, QPixmap image = QPixmap(), QPoint topLeftPoint = QPoint());
    ~PasteImage();

private:
    void initData( );
    void initWindow();

    void setImagePixmap(QPixmap image);             // 设置图片

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void moveWindow();                                      // 移动窗口

    bool eventFilter(QObject *watched, QEvent *event);      // 事件过滤
    void paintWidget();                                     // 内部widget上绘制图片

    void scaleImage();                                      // 缩放图片
    void showScaleInfo();                                   // 显示缩放信息

private:
    QWidget* paintArea;             // 图片绘制区域
    QPoint topLeftPoint;            // 图片显示的左上角
    QPixmap imagePixmap;            // 图片
    QPixmap imagePixmapCopy;        // 图片的拷贝，可用于缩放

    bool isPressLeftBtn;            //
    QPoint beginMovePoint;          // 移动初始位置
    QPoint endMovePoint;            // 移动终点位置

    QPainter *painter;              // 画家
    double scaleStep;               // 缩放系数

    ImageState curImageState;       // 当前图片状态
    QTimer *scaleTimer;             // 缩放信息显示定时器
};


#endif //ICEPASTE_PASTEIMAGE_H
