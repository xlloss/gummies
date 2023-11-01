#ifndef PAGE_CTL_H
#define PAGE_CTL_H

#include <QMainWindow>
#include <QWidget>
#include "coffee_page.h"
#include "cat_page.h"
#include "backlight_page.h"
#include "music_page.h"

class Page_Ctl
{

public:
    explicit Page_Ctl(QWidget *parent);

    Coffee_Page *coffee_page;
    Cat_Page *cat_page;
    Backlight_Page *backlight_page;
    Music_Page *music_page;
    class Frame_Page *framepage;

signals:

};

#endif
