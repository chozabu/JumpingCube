#ifndef TOPJCDIALOG_H
#define TOPJCDIALOG_H

#include <retroshare-gui/mainpage.h>
#include <retroshare/rsfiles.h>
#include <retroshare/rspeers.h>

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include "msgQue.h"
#include "jumpingcubewindow.h"

class p3ExampleRS;

namespace Ui {
class TopJCDialog;
}

class TopJCDialog  : public MainPage
{
    Q_OBJECT
    
public:
    explicit TopJCDialog(QWidget *parent = 0);
    ~TopJCDialog();
    virtual bool addLogInfo(const std::string &info);
    virtual bool addPeerItem(const std::string &info);
    p3ExampleRS *p3service;
    JumpingCubeWindow *jcw;
    msgQue * mMsgque;
    virtual void paintWAt(int x, int y);
    virtual void paintMouseMove(QMouseEvent *event);

public slots:
    virtual void okClicked();
    virtual void playClicked();
    virtual void sendMClick(int x, int y);
private slots:
    void on_timer();
private:
    Ui::TopJCDialog *ui;
    QTimer *timer;
    virtual void handleExampleItem( RsExampleItem * item );

};

#endif // TOPJCDIALOG_H
