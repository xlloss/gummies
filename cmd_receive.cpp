#include "backlight_page.h"
#include "cmd_receive.h"
#include <QDebug>

#define PAGE_00 "PAGE_0"//coffee
#define PAGE_01 "PAGE_1"//cat
#define PAGE_02 "PAGE_2"//backlight ON
#define PAGE_03 "PAGE_3"//backlight OFF
#define PAGE_04 "PAGE_4"//backlight add
#define PAGE_05 "PAGE_5"//backlight dec
#define PAGE_06 "PAGE_6"//open R_G_B LED
#define PAGE_07 "PAGE_7"//open R_LED
#define PAGE_08 "PAGE_8"//open G_LED
#define PAGE_09 "PAGE_9"//open B_LED

#define PAGE_10 "PAGE_10"//close R_LED
#define PAGE_11 "PAGE_11"//close G_LED
#define PAGE_12 "PAGE_12"//close B_LED
#define PAGE_13 "PAGE_13"//play music
#define PAGE_14 "PAGE_14"//stop music


#define REC_UART_PORT "/dev/ttyUSB0"
#define REC_UART_SPEED 115200

WorkThread::WorkThread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
    int ret;

    serialport = new Serial_Port();
    ret = serialport->Serial_Port_Open(REC_UART_PORT, REC_UART_SPEED);
    if (ret)
        qDebug("Serial_Port_Open fail\n");
}

void WorkThread::run()
{
    QByteArray rdata, cmdbuf;

    QThread::msleep(10);

    while(1) {
        serialport->Serial_Port_Read(&rdata);
        if (rdata.size() <= 0)
            goto gotsleep;

        //qDebug("rdata.size() %d\n", rdata.size());
        getcmd = new Cmd_Buf;
        getcmd->buf_sz = rdata.size();
        memcpy(getcmd->buf, rdata.data(), sizeof(uint8_t) * uint8_t(rdata.size()));
        cmd_list.append(getcmd);

        rdata.clear();
        rdata.resize(0);

gotsleep:
        msleep(1);
    }
}

PageCtl_Thread::PageCtl_Thread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
    cmd_receive = static_cast<Cmd_Receive *>(parent);
    //connect(mPage_ctl_thread, SIGNAL(Triger_Page_Signal()), cmd_receive, SLOT(Triger_Page(unsigned char)));
}

void PageCtl_Thread::run()
{
    unsigned char *readbuf;
    Cmd_Buf *getcmdlistbuf;
    int cmd_n, cmd_index, index;
    char page_info[10] = "PAGE_";
    unsigned char page_index;
    QProcess process;
    QString cmd;

    cmd.append("sh /home/root/init_da7218.sh");
    process.execute(cmd);
    QThread::msleep(10);

    while(1) {

        cmd_n = cmd_receive->mThread->cmd_list.size();
        if (!cmd_n)
            goto do_sleep;

        for (cmd_index = 0; cmd_index < cmd_n; cmd_index++) {
            getcmdlistbuf = cmd_receive->mThread->cmd_list.at(cmd_index);

            readbuf = new unsigned char [getcmdlistbuf->buf_sz + 1];
            memcpy(readbuf, getcmdlistbuf->buf, sizeof(unsigned char) * uint8_t(getcmdlistbuf->buf_sz));
            readbuf[getcmdlistbuf->buf_sz] = 0;
            for (index = 0; index < 5; index++) {
                if (readbuf[index] != page_info[index]) {
                    qDebug("SERIAL CMD FAIL\n");
                    break;
                }
            }

            //qDebug() << "index=" << index ;
            if (index == 5) {
                /* CMD => PAGE_0 PAGE_1 ... */
                if (getcmdlistbuf->buf_sz == 6) {
                    page_index = readbuf[5] - '0';
                } else {
                    page_index = ((readbuf[5] - '0') * 10) + readbuf[6] - '0';
                }
                cmd_receive->Triger_Page(page_index);
            }

            delete readbuf;
            cmd_receive->mThread->cmd_list.removeAt(cmd_index);
            delete getcmdlistbuf;
        }
do_sleep:
        QThread::msleep(1);
    }
}


Cmd_Receive::Cmd_Receive(QObject *parent) : QObject(parent)
{
    mThread = new WorkThread(this);
    mPage_ctl_thread = new PageCtl_Thread(this);
    mPage_ctl_thread->cmd_receive = (Cmd_Receive *)this;
    mThread->start();
    mPage_ctl_thread->start();
    current_page = "NONE";

}


void Cmd_Receive::Register(class Frame_Page *frameage)
{
    page_list.append(frameage);
    connect(this, SIGNAL(set_show_page()), frameage, SLOT(show()));
    connect(this, SIGNAL(set_close_page()), frameage, SLOT(close()));

}

int Cmd_Receive::Find_Frame(QString objname)
{
    int i, ret, list_cnt;
    class Frame_Page *frameage;

    if (page_list.empty())
        return -1;

    list_cnt = page_list.count();

    for (i = 0; i < list_cnt; i++) {
        frameage = page_list.at(i);
        ret = objname.compare(frameage->objectName());
        if (!ret)
            break;
    }

    if (i >= list_cnt)
        return -1;

    return i;

}

void Cmd_Receive::Frame_Page_Show(QString show_objname)
{
    class Frame_Page *show_framepage;
    class Frame_Page *close_framepage;
    int i, j;

    i = Find_Frame(show_objname);
    if (i < 0) {
        qDebug() << "can't find page\n" << show_objname;
        return;
    }


    qDebug() << "find page =" << show_objname;
    j = -1;
    show_framepage = page_list.at(i);
    if (current_page.compare("NONE") != 0) {
        j = Find_Frame(current_page);
        if (j < 0) {
            qDebug("can't find any current page\n");
            return;
        }
    }

    if (current_page.compare(show_objname) != 0) {
        if (j >= 0) {
            close_framepage = page_list.at(j);
            if (close_framepage)
                close_framepage->hide();
        }
        show_framepage->setWindowFlags(Qt::WindowStaysOnTopHint);
        show_framepage->setGeometry(0, 0, 800, 480);
        show_framepage->setWindowState(Qt::WindowActive);
        show_framepage->show();
    } else {
        show_framepage->update();
    }


    current_page = show_objname;

}

void Cmd_Receive::Triger_Page(unsigned char page_num)
{
    QProcess process;
    QString cmd;

   /*
    * real cmd, page start form 1
    * Qt source code, page start form 0
    * total cmd are 18
    */

    #define OBJNAME_TOTAL 15
    #define REAL_CMD_TOTAL (OBJNAME_TOTAL + 1)
    QString objname[OBJNAME_TOTAL] = {
        PAGE_00,
        PAGE_01,
        PAGE_02,
        PAGE_03,
        PAGE_04,
        PAGE_05,
        PAGE_06,
        PAGE_07,
        PAGE_08,
        PAGE_09,
        PAGE_10,
        PAGE_11,
        PAGE_12,
        PAGE_13,
        PAGE_14};

    qDebug() << "page num =" << page_num;
    cmd.clear();

    /* backlight control */
    if (page_num == 2 || page_num == 3 ||
        page_num == 4 || page_num == 5) {

        qDebug() << __func__ << __LINE__;
        switch (page_num) {
        case 2:
            qDebug() << "on_backlight.sh";
            cmd.append("sh /home/root/on_backlight.sh");
            break;

        case 3:
            qDebug() << "off_backlight.sh";
            cmd.append("sh /home/root/off_backlight.sh");
            break;

        case 4:
            cmd.append("sh /home/root/add_backlight.sh");
            break;

        case 5:
            cmd.append("sh /home/root/dec_backlight.sh");
            break;


        default:
            break;
        }

        process.execute(cmd);
        return;
    }

    /* led control */
    if (page_num == 7 || page_num == 8 || page_num == 9 ||
        page_num == 10 || page_num == 11 || page_num == 12) {
        switch (page_num) {
        case 7:
            qDebug() << "led_red_ctrl.sh on";
            cmd.append("sh /home/root/led_red_ctrl.sh 1");
            break;

        case 8:
            qDebug() << "led_green_ctrl.sh on";
            cmd.append("sh /home/root/led_green_ctrl.sh 1");
            break;

        case 9:
            qDebug() << "led_blue_ctrl.sh on";
            cmd.append("sh /home/root/led_blue_ctrl.sh 1");
            break;

        case 10:
            qDebug() << "led_red_ctrl.sh off";
            cmd.append("sh /home/root/led_red_ctrl.sh 0");
            break;

        case 11:
            qDebug() << "led_green_ctrl.sh";
            cmd.append("sh /home/root/led_green_ctrl.sh 0");
            break;

        case 12:
            qDebug() << "led_blue_ctrl.sh";
            cmd.append("sh /home/root/led_blue_ctrl.sh 0");
            break;

        default:
            break;
        }

        process.execute(cmd);
        page_num = 6;
    }

    /* music */
    if (page_num == 13 || page_num == 14) {

        switch (page_num) {
        case 13:
            cmd.append("sh /home/root/play_music.sh");
            process.execute(cmd);
            break;

        case 14:
            cmd.append("sh /home/root/stop_music.sh");
            process.execute(cmd);
            page_num = 13;
            break;

        default:
            break;
        }
    }

    if (page_num >= OBJNAME_TOTAL)
        return;

    Frame_Page_Show(objname[page_num]);
}
