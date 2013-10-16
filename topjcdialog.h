#ifndef TOPJCDIALOG_H
#define TOPJCDIALOG_H

#include <retroshare-gui/mainpage.h>
#include <retroshare/rsfiles.h>
#include <retroshare/rspeers.h>

#include <QWidget>
#include <QPushButton>

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
    virtual void setp3(p3ExampleRS *p3servicein);
    //virtual QPushButton getOKButton();
    p3ExampleRS *p3service;
    virtual void paintWAt(int x, int y);


public slots:
    //virtual void okClicked();
    virtual void paintMouseMove(QMouseEvent *event);
    
private:
    Ui::TopJCDialog *ui;

};

#endif // TOPJCDIALOG_H
