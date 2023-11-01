#ifndef CAT_PAGE_H
#define CAT_PAGE_H

#include <QMainWindow>
#include <QImage>
#include "frame_page.h"

#define CAT_PAGE_BACKGROUND ":/icon/barfram_bg.png"
#define CAT_PAGE_FRONTGROUND ":/icon/cat.png"


class Cat_Page : public Frame_Page
{
Q_OBJECT
public:
    explicit Cat_Page(QWidget *parent = nullptr);

private:
    QPixmap fgimg;

protected:
    void paintEvent(QPaintEvent *);

signals:

};

#endif
