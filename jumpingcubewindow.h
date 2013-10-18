#ifndef JUMPINGCUBEWINDOW_H
#define JUMPINGCUBEWINDOW_H

#include <QMainWindow>


#include <QTimer>


namespace Ui {
class JumpingCubeWindow;
}

class JumpingCubeWindow : public QMainWindow
{
    Q_OBJECT

public:
    int currentplayer;
    int myid;

    int boardWidth;
    int boardHeight;

    int **board;
    int **boardOwner;

    bool exploding;

    virtual void remoteClick(int x,int y);

    std::string peerid;
    explicit JumpingCubeWindow(QWidget *parent = 0);
    ~JumpingCubeWindow();
signals:
    void mClick(int x, int y);
private slots:
    void on_timer();
private:
    QTimer *timer;
    Ui::JumpingCubeWindow *ui;
    virtual int getNumSides(int x, int y);
    virtual bool checkExplosions();
    virtual void idClick(int x, int y, int player);

protected:
  void paintEvent(QPaintEvent *event);
  void drawLines(QPainter *qp);
  virtual void mousePressEvent(QMouseEvent *e);
};

#endif // JUMPINGCUBEWINDOW_H
