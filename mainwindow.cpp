#include <QPainter>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setObjectName(MAINWINDOW_OBJNAME);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setGeometry(GOBAL_BACKGROUND_IMG_X, GOBAL_BACKGROUND_IMG_Y,
                      GOBAL_BACKGROUND_IMG_W, GOBAL_BACKGROUND_IMG_H);

    backimg.load(MAINWINDOW_BG_IMG);

    page_ctl = new Page_Ctl(this);
    cmd_get = new Cmd_Receive(this);

    cmd_get->Register(dynamic_cast<Frame_Page *>(page_ctl->coffee_page));
    cmd_get->Register(dynamic_cast<Frame_Page *>(page_ctl->cat_page));
    cmd_get->Register(dynamic_cast<Frame_Page *>(page_ctl->backlight_page));
    cmd_get->Register(dynamic_cast<Frame_Page *>(page_ctl->music_page));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, backimg,
                       GOBAL_BACKGROUND_IMG_X, GOBAL_BACKGROUND_IMG_Y - 100,
                       GOBAL_BACKGROUND_IMG_W, GOBAL_BACKGROUND_IMG_H);
}
