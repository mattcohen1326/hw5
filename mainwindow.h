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
    int cindex = 0;
    int testingcount = 10;
    bool rollmode = true;
    bool minigamemode = false;
    void updateDisplay();
    ~MainWindow();
    int tictac_minigame(Player * p1, Player *p2);
    void check_tictac(Player *p1, Player *p2);
    void play();
    void start_game();
    bool game_started = false;
    bool use_item = false;
    bool firstgame = true;
private slots:

    void on_continueButton_clicked();
    void on_rollButton_clicked();
    void on_tic1_clicked();
    void on_tic2_clicked();
    void on_tic3_clicked();
    void on_tic4_clicked();
    void on_tic5_clicked();
    void on_tic6_clicked();
    void on_tic7_clicked();
    void on_tic8_clicked();
    void on_tic9_clicked();

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
    bool min_game_current;
    Player *minp1;
    Player *minp2;
    int counter = 0;


};

#endif // MAINWINDOW_H
