#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
//Matthew Cohen and Alejandro Gonzales
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene; //make a new scene
    QGraphicsView * view = ui->graphicsView;
    view->setScene(scene); //make the graphics  view the scene
    srand(time(0)); //initialize random
    rows_ = 19;
    cols_ = 19;
    ui->tictac->setVisible(false);
    tictac_minigame(players[0],players[1]);
    int alive_dead =0;
    for(int i = 0; i <= rows_; i++){
        for(int j = 0;j<= cols_;j++){
            cells[i][j] = new Cell();
            cells[i][j]->set_row(i*40);
            cells[i][j]->set_col(j*40);
            alive_dead = rand()%15+0;
            scene->addItem(cells[i][j]);
            if(alive_dead == 1){
                cells[i][j]->set_coin(-5);
            }
            else{
                cells[i][j]->set_coin(10);
            }
        }
    }

    qt_party();
    calc_neighbors();
    //set spaces that are gates (chose which way you go)

    //debug_neighbors();
    for(int i = 0; i <= rows_;i++){
        for(int j = 0; j<= cols_;j++){
            if(cells[i][j]->is_alive()){
                QColor color;
                if(cells[i][j]->get_coins() > 0){
                    color = QColor(0,0,255);

                }
                else{
                    color = QColor(255,0,0);
                }
                if(cells[i][j]->is_gate){
                    color = QColor(255,255,255);

                }
                cells[i][j]->set_color(color);
                cells[i][j]->set_norm(color);
            }
            else{
                QColor color = QColor(211,211,211);
                cells[i][j]->set_color(color);
                cells[i][j]->set_norm(color);
            }
        }
    }

    for(int i = 0; i < 4; i++){
        players[i] = new Player();
    }
    current_player = players[0];
    qDebug() << current_player->roll;
    /*while(current_player->roll != 0){
        qDebug() << "HERE";
        if(!cells[current_player->get_row()][current_player->get_col()]->is_gate){
            qDebug() << "OKKKK";
            move_player(players[0]);
            current_player->roll--;
        }
        else{
            continue_move = true;
            qDebug() << "FUCK" ;
            move_player(players[0]);
            current_player->roll--;
        }
       qDebug() << "ROLL" << current_player->roll;
    }*/

    //std::string out = "yay";
    std::string out = players[0]->get_dir();
    QString outs = QString::fromUtf8(out.c_str());
    qDebug() << outs ;
    scene->update();


}
void MainWindow::move_player(){ //logic to move one space based on what direction youre going NOT FINISHED
    if(ui->gateChoice->currentText() != ""){
    current_player->set_dir(ui->gateChoice->currentText().toLocal8Bit().constData());
    QString dir = QString::fromUtf8(current_player->get_dir().c_str());
    qDebug() <<dir;
    }
    cells[current_player->get_row()][current_player->get_col()]->set_color(cells[current_player->get_row()][current_player->get_col()]->get_norm());
    if(current_player->get_dir() == "right"){

        if(cells[current_player->get_row()][current_player->get_col()+1]->is_gate){
            current_player->set_col(current_player->get_col()+1);
        }
        else if(cells[current_player->get_row()-1][current_player->get_col()]->is_gate){
            current_player->set_row(current_player->get_row()-1);
        }
        else if(cells[current_player->get_row()+1][current_player->get_col()]->is_gate){
             current_player->set_row(current_player->get_row()+1);
        }

        /*else if(cells[current_player->get_row()][current_player->get_col()]->is_gate){
            //Output "Choices"
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[1]){
                    qDebug() << "UP";
                    ui->gateChoice->addItem("up");
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[3]){
                qDebug() << "LEFT";
                ui->gateChoice->addItem("left");
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                qDebug() << "RIGHT";
                ui->gateChoice->addItem("right");
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[6]){
                qDebug() << "DOWN";
                ui->gateChoice->addItem("down");
            }
            if(continue_move){
                if(ui->gateChoice->currentText() == "right"){
                    current_player->set_col(current_player->get_col()+1);
                }
                else if(ui->gateChoice->currentText() == "up"){
                    current_player->set_row(current_player->get_row()-1);
                }
                else if(ui->gateChoice->currentText() == "left"){
                    current_player->set_col(current_player->get_col()-1);
                }
                else if(ui->gateChoice->currentText() == "down"){
                    current_player->set_row(current_player->get_row()+1);
                }
            }

        }*/
        else{
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                current_player->set_col(current_player->get_col()+1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[2]){
                current_player->set_row(current_player->get_row()-1);
                current_player->set_col(current_player->get_col()+1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[7]){
                current_player->set_row(current_player->get_row()+1);
                current_player->set_col(current_player->get_col()+1);
            }
            else{
                if(cells[current_player->get_row()][current_player->get_col()]->neighbors[1]){
                    current_player->set_dir("up");
                }
                else{
                    current_player->set_dir("down");
                }
                move_player();
            }

        }
    }
    else if(current_player->get_dir() == "left"){
        if(cells[current_player->get_row()][current_player->get_col()-1]->is_gate){
            current_player->set_col(current_player->get_col()-1);
        }
        else if(cells[current_player->get_row()-1][current_player->get_col()]->is_gate){
            current_player->set_row(current_player->get_row()-1);
        }
        else if(cells[current_player->get_row()+1][current_player->get_col()]->is_gate){
            current_player->set_row(current_player->get_row()+1);
        }
        /*else if(cells[current_player->get_row()][current_player->get_col()]->is_gate){
            //Output "Choices"
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[1]){
                    qDebug() << "UP";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[3]){
                qDebug() << "LEFT";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                qDebug() << "RIGHT";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[6]){
                qDebug() << "DOWN";
            }
        }*/
        else{
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[3]){
                current_player->set_col(current_player->get_col()-1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[0]){
                current_player->set_row(current_player->get_row()-1);
                current_player->set_col(current_player->get_col()-1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[5]){
                current_player->set_row(current_player->get_row()+1);
                current_player->set_col(current_player->get_col()-1);
            }
            else{
                if(cells[current_player->get_row()][current_player->get_col()]->neighbors[6]){
                    current_player->set_dir("down");
                    move_player();
                }
                else{
                    current_player->set_dir("up");
                    move_player();
                }
            }

        }
    }
    else if(current_player->get_dir() == "up"){

        if(cells[current_player->get_row()-1][current_player->get_col()]->is_gate){
            current_player->set_row(current_player->get_row()-1);
        }
        else if(cells[current_player->get_row()][current_player->get_col()-1]->is_gate){
            current_player->set_col(current_player->get_col()-1);
        }
        else if(cells[current_player->get_row()][current_player->get_col()+1]->is_gate){
            current_player->set_col(current_player->get_col()+1);
        }
        /*else if(cells[current_player->get_row()][current_player->get_col()]->is_gate){
            //Output "Choices"
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[1]){
                    qDebug() << "UP";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[3]){
                qDebug() << "LEFT";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                qDebug() << "RIGHT";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[6]){
                qDebug() << "DOWN";
            }
        }*/
        else{
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[1]){
                current_player->set_row(current_player->get_row()-1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[0]){
                current_player->set_row(current_player->get_row()-1);
                current_player->set_col(current_player->get_col()-1);

            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[2]){
                current_player->set_row(current_player->get_row()-1);
                current_player->set_col(current_player->get_col()+1);
            }
            else{
                if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                    current_player->set_dir("right");
                    move_player();
                }
                else{
                    current_player->set_dir("left");
                    move_player();
                }
            }

        }

    }
    else if(current_player->get_dir()== "down"){
        if(current_player->get_row() == rows_){
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                current_player->set_dir("right");
                move_player();
            }
            else{
                current_player->set_dir("left");
            }
        }
        else if(cells[current_player->get_row()+1][current_player->get_col()]->is_gate){
            current_player->set_row(current_player->get_row()+1);
        }
        else if(cells[current_player->get_row()][current_player->get_col()-1]->is_gate){
            current_player->set_col(current_player->get_col()-1);
        }
        else if(cells[current_player->get_row()][current_player->get_col()+1]->is_gate){
            current_player->set_col(current_player->get_col()+1);
        }
        /*else if(cells[current_player->get_row()][current_player->get_col()]->is_gate){
            //Output "Choices"
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[1]){
                    qDebug() << "UP";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[3]){
                qDebug() << "LEFT";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                qDebug() << "RIGHT";
            }
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[6]){
                qDebug() << "DOWN";
            }
        }*/
        else{
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[6]){
                current_player->set_row(current_player->get_row()+1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[7]){
                current_player->set_row(current_player->get_row()+1);
                current_player->set_col(current_player->get_col()+1);
            }
            else if(cells[current_player->get_row()][current_player->get_col()]->neighbors[5]){
                current_player->set_row(current_player->get_row()+1);
                current_player->set_col(current_player->get_col()-1);

            }
            else{
                if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                    current_player->set_dir("right");

                    move_player();
                }
                else{
                    current_player->set_dir("left");
                }
            }

        }
    }

    int crow = current_player->get_row();
    int ccol = current_player->get_col();
    if(cells[current_player->get_row()][current_player->get_col()]->is_gate){
        if(cells[crow][ccol]->neighbors[1]){
            ui->gateChoice->addItem("up");
        }
        if(cells[crow][ccol]->neighbors[3]){
            ui->gateChoice->addItem("left");
        }
        if(cells[crow][ccol]->neighbors[4]){
            ui->gateChoice->addItem("right");
        }
        if(cells[crow][ccol]->neighbors[6]){
            ui->gateChoice->addItem("down");
        }


    }
    else{
        ui->gateChoice->clear();
    }

    QColor col = QColor(255,0,255);
    current_player->roll--;
    cells[current_player->get_row()][current_player->get_col()]->set_color(col);
    QString crow_ = QString::number(current_player->get_row());
    QString ccol_ = QString::number(current_player->get_col());
    ui->rowLabel->setText(crow_);
    ui->colLabel->setText(ccol_);
    scene->update();
    return;




    }
//sets the board up

void MainWindow::qt_party(){
    cells[1][0]->set_alive(true);
    cells[1][1]->set_alive(true);
    cells[1][2]->set_alive(true);
    cells[1][3]->set_alive(true);
    cells[1][8]->set_alive(true);
    cells[1][9]->set_alive(true);
    cells[1][10]->set_alive(true);
    cells[1][11]->set_alive(true);
    cells[1][12]->set_alive(true);
    cells[1][13]->set_alive(true);
    cells[1][14]->set_alive(true);
    cells[1][15]->set_alive(true);
    cells[1][16]->set_alive(true);
    cells[1][17]->set_alive(true);
    cells[1][0]->set_alive(true);
    cells[1][3]->set_alive(true);
    cells[1][5]->set_alive(true);
    cells[1][12]->set_alive(true);
    cells[1][17]->set_alive(true);
    cells[2][0]->set_alive(true);
    cells[2][3]->set_alive(true);
    cells[2][5]->set_alive(true);
    cells[2][12]->set_alive(true);
    cells[2][17]->set_alive(true);
    cells[3][0]->set_alive(true);
    cells[3][3]->set_alive(true);
    cells[3][4]->set_alive(true);
    cells[3][5]->set_alive(true);
    cells[3][6]->set_alive(true);
    cells[3][12]->set_alive(true);
    cells[3][17]->set_alive(true);
    cells[3][18]->set_alive(true);
    cells[4][0]->set_alive(true);
    cells[4][1]->set_alive(true);
    cells[4][2]->set_alive(true);
    cells[4][3]->set_alive(true);
    cells[4][5]->set_alive(true);
    cells[4][12]->set_alive(true);
    cells[4][18]->set_alive(true);
    cells[5][2]->set_alive(true);
    cells[5][5]->set_alive(true);
    cells[5][10]->set_alive(true);
    cells[5][11]->set_alive(true);
    cells[5][12]->set_alive(true);
    cells[5][13]->set_alive(true);
    cells[5][14]->set_alive(true);
    cells[5][18]->set_alive(true);
    cells[6][2]->set_alive(true);
    cells[6][3]->set_alive(true);
    cells[6][5]->set_alive(true);
    cells[6][6]->set_alive(true);
    cells[6][10]->set_alive(true);
    cells[6][14]->set_alive(true);
    cells[6][15]->set_alive(true);
    cells[6][18]->set_alive(true);
    cells[7][10]->set_alive(true);
    cells[7][15]->set_alive(true);
    cells[7][18]->set_alive(true);
    //cells[8][8]->set_alive(true);
    cells[8][9]->set_alive(true);
    cells[8][10]->set_alive(true);
    cells[8][11]->set_alive(true);
    //cells[8][12]->set_alive(true);
    cells[8][15]->set_alive(true);
    cells[8][16]->set_alive(true);
    cells[8][17]->set_alive(true);
    cells[8][18]->set_alive(true);
    //cells[9][7]->set_alive(true);
    cells[9][8]->set_alive(true);
    cells[9][10]->set_alive(true);
    cells[9][12]->set_alive(true);
    //cells[9][13]->set_alive(true);
    //cells[10][6]->set_alive(true);
    cells[10][7]->set_alive(true);
    cells[10][10]->set_alive(true);
    cells[10][13]->set_alive(true);
    //cells[10][14]->set_alive(true);
    //cells[11][5]->set_alive(true);
    cells[11][6]->set_alive(true);
    //cells[11][9]->set_alive(true);
    cells[11][10]->set_alive(true);
    //cells[11][11]->set_alive(true);
    cells[11][14]->set_alive(true);
    //cells[11][15]->set_alive(true);
    //cells[12][4]->set_alive(true);
    cells[12][5]->set_alive(true);
    //cells[12][8]->set_alive(true);
    cells[12][10]->set_alive(true);
    //cells[12][12]->set_alive(true);
    cells[12][15]->set_alive(true);
    //cells[12][16]->set_alive(true);
    cells[13][4]->set_alive(true);
    //cells[13][7]->set_alive(true);
    cells[13][10]->set_alive(true);
    //cells[13][13]->set_alive(true);
    cells[13][16]->set_alive(true);
    //cells[14][0]->set_alive(true);
    cells[14][1]->set_alive(true);
    cells[14][2]->set_alive(true);
    cells[14][3]->set_alive(true);
    cells[14][4]->set_alive(true);
    cells[14][5]->set_alive(true);
    cells[14][6]->set_alive(true);
    cells[14][7]->set_alive(true);
    cells[14][8]->set_alive(true);
    cells[14][9]->set_alive(true);
    cells[14][10]->set_alive(true);
    cells[14][11]->set_alive(true);
    cells[14][12]->set_alive(true);
    cells[14][13]->set_alive(true);
    cells[14][14]->set_alive(true);
    cells[14][15]->set_alive(true);
    cells[14][16]->set_alive(true);
    cells[15][1]->set_alive(true);
    cells[15][4]->set_alive(true);
    //cells[15][7]->set_alive(true);
    cells[15][10]->set_alive(true);
    //cells[15][13]->set_alive(true);
    cells[15][16]->set_alive(true);
    cells[16][1]->set_alive(true);
    //cells[16][4]->set_alive(true);
    cells[16][5]->set_alive(true);
    //cells[16][8]->set_alive(true);
    cells[16][10]->set_alive(true);
    //cells[16][12]->set_alive(true);
    cells[16][15]->set_alive(true);
    //cells[16][16]->set_alive(true);
    cells[17][1]->set_alive(true);
    //cells[17][5]->set_alive(true);
    cells[17][6]->set_alive(true);
    //cells[17][9]->set_alive(true);
    cells[17][10]->set_alive(true);
    //cells[17][11]->set_alive(true);
    cells[17][14]->set_alive(true);
    //cells[17][15]->set_alive(true);
    cells[18][1]->set_alive(true);
    //cells[18][6]->set_alive(true);
    cells[18][7]->set_alive(true);
    cells[18][10]->set_alive(true);
    cells[18][13]->set_alive(true);
    //cells[18][14]->set_alive(true);
   // cells[19][1]->set_alive(true);
    //cells[19][7]->set_alive(true);
    cells[18][8]->set_alive(true);
    cells[18][9]->set_alive(true);
    //cells[18][10]->set_alive(true);
    cells[18][11]->set_alive(true);
    cells[18][12]->set_alive(true);
    //cells[19][13]->set_alive(true);
    cells[14][4]->is_gate = true;
    cells[14][10]->is_gate = true;
    cells[14][16]->is_gate = true;
    cells[18][10]->is_gate = true;
    cells[8][10]->is_gate = true;
    cells[5][12]->is_gate = true;
    cells[1][12]->is_gate = true;
    cells[3][5]->is_gate = true;
    cells[3][3]->is_gate = true;
    cells[4][2]->is_gate = true;
}
//fills each cells neighbor array
void MainWindow::calc_neighbors(){
    for(int i = 0; i <= rows_;i++){
        for(int j=0;j<= cols_;j++){
            //cells[i][j]->alive_neigh->clear();
            for(int k = 0; k <8; k++){
                cells[i][j]->neighbors[k] = 0;
            }
            if(i == 0){ // first row
                if(j == 0){//first row + first column [0][0]
                    if(cells[0][1]->is_alive()){ //change to avoid hardcode
                        cells[i][j]->neighbors[4] = 1;
                    }
                    if(cells[1][0]->is_alive()){
                        cells[i][j]->neighbors[6] = 1;

                    }
                    if(cells[1][1]->is_alive()){
                        cells[i][j]->neighbors[7] = 1;
                    }
                    /*if(cells[rows_][cols_]->is_alive()){
                       cells[i][j]->neighbors[0] = 1;
                    }
                    if(cells[rows_][0]->is_alive()){
                        cells[i][j]->neighbors[1] = 1;
                    }
                    if(cells[rows_][1]->is_alive()){
                       cells[i][j]->neighbors[2] = 1;
                    }
                    if(cells[0][cols_]->is_alive()){
                        cells[i][j]->neighbors[3] = 1;

                    }
                    if(cells[1][cols_]->is_alive()){
                        cells[i][j]->neighbors[5] = 1;
                    }*/

                    //qDebug() << cells[0][0]->neighbors[6];
                }
                else if(j==cols_){//first row + last column[0][19]
                    if(cells[0][cols_-1]->is_alive()){
                        cells[i][j]->neighbors[3] = 1;
                    }
                    if(cells[1][cols_-1]->is_alive()){
                        cells[i][j]->neighbors[5] = 1;
                    }
                    if(cells[1][cols_]->is_alive()){
                        cells[i][j]->neighbors[6] = 1;
                    }
                    /*if(cells[rows_][cols_-1]->is_alive()){
                        cells[i][j]->neighbors[0] = 1;
                    }
                    if(cells[rows_][cols_]->is_alive()){
                        cells[i][j]->neighbors[1] = 1;
                    }
                    if(cells[rows_][0]->is_alive()){
                        cells[i][j]->neighbors[2] = 1;
                    }
                    if(cells[0][0]->is_alive()){
                        cells[i][j]->neighbors[4] = 1;
                    }
                    if(cells[1][0]->is_alive()){
                        cells[i][j]->neighbors[7] = 1;
                    }*/

                    //qDebug() << i << " "<< j;

                }
                else{//all othere first row
                    if(cells[0][j-1]->is_alive()){
                        cells[i][j]->neighbors[3] = 1;
                    }
                    if(cells[0][j+1]->is_alive()){
                       cells[i][j]->neighbors[4] = 1;
                    }
                    if(cells[1][j-1]->is_alive()){
                        cells[i][j]->neighbors[5] = 1;
                    }
                    if(cells[1][j]->is_alive()){
                        cells[i][j]->neighbors[6] = 1;
                    }
                    if(cells[1][j+1]->is_alive()){
                        cells[i][j]->neighbors[7] = 1;
                    }
                    /*if(cells[rows_][j-1]->is_alive()){
                       cells[i][j]->neighbors[0] = 1;
                    }
                    if(cells[rows_][j]->is_alive()){
                        cells[i][j]->neighbors[1] = 1;
                    }
                    if(cells[rows_][j+1]->is_alive()){
                        cells[i][j]->neighbors[0] = 1;
                    }*/

                    //qDebug() << i << " "<< j;

                }
            }
            else if(i == rows_){//last row
                if(j == 0){//last row + first column [9][0]
                    if(cells[rows_][1]->is_alive()){
                        cells[i][j]->neighbors[4] = 1;
                    }
                    if(cells[rows_-1][0]->is_alive()){
                        cells[i][j]->neighbors[1] = 1;
                    }
                    if(cells[rows_-1][1]->is_alive()){
                        cells[i][j]->neighbors[2] = 1;
                    }
                    /*if(cells[0][cols_]->is_alive()){
                        cells[i][j]->neighbors[5] = 1;
                    }
                    if(cells[0][1]->is_alive()){
                        cells[i][j]->neighbors[7] = 1;
                    }
                    if(cells[0][0]->is_alive()){
                       cells[i][j]->neighbors[6] = 1;
                    }
                    if(cells[rows_-1][cols_]->is_alive()){
                        cells[i][j]->neighbors[0] = 1;
                    }
                    if(cells[rows_][cols_]->is_alive()){
                        cells[i][j]->neighbors[3] = 1;
                    }*/

                   // qDebug() << i << " "<< j;

                }
                else if(j==cols_){//last row + last column[9][19]
                    if(cells[rows_][cols_-1]->is_alive()){
                       cells[i][j]->neighbors[3] = 1;
                    }
                    if(cells[rows_-1][cols_]->is_alive()){
                       cells[i][j]->neighbors[1] = 1;
                    }
                    if(cells[rows_-1][cols_-1]->is_alive()){
                       cells[i][j]->neighbors[0] = 1;
                    }
                    /*if(cells[0][0]->is_alive()){
                        cells[i][j]->neighbors[7] = 1;
                    }
                    if(cells[rows_][0]->is_alive()){
                        cells[i][j]->neighbors[4] = 1;
                    }
                    if(cells[rows_-1][0]->is_alive()){
                       cells[i][j]->neighbors[2] = 1;
                    }
                    if(cells[0][cols_]->is_alive()){
                       cells[i][j]->neighbors[6] = 1;
                    }
                    if(cells[0][cols_-1]->is_alive()){
                        cells[i][j]->neighbors[5] = 1;
                    }*/

                    //qDebug() << i << " "<< j;


                }
                else{//all othere last row
                    if(cells[rows_][j-1]->is_alive()){
                        cells[i][j]->neighbors[3] = 1;
                    }
                    if(cells[rows_][j+1]->is_alive()){
                        cells[i][j]->neighbors[4] = 1;
                    }
                    if(cells[rows_-1][j-1]->is_alive()){
                        cells[i][j]->neighbors[0] = 1;
                    }
                    if(cells[rows_-1][j]->is_alive()){
                        cells[i][j]->neighbors[1] = 1;
                    }
                    if(cells[rows_-1][j+1]->is_alive()){
                        cells[i][j]->neighbors[0] = 1;
                    }
                    /*if(cells[0][j-1]->is_alive()){
                        cells[i][j]->neighbors[5] = 1;
                    }
                    if(cells[0][j]->is_alive()){
                        cells[i][j]->neighbors[6] = 1;
                    }
                    if(cells[0][j+1]->is_alive()){
                        cells[i][j]->neighbors[0] = 1;
                    }*/

                    //qDebug() << i << " "<< j;


                }
            }

            else if(j == 0){
                //qDebug() << "first col" ;
                if(cells[i+1][0]->is_alive()){
                    cells[i][j]->neighbors[6] = 1;
                }
                if(cells[i-1][0]->is_alive()){
                    cells[i][j]->neighbors[1] = 1;
                }
                if(cells[i-1][1]->is_alive()){
                    cells[i][j]->neighbors[2] = 1;
                }
                if(cells[i][1]->is_alive()){
                   cells[i][j]->neighbors[4] = 1;
                }
                if(cells[i+1][1]->is_alive()){
                    cells[i][j]->neighbors[7] = 1;
                }
                /*if(cells[i-1][cols_]->is_alive()){
                    cells[i][j]->neighbors[0] = 1;
                }
                if(cells[i][cols_]->is_alive()){
                   cells[i][j]->neighbors[3] = 1;
                }
                if(cells[i+1][cols_]->is_alive()){
                   cells[i][j]->neighbors[5] = 1;
                }*/

                //qDebug() << i << " "<< j;
            }
            else if(j == cols_){
                if(cells[i-1][cols_]->is_alive()){
                    cells[i][j]->neighbors[1] = 1;
                }
                if(cells[i+1][cols_]->is_alive()){
                    cells[i][j]->neighbors[6] = 1;
                }
                if(cells[i-1][cols_-1]->is_alive()){
                    cells[i][j]->neighbors[0] = 1;
                }
                if(cells[i][cols_-1]->is_alive()){
                   cells[i][j]->neighbors[3] = 1;
                }
                if(cells[i+1][cols_-1]->is_alive()){
                    cells[i][j]->neighbors[5] = 1;
                }
                /*if(cells[i-1][0]->is_alive()){
                    cells[i][j]->neighbors[2] = 1;
                }
                if(cells[i][0]->is_alive()){
                    cells[i][j]->neighbors[4] = 1;
                }
                if(cells[i+1][0]->is_alive()){
                    cells[i][j]->neighbors[7] = 1;
                }*/

                //qDebug() << i << " "<< j;

            }
            else{
                if(cells[i-1][j-1]->is_alive()){
                    cells[i][j]->neighbors[0] = 1;
                }
                if(cells[i-1][j]->is_alive()){
                  cells[i][j]->neighbors[1] = 1;
                }
                if(cells[i-1][j+1]->is_alive()){
                    cells[i][j]->neighbors[2] = 1;
                }
                if(cells[i][j-1]->is_alive()){
                    cells[i][j]->neighbors[3] = 1;
                }
                if(cells[i][j+1]->is_alive()){
                    cells[i][j]->neighbors[4] = 1;
                }
                if(cells[i+1][j-1]->is_alive()){
                    cells[i][j]->neighbors[5] = 1;
                }
                if(cells[i+1][j]->is_alive()){
                    cells[i][j]->neighbors[6] = 1;
                }
                if(cells[i+1][j+1]->is_alive()){
                    cells[i][j]->neighbors[7] = 1;
                }

                //qDebug() << i << " "<< j;

            }




            //qDebug()<< cells[i][j]->is_alive();
            //qDebug() << alive_around;
            //qDebug() << cells[i][j]->is_alive_next();
        }
    }

    return;
}
//function to verify corrrect neighbors chosen
void MainWindow::testing(){
    while(testingcount > 0){

    }
}
void MainWindow::debug_neighbors(){
    for(int i = 0; i <= rows_;i++){
        qDebug() << "Row " << i << "/n";
        for(int j = 0; j<= cols_; j++){
            qDebug() << "Cell" << i << " , " << j;
            for(int k = 0; k < 8; k++){
                qDebug() << cells[i][j]->neighbors[k];
            }

        }
    }
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_continueButton_clicked()

{
    if(!test_mode){
    testingcount--;
    if(current_player->roll > 0){
        continue_move = true;
        move_player();
        QString dir = QString::fromUtf8(current_player->get_dir().c_str());
        qDebug() << dir;
        qDebug() << current_player->roll;
    }
    else{
        current_player->roll = 5;
        int cid = cindex;
        cid = cindex + 1;
        if(cid == 4){
            cid = 0;
        }
        cindex = cid;
        current_player = players[cindex];
        test_mode = true;
        qDebug() << current_player->roll;
        qDebug() << cid ;
    }
}
        return;
}

void MainWindow::on_pushButton_clicked()
{
    test_mode = false;
}
int MainWindow::tictac_minigame(Player *p1, Player *p2){
    min_game_current = 0;
    ui->tictac->show();
    counter = 0;
    ui->tic1->setText("1");
    ui->tic2->setText("2");
    ui->tic3->setText("3");
    ui->tic4->setText("4");
    ui->tic5->setText("5");
    ui->tic6->setText("6");
    ui->tic7->setText("7");
    ui->tic8->setText("8");
    ui->tic9->setText("9");
    minp1 = p1;
    minp2 = p2;
}

void MainWindow::check_tictac(Player *p1, Player *p2){
    int state = -1; //counts winning player

        if (ui->tic1->text() == ui->tic2->text() && ui->tic2->text() == ui->tic3->text()){

            state =  min_game_current;
            }
        else if (ui->tic4->text() == ui->tic5->text() && ui->tic5->text() == ui->tic6->text()){
            state =  min_game_current;
            }
        else if (ui->tic7->text() == ui->tic8->text() && ui->tic8->text() == ui->tic9->text()){

            state =  min_game_current;
            }
        else if (ui->tic1->text() == ui->tic4->text() && ui->tic4->text() == ui->tic7->text()){

            state =  min_game_current;
            }
        else if (ui->tic2->text() == ui->tic5->text() && ui->tic5->text() == ui->tic8->text()){

            state =  min_game_current;
            }
        else if (ui->tic3->text() == ui->tic6->text() && ui->tic6->text() == ui->tic9->text()){

            state =  min_game_current;
            }

        else if (ui->tic1->text() == ui->tic5->text() && ui->tic5->text() == ui->tic9->text()){
            state =  min_game_current;
            }

        else if (ui->tic3->text() == ui->tic5->text() && ui->tic5->text() == ui->tic7->text()){
            state =  min_game_current;
            }

        if(state == 0){
            p2->add_coins(10);
            ui->logText->setText("p2 win");
            ui->tictac->hide();

        }
        else if(state == 1){
            p1->add_coins(10);
            ui->logText->setText("p1 win");
            ui->tictac->hide();
        }
        else {
            counter ++;
        }
        if(counter == 9){
            //p1->add_coins(5);
            //p2->add_coins(5);
            ui->logText->setText("Tied Game");
            ui->tictac->hide();
        }

}



void MainWindow::on_tic1_clicked()
{
    if(ui->tic1->text()!="X" &&ui->tic1->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic1->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic1->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic2_clicked()
{
    if(ui->tic2->text()!="X" &&ui->tic2->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic2->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic2->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic3_clicked()
{
    if(ui->tic3->text()!="X" &&ui->tic3->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic3->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic3->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic4_clicked()
{
    if(ui->tic4->text()!="X" &&ui->tic4->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic4->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic4->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic5_clicked()
{
    if(ui->tic5->text()!="X" &&ui->tic5->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic5->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic5->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic6_clicked()
{
    if(ui->tic6->text()!="X" &&ui->tic6->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic6->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic6->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic7_clicked()
{
    if(ui->tic7->text()!="X" &&ui->tic7->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic7->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic7->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic8_clicked()
{
    if(ui->tic8->text()!="X" &&ui->tic8->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic8->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic8->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}

void MainWindow::on_tic9_clicked()
{
    if(ui->tic9->text()!="X" && ui->tic9->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic9->setText("X");
        }
        if(min_game_current == 1 ){
            ui->tic9->setText("O");
        }
    }
    min_game_current = !min_game_current;
    check_tictac(minp1, minp2);
}
