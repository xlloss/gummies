#include "backlight_page.h"
#include <QPainter>
#include "coordinate.h"
#include "string/string.h"


Backlight_Page::Backlight_Page(QWidget *parent) : Frame_Page(parent)
{
    this->setObjectName("PAGE_6");
    this->setGeometry(0, 0, 800, 480);
    bgimg.load(BACKLIGHT_PAGE_BACKGROUND);
    fgimg.load(BACKLIGHT_PAGE_FRONTGROUND);
    qDebug("Backlight_Page\n");
}

void Backlight_Page::on_light()
{

}

void Backlight_Page::off_light()
{

}

void Backlight_Page::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, bgimg,
                       0, 0,
                       800, 480);

    painter.drawPixmap(0, 0, fgimg,
                       0, 0,
                       800, 480);
}
