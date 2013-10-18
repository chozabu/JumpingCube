#include "jumpingcubewindow.h"
#include "ui_jumpingcubewindow.h"


#include <QPainter>
#include <QMouseEvent>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>


JumpingCubeWindow::JumpingCubeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JumpingCubeWindow)
{
    ui->setupUi(this);
    //ui->gameDisplay->
    currentplayer = 0;
    boardWidth = 8;
    boardHeight = 8;

    board = new int*[boardWidth];
    for (int i = 0; i < boardWidth; ++i) {
      board[i] = new int[boardHeight];
      for (int j = 0; j < boardHeight; ++j) {
          board[i][j] = getNumSides(i,j);
      }
    }


    boardOwner = new int*[boardWidth];
    for (int i = 0; i < boardWidth; ++i) {
      boardOwner[i] = new int[boardHeight];
      for (int j = 0; j < boardHeight; ++j) {
          boardOwner[i][j] = -1;
      }
    }


    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(on_timer()));
    timer->start(500);

    exploding = false;

}

void JumpingCubeWindow::on_timer(){
    if (exploding){
       exploding = checkExplosions();
       if (exploding)update();
    }
}


void JumpingCubeWindow::paintEvent(QPaintEvent *e)
{
  Q_UNUSED(e);
  QPainter qp(this);
  drawLines(&qp);
}


void JumpingCubeWindow::remoteClick(int x, int y)
{
    if (exploding)return;
    int player = 0;
    if(myid==0)player=1;
    if (player != currentplayer)return;
    if (boardOwner[x][y] != -1 && player != boardOwner[x][y]) return;
    idClick(x,y, player);

}

void JumpingCubeWindow::mousePressEvent(QMouseEvent *e){
    if (exploding)return;
    int player = myid;
    if (player != currentplayer)return;
    int winWidth = this->size().rwidth();
    int winHeight = this->size().rheight();
    float cellwidth = winWidth/boardWidth;
    float cellheight = winHeight/boardHeight;
    int x = e->pos().x();
    int y =e->pos().y();
    x/=cellwidth;
    y/=cellheight;
    //TODO send packet here
    std::cerr << "got a mpe\n";
    if (boardOwner[x][y] != -1 && player != boardOwner[x][y]) return;
    emit mClick(x,y);
    idClick(x,y, player);
}

void JumpingCubeWindow::idClick(int x, int y, int player){
    boardOwner[x][y] = player;
    board[x][y]-=1;

    exploding = true;
    currentplayer++;
    if (currentplayer>1)currentplayer = 0;

    update();
}


bool JumpingCubeWindow::checkExplosions()
{
    bool exploded = false;
    for (int x=0;x<boardWidth;x++){
        for (int y=0;y<boardHeight;y++){
            if (board[x][y] < 1){
                exploded = true;
                board[x][y]+=getNumSides(x,y);
                if (x!=0){
                    board[x-1][y]--;
                    boardOwner[x-1][y] = boardOwner[x][y];
                }
                if (x!=boardWidth-1){
                    board[x+1][y]--;
                    boardOwner[x+1][y] = boardOwner[x][y];
                }
                if (y!=0){
                    board[x][y-1]--;
                    boardOwner[x][y-1] = boardOwner[x][y];
                }
                if (y!=boardHeight-1){
                    board[x][y+1]--;
                    boardOwner[x][y+1] = boardOwner[x][y];
                }
                boardOwner[x][y] = -1;

            }
        }
    }
    return exploded;
}

void JumpingCubeWindow::drawLines(QPainter *qp)
{
    QPen pen(Qt::black, 2, Qt::SolidLine);
    QPen rpen(Qt::red, 2, Qt::SolidLine);
    QPen gpen(Qt::green, 2, Qt::SolidLine);
  qp->setPen(pen);
  //qp->drawLine(20, 40, 250, 40);
  int winWidth = this->size().rwidth();
  int winHeight = this->size().rheight();
  float cellwidth = winWidth/boardWidth;
  float cellheight = winHeight/boardHeight;

  for (int x=0;x<boardWidth;x++){
      float xp = x*cellwidth;
      qp->drawLine(xp, 0, xp, winHeight);
  }
  for (int y=0;y<boardHeight;y++){
      float yp = y*cellheight;
      qp->drawLine(0, yp, winWidth, yp);
  }
  for (int x=0;x<boardWidth;x++){
      float xp = x*cellwidth;
      for (int y=0;y<boardHeight;y++){
          float yp = y*cellheight;
          float drawRad = board[x][y]*10;
          if (boardOwner[x][y] == 0)qp->setPen(rpen);
          else if (boardOwner[x][y] == 1)qp->setPen(gpen);
          if (board[x][y] == getNumSides(x,y) and false)
              qp->drawRect(xp+cellwidth/2-drawRad/2, yp+cellheight/2-drawRad/2, drawRad, drawRad);
          else {
              if (board[x][y] %2 == 0)
                  qp->drawRect( xp+cellwidth/2-drawRad/2, yp+cellheight/2-drawRad/2, drawRad, drawRad);
              else
                  qp->drawEllipse(xp+cellwidth/2-drawRad/2, yp+cellheight/2-drawRad/2, drawRad, drawRad);
              //else
              //  qp->drawEllipse(xp+cellwidth/2-drawRad/2, yp+cellheight/2-drawRad/2, drawRad, drawRad);
          }
          std::stringstream ss;
          ss << boardOwner[x][y];
          qp->drawText(xp,yp,ss.str().data());
          qp->setPen(pen);
      }
  }


  /*

  pen.setStyle(Qt::DashLine);
  qp->setPen(pen);
  qp->drawLine(20, 80, 250, 80);

  pen.setStyle(Qt::DashDotLine);
  qp->setPen(pen);
  qp->drawLine(20, 120, 250, 120);

  pen.setStyle(Qt::DotLine);
  qp->setPen(pen);
  qp->drawLine(20, 160, 250, 160);

  pen.setStyle(Qt::DashDotDotLine);
  qp->setPen(pen);
  qp->drawLine(20, 200, 250, 200);

  QVector<qreal> dashes;
  qreal space = 4;

  dashes << 1 << space << 5 << space;

  pen.setStyle(Qt::CustomDashLine);
  pen.setDashPattern(dashes);
  qp->setPen(pen);
  qp->drawLine(20, 240, 250, 240);
  */
}

JumpingCubeWindow::~JumpingCubeWindow()
{
    delete ui;
}

int JumpingCubeWindow::getNumSides(int x, int y)
{
    int sides = 0;
    if (x!=0)sides++;
    if (x!=boardWidth-1)sides++;
    if (y!=0)sides++;
    if (y!=boardHeight-1)sides++;
    return sides;
}
