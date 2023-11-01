#ifndef CMD_RECEIVE_H
#define CMD_RECEIVE_H
#include <QThread>
#include <QObject>
#include <QMutex>
#include "serial_port.h"
#include "frame_page.h"
#include "coffee_page.h"
#include "protocol_fmt.h"

class Cmd_Receive;

class Cmd_Buf
{
public:
    uint8_t buf[BUFFER_SIZE];
    int32_t buf_sz;
};



class WorkThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = 0, bool b = false);
    void run();

    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;
    QList <Cmd_Buf *> cmd_list;
    Cmd_Buf *getcmd;
    Serial_Port *serialport;
signals:

public slots:

};

class PageCtl_Thread : public QThread
{
    Q_OBJECT
public:
    Cmd_Receive *cmd_receive;
    bool Stop;
    explicit PageCtl_Thread(QObject *parent = 0, bool b = false);
    void run();

signals:
    void Triger_Page_Signal();

public slots:

};


class Cmd_Receive : public QObject
{
    Q_OBJECT
public:
    explicit Cmd_Receive(QObject *parent = nullptr);

    WorkThread *mThread;
    PageCtl_Thread *mPage_ctl_thread;
    CarInfo_Data m_carinfo_data;
    void Register(class Frame_Page *frameage);
    void Frame_Page_Show(QString objname);
    int Find_Frame(QString objname);
    QString current_page;
    QList <class Frame_Page *> page_list;
    CarInfo_Data *pcarinfo_data;
    void Triger_Page(unsigned char page_num);
private slots:

signals:
    void set_icon_light_enable(int);
    void set_show_page();
    void set_close_page();

};

#endif // CMD_RECEIVE_H
