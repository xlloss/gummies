#include "cat_page.h"
#include <QPainter>
#include "coordinate.h"
#include "string/string.h"


Cat_Page::Cat_Page(QWidget *parent) : Frame_Page(parent)
{
    this->setObjectName("PAGE_1");
    this->setGeometry(0, 0, 800, 480);
    bgimg.load(CAT_PAGE_BACKGROUND);
    fgimg.load(CAT_PAGE_FRONTGROUND);
    qDebug("Cat_Page\n");
}



void Cat_Page::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, bgimg,
                       0, 0,
                       800, 480);

    painter.drawPixmap(0, 0, fgimg,
                       0, 0,
                       800, 480);
}
