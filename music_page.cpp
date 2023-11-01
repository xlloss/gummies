#include "music_page.h"
#include <QPainter>
#include "coordinate.h"
#include "string/string.h"


Music_Page::Music_Page(QWidget *parent) : Frame_Page(parent)
{
    this->setObjectName("PAGE_13");
    this->setGeometry(0, 0, 800, 480);
    bgimg.load(MUSIC_PAGE_BACKGROUND);
    fgimg.load(MUSIC_PAGE_FRONTGROUND);
    qDebug("MUSIC_Page\n");
}

void Music_Page::on_play()
{

}

void Music_Page::on_stop()
{

}

void Music_Page::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, bgimg,
                       0, 0,
                       800, 480);

    painter.drawPixmap(0, 0, fgimg,
                       0, 0,
                       800, 480);
}
