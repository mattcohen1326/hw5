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
    bool continue_move = false;
    bool test_mode = false;
    int cindex = 0;
    int testingcount = 10;
    ~MainWindow();


private slots:

    void on_continueButton_clicked();

    void on_pushButton_clicked();

private:
    Player * players[4];
    Player * current_player;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Cell * cells[20][20];
    void testing();
    void qt_party();
    void calc_neighbors();
    int rows_;
    int cols_;
    void debug_neighbors();
    void move_player();


};

#endif // MAINWINDOW_H
