#ifndef MUSIC_PAGE_H
#define MUSIC_PAGE_H

#include <QMainWindow>
#include <QImage>
#include <QProcess>
#include "frame_page.h"

#define MUSIC_PAGE_BACKGROUND ":/icon/barfram_bg.png"
#define MUSIC_PAGE_FRONTGROUND ":/icon/music.png"


class Music_Page : public Frame_Page
{
Q_OBJECT
public:
    explicit Music_Page(QWidget *parent = nullptr);
    void on_play();
    void on_stop();

private:
    QPixmap fgimg;

protected:
    void paintEvent(QPaintEvent *);

signals:

};

#endif
