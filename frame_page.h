#ifndef FRAME_PAGE_H
#define FRAME_PAGE_H

#include <QFrame>

namespace Ui {
class Frame_Page;
}

class Frame_Page : public QFrame
{
    Q_OBJECT

public:
    explicit Frame_Page(QWidget *parent = nullptr);
    ~Frame_Page();
    void Enable_Icon_Light(int i);
    void Load_Background(QString image);

private slots:

protected:
    QPixmap bgimg;

private:
    Ui::Frame_Page *ui;
};

#endif // FRAME_PAGE_H
