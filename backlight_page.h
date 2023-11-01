#ifndef BACKLIGHT_PAGE_H
#define BACKLIGHT_PAGE_H

#include <QMainWindow>
#include <QImage>
#include <QProcess>
#include "frame_page.h"

#define BACKLIGHT_PAGE_BACKGROUND ":/icon/barfram_bg.png"
#define BACKLIGHT_PAGE_FRONTGROUND ":/icon/flashlight.png"


class Backlight_Page : public Frame_Page
{
Q_OBJECT
public:
    explicit Backlight_Page(QWidget *parent = nullptr);

private:
    QPixmap fgimg;
    void on_light();
    void off_light();
    unsigned backlight_val;

protected:
    void paintEvent(QPaintEvent *);

signals:

};

#endif
