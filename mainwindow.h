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
#include <player.h>
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
    void tictac_minigame(Player * p1, Player *p2);
    int check_tictac(Player *p1, Player *p2);
    void play();
    void start_game();
    bool game_started = false;
    bool simulation = false;
    bool use_item = false;
    bool firstgame = true;
    bool beginning = true;
    bool tictac = true;
    void reset_tic();
    void simulate();
    void most_coins();
    void calculate_winner();
    void update_graph(QGraphicsView * view2);

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
    void guesser_game(Player *p1, Player *p2);

    void on_simulateButton_clicked();

    void on_checkGuess_clicked();

    void on_useItem_clicked();

private:
    int turns = 2;
    Player * players[4];
    Player * current_player;
    Player * winner;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QGraphicsView * chartview;
    void simulate_turn();
    Cell * cells[20][20];
    bool itemsfilled;
    void qt_party();
    void calc_neighbors();
    int rows_ = 19;
    int cols_ = 19;
    void move_player();
    bool min_game_current;
    Player *minp1;
    Player *minp2;
    int counter = 0;
    int guess_answer;
    bool can_check;


};

#endif // MAINWINDOW_H
