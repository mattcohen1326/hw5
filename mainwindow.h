#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QTimer>
#include <QMainWindow>
#include <QTimer>
#include "cell.h"
#include "player.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Player * players[4];
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Cell * cells[20][20];
    void qt_party();
    void calc_neighbors();
    int rows_;
    int cols_;
    void debug_neighbors();
    void move_player(Player * cplayer);

};

#endif // MAINWINDOW_H
