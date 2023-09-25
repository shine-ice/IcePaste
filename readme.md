# 0. 前言

基于Qt5开发贴图工具



# 1. 贴图

## 1.1 贴图类

1. `PasteImage.h`

```cpp
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

```



2. `PasteImage.cpp`

```cpp
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

```



## 1.2 调用类

1. `IcePaste.h`

```cpp
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

```



2. `IcePaste.cpp`

```cpp
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


```



## 1.3 main.cpp

```cpp
#include <QApplication>
#include "IcePaste.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    IcePaste w;
    w.show();
    return a.exec();
}

```



# 2. 测试

![image-20230925090835337](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230925090835337.png)



![image-20230925090903162](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230925090903162.png)



![image-20230925090915040](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230925090915040.png)





# X. 问题与参考

## x.1 加载jpg图片

> [QPixmap,QImage load图片失败问题](https://blog.csdn.net/weixin_39834568/article/details/111500808)
>
> [QT Qimage、QPixmap等读取图片失败的几种可能情况](https://blog.csdn.net/qq_39295271/article/details/105755167)
>
> [关于qt qpixmap qimage 无法正常加载jpg格式图片问题(坑啊)](https://shenmingyi.blog.csdn.net/article/details/121163706)

![image-20230925090349195](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230925090349195.png)



![image-20230925090553590](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230925090553590.png)



imageformats文件夹内存放Qt所有图片解析库，应放在与应用程序同级目录



## x.2 在函数内调用QWidget子类的show()函数，窗口不显示

> [在函数内调用QWidget类show()函数，没有显示窗口问题](https://blog.csdn.net/weixin_44901043/article/details/123212797)
>
> [关于QWidget的子类调用show()方法不能显示的问题](https://blog.csdn.net/u013267480/article/details/49645093)

因为QWidget不是一个窗口，是一个普通部件，需要将QWidget实例设置成窗口属性，或者修改为集成QDialog

```cpp
void Widget::on_pushButton_clicked()
{
    QWidget * dlg = new QWidget(this);
    dlg->setWindowFlags(Qt::Window);
    dlg->show();
}

```



## x.3 在子控件Widget上绘图报错

> [qt在子控件widget上绘图报错：QWidget::paintEngine: Should no longer be called... 解决](https://blog.csdn.net/qq_40015157/article/details/122605512)

**错误：**

```cpp
void PageOne::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    qDebug() << "this==== " << this->ui->widget_5;
    ...
}
```



![image-20230808050453305](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230808050453305.png)



**解决：**

1. 通过父窗口给控件安装事件过滤器 ui->widget_5->installEventFilter(this);
2. 重写函数 eventFilter()、paintWidget()

```cpp
PageOne::PageOne(QWidget *parent) : QWidget(parent)
      , ui(new Ui::PageOne)
{
    ui->setupUi(this);
    ui->widget_5->installEventFilter(this);
    showVideo();
}

bool PageOne::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->widget_5 && event->type() == QEvent::Paint) {
        paintWidget();
    }
 
    return QWidget::eventFilter(watched, event);
}

void PageOne::paintWidget() {
    QPainter painter(ui->widget_5);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());//先画成黑色
    if(m_Image.size().width() <= 0)
        return;
    //将图像按比例缩放成和窗口一样大小
    QImage img = m_Image.scaled(this->size(), Qt::KeepAspectRatio);
    int x = this->width() - img.width();
    int y = this->height() - img.height();
    x /=  2;
    y /= 2;
    painter.drawImage(QPoint(x, y), img);
}
```



## x.4 设置窗口阴影

> [QT界面设计-窗体阴影（1）](https://blog.csdn.net/tianyi1991/article/details/131069864)
>
> [qt自定义无边框、可拉伸、可拖拽移动、阴影窗体](https://blog.csdn.net/QW1540235670/article/details/111028331)
>
> [QT设置窗口阴影](https://blog.csdn.net/weixin_43435307/article/details/130536067)

1. 采用widget嵌套的方式实现

![image-20230808060000627](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230808060000627.png)

2. 主widget背景透明，且大于子widget，为子widget添加阴影

```cpp
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(20);
    effect->setColor(QColor("#c7c7c7"));
    effect->setOffset(0, 0);
    ui->frame_MainBg->setGraphicsEffect(effect);
 
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
```



## x.5 在Windows中，为子控件设置句柄

> [QWidget之Alien与Native小记](https://blog.csdn.net/dbzhang800/article/details/7006270)
>
> [请问QT创建出来的对话框里面的控件(如BUTTON)是否带句柄的???](https://bbs.csdn.net/topics/380093785)

在Windows,对应一个对话框程序(比如"计算器"这个程序),用Spy++看,可以看到每个按钮都对应一个窗口(HWND)的,而浏览器中的控件,比如csdn的回复页面,里面的"结贴","发帖"这些按钮用Spy++看,他们是没有对应一个窗口(HWND)的,我称之为DirectUI,我就是想问QT开发出来的对话框程序,在Windows下跑的时候是否每个控件对应一个窗口(HWND)的????

不是，从4.4 Qt开始，大部分控件默认都是没有HWND句柄的(即Qt中所谓的alien widget)。有HWND句柄的，称之为native widget。

除了窗口(Window)、QGLWidget、等一些东西必须为native widget外，其他的你可以自己控制是使用native还是alien。

如果你对一个alien widget调用winId()，那么它会先被转换成native widget。

![image-20230808063620166](E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\assets\image-20230808063620166.png)



## x.6 监听鼠标上下滚动事件

> [Qt5.13监听鼠标滚轮的上下滚动事件QWheelEvent的angleDelta().y()](https://blog.csdn.net/luolaihua2018/article/details/110086093)
>
> [【QT】QT从零入门教程(七)：鼠标滚轮实现图像的放大缩小](https://blog.csdn.net/qq_44951518/article/details/102925713)

在Qt5中有两种读取鼠标滚轮事件滚动增量的方法:

- angleDelta()返回滚轮度数的增量， 始终提供此值
- pixelDelta()返回屏幕像素的增量,可以在具有高分辨率触摸板的平台上使用,比如macOS 如果是这样,source()将返回Qt::MouseEventSynthesizedBySystem，但在普通设备中source()将返回Qt::MouseEventNotSynthesized，并且pixelDelta()返回的是QPoint(0,0)
- delta(),新版的Qt已经将其废除，它的返回值相当于angleDelta()的返回值的y点坐标

利用QWheelEvent的delta()函数获得滚轮滚动的距离值，通过此值判断滚轮滚动的方向。若delta大于0，则表示滚轮向前（远离用户的方向），小于零则表明向后，（靠近用户的方向）。
鼠标的滚动事件，滚轮每滚动1度，相当于移动了8度，而常见的滚轮鼠标拨动一下的滚动角度为15度，因此滚轮拨动一下相当于移动了120度。

```cpp
void MainWindow::wheelEvent(QWheelEvent *event){
QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta();
    int delta = event->delta ();
    qDebug() << "numPixels:"<<numPixels;
    qDebug() << "numDegrees:"<<numDegrees;
    qDebug() << "delta:"<<delta;
    qDebug() << "the wheel event source: "<<event->source ();
    if(numDegrees.y()>0){
        qDebug() << "向前滚动"<<numDegrees.y();
    }else{
        qDebug() << "向后滚动"<<numDegrees.y();
    }
}

```

当上下滚动滑轮时，有如下显示：

```bash
numPixels: QPoint(0,0)
numDegrees: QPoint(0,120)
delta: 120
the wheel event source:  Qt::MouseEventNotSynthesized
向前滚动 120
numPixels: QPoint(0,0)
numDegrees: QPoint(0,-120)
delta: -120
the wheel event source:  Qt::MouseEventNotSynthesized
向后滚动 -120

```

综上所述，要判断鼠标滚轮滚动方向，可以使用QWheelEvent的delta()和angleDelta()函数，但是delta()函数在新版Qt中已被废除，所以最好使用angleDelta().y()的值来判断。



```cpp
void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees;                                     // 定义指针类型参数numDegrees用于获取滚轮转角
    numDegrees = event->angleDelta();                      // 获取滚轮转角
    int step = 0;                                          // 设置中间参数step用于将获取的数值转换成整数型
    if (!numDegrees.isNull())                              // 判断滚轮是否转动
    {
        step = numDegrees.y();                             // 将滚轮转动数值传给中间参数step
    }
    event->accept();                                       // 获取事件
    int currentWidth = imgLabel->width();                  // 获取当前图像的宽
    int currentHeight = imgLabel->height();                // 获取当前图像的高
    currentWidth += step;                                  // 对当前图像的高累加
    currentHeight += step;                                 // 对当前图像的宽累加
    if (step > 0)                                          // 判断图像是放大还是缩小
    {
        QString imgsize = QString("图像放大,尺寸为：%1 * %2")
                .arg(currentWidth).arg(currentHeight);
        qDebug() << imgsize;                               // 打印放大后的图像尺寸
    }
    else
    {
        QString imgsize = QString("图像缩小,尺寸为：%1 * %2")
                .arg(currentWidth).arg(currentHeight);
        qDebug() << imgsize;                                // 打印缩小后的图像尺寸
    }
    imgLabel->resize(currentWidth, currentHeight);          // 通过更新图像显示控件的大小来更新图像大小
}

```



## x.7 Qt::QPixmap的图片缩放方法

> [Qt:QPixmap的图片缩放方法](https://blog.csdn.net/tieshuxianrezhang/article/details/79060162)

```cpp
Qsize picSize(600,400);
//将pixmap缩放成picSize大小然后保存在scaledPixmap中;

//按比例缩放：
QPixmap scaledPixmap = pixmap.scaled(picSize, Qt::KeepAspectRatio);

//不按照比例缩放：
QPixmap scaledPixmap = pixmap.scaled(picSize);
```

