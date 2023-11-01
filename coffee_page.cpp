#include "coffee_page.h"
#include <QPainter>
#include "coordinate.h"
#include "string/string.h"


Coffee_Page::Coffee_Page(QWidget *parent) : Frame_Page(parent)
{
    this->setObjectName("PAGE_0");
    this->setGeometry(0, 0, 800, 480);
    bgimg.load(COFFEE_PAGE_BACKGROUND);
    fgimg.load(COFFEE_PAGE_FRONTGROUND);
    qDebug("Coffee_Page\n");
}



void Coffee_Page::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, bgimg,
                       0, 0,
                       800, 480);

    painter.drawPixmap(0, 0, fgimg,
                       0, 0,
                       800, 480);
}
