#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QMainWindow>
#include <QImage>
#include "frame_page.h"

#define COFFEE_PAGE_BACKGROUND ":/icon/barfram_bg.png"
#define COFFEE_PAGE_FRONTGROUND ":/icon/coffee.png"


class Coffee_Page : public Frame_Page
{
Q_OBJECT
public:
    explicit Coffee_Page(QWidget *parent = nullptr);

private:
    QPixmap fgimg;

protected:
    void paintEvent(QPaintEvent *);

signals:

};

#endif
