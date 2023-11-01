#include "frame_page.h"
#include "ui_frame_page.h"
#include <QDebug>
#include <QPainter>
#include "coordinate.h"

Frame_Page::Frame_Page(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Frame_Page)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->close();
    this->setGeometry(GOBAL_BACKGROUND_IMG_X, GOBAL_BACKGROUND_IMG_Y,
                      GOBAL_BACKGROUND_IMG_W, GOBAL_BACKGROUND_IMG_H);
    this->setWindowState(Qt::WindowNoState);
}

Frame_Page::~Frame_Page()
{
    delete ui;
}

void Frame_Page::Load_Background(QString image)
{
    if (image.isNull())
        return;
}

void Frame_Page::Enable_Icon_Light(int i)
{
    if (i < 0)
        return;
}
