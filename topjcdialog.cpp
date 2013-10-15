#include "topjcdialog.h"
#include "ui_topjcdialog.h"
#include "p3ExampleRS.h"

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

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
}

TopJCDialog::~TopJCDialog()
{
    delete ui;
}


void TopJCDialog::setp3(p3ExampleRS *p3servicein){
    p3service = p3servicein;
}

void TopJCDialog::okClicked(){
    std::cout << "jsglsnfewjefnon" <<std::endl;
    std::cerr << "jsglsnfewjefnon" <<std::endl;
    ui->loginfo->append("\n OK Clicked! \n");
    //p3service = p3servicein;
    //std::cout << "ITEM SELECTED IS: " << ui->onlinePeerView << std::endl;
    //ui->loginfo->append(ui->onlinePeerView->item(0)->text());
    ui->loginfo->append(ui->onlinePeerView->currentItem()->text());
    p3service->testit();
    std::string peerid = ui->onlinePeerView->item(0)->text().toStdString();
    p3service->msgPeer(peerid, ui->inputText->toPlainText().toStdString());
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
    return true;
}


