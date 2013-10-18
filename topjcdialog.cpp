#include "topjcdialog.h"
#include "ui_topjcdialog.h"
#include "p3ExampleRS.h"
//#include "msgQue.h"


#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

/** Constructor
LinksDialog::LinksDialog(RsPeers *peers, RsFiles *files, QWidget *parent)
: MainPage(parent), mPeers(peers), mFiles(files)
{

}**/


TopJCDialog::TopJCDialog(QWidget *parent) :
    MainPage(parent),
    ui(new Ui::TopJCDialog)
{
    ui->setupUi(this);
    ui->loginfo->append("\nasd\n");
    //p3ExampleRS *p3service = NULL;
    ui->paintWidget->tjd = this;

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->playGameButton, SIGNAL(clicked()), this, SLOT(playClicked()));
    //connect(ui->paintWidget, SIGNAL(mouseMoveEvent()), this, SLOT(paintMouseMove()));
    //connect(ui->drawingArea, SIGNAL(mouseMoveEvent()), this, SLOT(paintMouseMove()));

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(on_timer()));
    timer->start(500);

    jcw = NULL;


}

TopJCDialog::~TopJCDialog()
{
    delete ui;
}

void TopJCDialog::paintWAt(int x, int y){
    ui->paintWidget->paintAt(x,y);
}


void TopJCDialog::on_timer(){

    std::vector<RsExampleItem> *msges = mMsgque->getMsgList();
    std::vector<RsExampleItem> msgs = *msges;


    for(uint y=0; y<msgs.size(); y++)
    {

        handleExampleItem(&msgs[y]);
    }
}

std::vector<std::string> tokenize(std::string msg){
std::istringstream iss(msg);
std::vector<std::string> tokens;
copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string> >(tokens));
return tokens;
}

void TopJCDialog::handleExampleItem( RsExampleItem * item )
{
    std::string msg = item->getMessage();
    std::cerr << item->PeerId() << " said: " << msg << std::endl;
    //msgque
    std::cerr << msg.substr(0,4) << std::endl;
    if (msg.substr(0,4).compare("DATA")==0){
        //DATA mx=75 my=127
        // tokeniser from http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
        //std::istringstream iss(msg);
        std::cerr << "tokenising" << std::endl;
        std::vector<std::string> tokens = tokenize(msg);
        /*copy(std::istream_iterator<std::string>(iss),
                 std::istream_iterator<std::string>(),
                 std::back_inserter<std::vector<std::string> >(tokens));*/
        std::string xstr = tokens.at(1);
        int x = atoi(xstr.c_str());
        std::string ystr = tokens.at(2);
        int y = atoi(ystr.c_str());
        std::cerr << "CONVERTEDNUMS: " << x << y << std::endl;
        paintWAt(x,y);
    }else if (msg.substr(0,4).compare("INIT")==0){
        addPeerItem(item->PeerId());
    }else if (msg.substr(0,4).compare("CHAT")==0){
        ui->chatWindow->append(item->PeerId().data());
        ui->chatWindow->append(" says:");
        msg = msg.erase(0,5);
        ui->chatWindow->append(msg.data());
        ui->chatWindow->append("");
    }else if (msg.substr(0,4).compare("JCGM")==0){
        JumpingCubeWindow* jc = new JumpingCubeWindow(this);
        jc->myid = 0;
        std::string peerid = item->PeerId();
        jc->peerid = peerid;
        jc->show();
        jcw = jc;
        connect(jc, SIGNAL(mClick(int, int)), this, SLOT(sendMClick()));
    }else if (msg.substr(0,4).compare("JCPR")==0){
        std::vector<std::string> tokens = tokenize(msg);
        std::string xstr = tokens.at(1);
        int x = atoi(xstr.c_str());
        std::string ystr = tokens.at(2);
        int y = atoi(ystr.c_str());
        std::cout << "CONVERTEDNUMS: " << x << y << std::endl;
        jcw->remoteClick(x,y);
        //emit incomingRemoteClick(2,2);
    }else{
        addLogInfo("unknown message from:");
        addLogInfo(item->PeerId());
        addLogInfo(item->getMessage());
    }
    //item->RS_PKT_SUBTYPE
}


void TopJCDialog::paintMouseMove(QMouseEvent *event){
    std::cout << "inpaintslot" << std::endl;
    int x = event->x();
    int y = event->y();
    std::cout << x;

    if (ui->onlinePeerView->currentItem() == NULL){
        ui->loginfo->append("\nNothing selected, so returning \n");
        return;
    }
    std::string peerid = ui->onlinePeerView->currentItem()->text().toStdString();
    p3service->msgPeerXY(peerid, x,y);
}

void TopJCDialog::sendMClick(int x, int y){
    std::cerr << "SENDING MESSAGE FROM CLICK";
    std::string peerid = ui->onlinePeerView->currentItem()->text().toStdString();
    p3service->msgPeerXYT(peerid, x,y,"JCPR");
}

void TopJCDialog::okClicked(){
    std::cout << "OKClicked" <<std::endl;
    ui->loginfo->append("\n OK Clicked! \n");
    ui->chatWindow->append( "you say:");
    ui->chatWindow->append(ui->inputText->toPlainText().toStdString().data());
    //p3service = p3servicein;
    //std::cout << "ITEM SELECTED IS: " << ui->onlinePeerView << std::endl;
    //ui->loginfo->append(ui->onlinePeerView->item(0)->text());
    if (ui->onlinePeerView->currentItem() == NULL){
        ui->chatWindow->append("To no-one - select a peer on the left");
        ui->loginfo->append("Nothing selected, so returning");
        ui->chatWindow->append("");
        return;
    }
    ui->loginfo->append(ui->onlinePeerView->currentItem()->text());
    //p3service->testit();
    std::string msg = "CHAT ";
    msg.append(ui->inputText->toPlainText().toStdString());
    ui->chatWindow->append("");
    std::string peerid = ui->onlinePeerView->currentItem()->text().toStdString();
    p3service->msgPeer(peerid, msg);
}


void TopJCDialog::playClicked(){
    std::cout << "Play Clicked" <<std::endl;
    ui->loginfo->append("Play  Clicked!");
    if (ui->onlinePeerView->currentItem() == NULL){
        ui->chatWindow->append("select a peer on the left");
        ui->loginfo->append("Nothing selected, so returning");
        ui->chatWindow->append("");
        return;
    }
    JumpingCubeWindow* jc = new JumpingCubeWindow(this);
    jc->myid = 1;
    std::string peerid = ui->onlinePeerView->currentItem()->text().toStdString();
    jc->peerid = peerid;
    jc->show();
    jcw = jc;
    connect(jc, SIGNAL(mClick(int, int)), this, SLOT(sendMClick(int, int)));


    std::string msg = "JCGM please";
    p3service->msgPeer(peerid, msg);
}


//QPushButton TopJCDialog::getOKButton(){
  //  return ui->okButton;
    //std::cerr << "passing: " << info.data() << std::endl;
    //ui->loginfo->append(info.data());
//}

bool TopJCDialog::addLogInfo(const std::string &info){
    std::cerr << "passing: " << info.data() << std::endl;
    ui->loginfo->append(info.data());
    return true;
}
bool TopJCDialog::addPeerItem(const std::string &info){
    //std::cerr << "passing: " << info.data() << std::endl;
    //ui->loginfo->append(info.data());
    ui->onlinePeerView->addItem(info.data());
    //if (ui->onlinePeerView->count() == 1)ui->onlinePeerView->selectAll();
    return true;
}


