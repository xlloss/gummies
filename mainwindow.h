#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include "page_ctl.h"
#include "frame_page.h"
#include "cmd_receive.h"

#define MAINWINDOW_OBJNAME "Mainwindow"
#define MAINWINDOW_BG_IMG ":/icon/Regulus.png"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace name {
    class Frame_Page;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap backimg;


    Page_Ctl *page_ctl;
    Cmd_Receive *cmd_get;

protected:
    void paintEvent(QPaintEvent *);

private slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
