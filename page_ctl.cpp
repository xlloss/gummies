#include "page_ctl.h"


Page_Ctl::Page_Ctl(QWidget *parent)
{
    coffee_page = new Coffee_Page(parent);
    cat_page = new Cat_Page(parent);
    backlight_page = new Backlight_Page(parent);
    music_page = new Music_Page(parent);
}
