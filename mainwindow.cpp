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
    scene2 = new QGraphicsScene;
    QGraphicsView * view2 = ui->minigame;
    view2->setScene(scene2);

    chartview = view2;//initialize random
    ui->tictac->hide();
    ui->guesserGame_2->hide();
    ui->graphLayout->setVisible(false);
    qt_party(); //sets up the board
    calc_neighbors(); //assigns all cells their neighbor
    current_player = players[0];//player 1 is the current player to start
    //qDebug() << current_player->roll;
    //qDebug() << outs ;
    start_game();//peoples cpu options
    scene->update();


}
/*fills the
 * gatechoice with a choice of how many cpus
 * */
void MainWindow::start_game(){
    ui->logText->setText("Chose How many human players you will have");
    ui->gateChoice->addItem("0");
    ui->gateChoice->addItem("1");
    ui->gateChoice->addItem("2");
    ui->gateChoice->addItem("3");
    ui->gateChoice->addItem("4");

}
//depending on players direction and the available neighbors, a player is moved a space if their direction
//has no options then a new direction is set and move player is called again
void MainWindow::move_player(){ //logic to move one space based on what direction youre going NOT FINISHED
    current_player = players[cindex];
    //set their new direction
    if(ui->gateChoice->currentText() != "" && ui->gateChoice->currentText() != "1" && ui->gateChoice->currentText() != "2" && ui->gateChoice->currentText() != "3" && ui->gateChoice->currentText() != "4" && ui->gateChoice->currentText()!="0"){
    current_player->set_dir(ui->gateChoice->currentText().toLocal8Bit().constData());
    //QString dir = QString::fromUtf8(current_player->get_dir().c_str());
    //qDebug() <<dir;
    }
    //set direction to first choice if its a cpu
    if(!current_player->is_human()){
        for(int i = 0; i < ui->gateChoice->count();i++){
            if(current_player->get_first() == ui->gateChoice->itemText(i).toUtf8().constData()){
                    current_player->set_dir(ui->gateChoice->itemText(i).toUtf8().constData());
            }
    }
    }
    bool changecolor = true; //checks to see if other players are on the previous square as to not change its color
    for(int i = 0; i < 4; i++){
        if(current_player->id != players[i]->id){
            if((current_player->get_row() == players[i]->get_row()) && (current_player->get_col() == players[i]->get_col())){
                    //qDebug() << "ok";
                    cells[current_player->get_row()][current_player->get_col()]->set_color(players[i]->get_color());
                    changecolor = false;
                    break;
            }
            else{
                continue;
            }

        }

    }
    //switch spot back to original if no space
    if(changecolor){
         cells[current_player->get_row()][current_player->get_col()]->set_color(cells[current_player->get_row()][current_player->get_col()]->get_norm());
    }
    //if the player is going right
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
                return;
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
                    return;
                }
                else{
                    current_player->set_dir("up");
                    move_player();
                    return;
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
                    return;
                }
                else{
                    current_player->set_dir("left");
                    move_player();
                    return;
                }
            }

        }

    }
    else if(current_player->get_dir()== "down"){
        if(current_player->get_row() == rows_){
            if(cells[current_player->get_row()][current_player->get_col()]->neighbors[4]){
                current_player->set_dir("right");
                move_player();
                return;
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
                    return;
                }
                else{
                    current_player->set_dir("left");
                }
            }

        }
    }

    int crow = current_player->get_row();
    int ccol = current_player->get_col();
    //if the new spot is a gate the appropriate gate choices are added
    if(cells[current_player->get_row()][current_player->get_col()]->is_gate){
        if(cells[crow][ccol]->neighbors[1]){
            if(current_player->get_dir()!="down"){
                ui->gateChoice->addItem("up");
            }
        }
        if(cells[crow][ccol]->neighbors[3]){
            if(current_player->get_dir()!="right"){
                ui->gateChoice->addItem("left");
            }
        }
        if(cells[crow][ccol]->neighbors[4]){
            if(current_player->get_dir()!="left"){
                ui->gateChoice->addItem("right");
            }
        }
        if(cells[crow][ccol]->neighbors[6]){
            if(current_player->get_dir()!="up"){
                ui->gateChoice->addItem("down");
            }
        }


    }
    else{
        ui->gateChoice->clear();
    }
    //new space color set and roll decremented if it is there last move add the appropriate coins
    cells[current_player->get_row()][current_player->get_col()]->set_color(current_player->get_color());
    current_player->roll--;
    ui->rollLabel->setText(QString("Roll: ").append(QString::number(current_player->roll)));
    QString crow_ = QString::number(current_player->get_row());
    QString ccol_ = QString::number(current_player->get_col());
    ui->rowLabel->setText(crow_);
    ui->colLabel->setText(ccol_);
    if(current_player->roll == 0){
        //qDebug() << cells[current_player->get_row()][current_player->get_col()]->get_coins();
        current_player->add_coins(cells[current_player->get_row()][current_player->get_col()]->get_coins());
    }
    //logic for creating a new star somewhere else and sets the cpus first choice to where the star  is
    if(cells[current_player->get_row()][current_player->get_col()]->is_star){
            current_player->add_stars();
            cells[current_player->get_row()][current_player->get_col()]->is_star =false;
            Cell * temp;
            srand(time(0));
            int trow = 15;
            int tcol = 10;
            while(!temp->is_alive()){
                 trow = rand()%rows_+0;
                 tcol = rand()%cols_+0;
                 temp = cells[trow][tcol];
            }
            cells[trow][tcol]->is_star = true;
            QColor yel = QColor(255,255,0);
            cells[trow][tcol]->set_color(yel);
            qDebug() << "STAR ROW :" << trow;
            qDebug() << "STAR COL :" << tcol;
            for(int i = 0; i < 4; i++){
                if(!players[i]->is_human()){
                    if(tcol < 10){
                        players[i]->set_first("left");
                    }
                    else{
                        players[i]->set_first("right");
                    }
                }
            }
    }
    scene->update();
    return;




    }
//sets the board up pretty simple
void MainWindow::qt_party(){
    srand(time(0));
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
    //qDebug() << "here ";
    //cells[1][0]->set_alive(true);
    //cells[1][1]->set_alive(true);
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
    //cells[1][0]->set_alive(true);
    //cells[1][3]->set_alive(true);
    //cells[1][5]->set_alive(true);
    cells[1][12]->set_alive(true);
    cells[1][17]->set_alive(true);
    //cells[2][0]->set_alive(true);
    //cells[2][2]->set_alive(true);
    //cells[2][3]->set_alive(true);
    //cells[2][5]->set_alive(true);
    cells[2][12]->set_alive(true);
    cells[2][17]->set_alive(true);
    //cells[3][0]->set_alive(true);
    //cells[3][3]->set_alive(true);
    //cells[3][4]->set_alive(true);
    //cells[3][5]->set_alive(true);
    //cells[3][6]->set_alive(true);
    //cells[3][2]->set_alive(true);
    cells[3][12]->set_alive(true);
    //cells[3][17]->set_alive(true);
    cells[3][18]->set_alive(true);
    //cells[4][0]->set_alive(true);
    //cells[4][1]->set_alive(true);
    //cells[4][2]->set_alive(true);
    //cells[4][3]->set_alive(true);
    //cells[4][5]->set_alive(true);
    cells[4][12]->set_alive(true);
    cells[4][18]->set_alive(true);
    //cells[5][2]->set_alive(true);

    //cells[5][9]->set_alive(true);
    cells[5][10]->set_alive(true);
    cells[5][11]->set_alive(true);
    cells[5][12]->set_alive(true);
    cells[5][13]->set_alive(true);
    cells[5][14]->set_alive(true);
    cells[5][18]->set_alive(true);
    //cells[6][2]->set_alive(true);
    //cells[6][3]->set_alive(true);
    //cells[6][5]->set_alive(true);
    //cells[6][6]->set_alive(true);
    cells[6][10]->set_alive(true);
    //cells[6][14]->set_alive(true);
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
    //cells[4][2]->is_gate = true;
    cells[1][8]->is_star = true;
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
        players[i]->id = i+1;
    }
    //guesser_game(players[0],players[1]);
    players[0]->set_color(QColor(255,0,255));
    players[1]->set_color(QColor(102,255,255));
    players[2]->set_color(QColor(0,255,0));
    players[3]->set_color(QColor(100,100,100));
    cells[1][8]->is_star = true;
    cells[1][8]->set_color(QColor(255,255,0));

}
//fills each cells neighbor array with
// the same logic as the cells in hw4
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

MainWindow::~MainWindow()
{
    delete ui;
}

//updates all players values on the display
void MainWindow::updateDisplay(){
    ui->p1name->setText("Player 1");
    QString s = QString::number(players[0]->get_stars());
    QString s2 = s.prepend("Stars: ");
    ui->p1stars->setText(s2);
    QString c = QString::number(players[0]->get_coins());
    QString c2 = c.prepend("Coins: ");
    ui->p1coins->setText(c2);

    ui->p2name->setText("Player 2");
    QString s_2 = QString::number(players[1]->get_stars());
    QString s2_2 = s_2.prepend("Stars: ");
    ui->p2stars->setText(s2_2);
    QString c_2 = QString::number(players[1]->get_coins());
    QString c2_2 = c_2.prepend("Coins: ");
    ui->p2coins->setText(c2_2);

    ui->p3name->setText("Player 3");
    QString s_3 = QString::number(players[2]->get_stars());
    QString s2_3 = s_3.prepend("Stars: ");
    ui->p3stars->setText(s2_3);
    QString c_3 = QString::number(players[2]->get_coins());
    QString c2_3 = c_3.prepend("Coins: ");
    ui->p3coins->setText(c2_3);

    ui->p4name->setText("Player 4");
    QString s_4 = QString::number(players[3]->get_stars());
    QString s2_4 = s_4.prepend("Stars: ");
    ui->p4stars->setText(s2_4);
    QString c_4 = QString::number(players[3]->get_coins());
    QString c2_4 = c_4.prepend("Coins: ");
    ui->p4coins->setText(c2_4);

}
//continue button clicked is the main driver of action
void MainWindow::on_continueButton_clicked()
{
    if(turns == 0 && !simulation){
        game_started = false;
        calculate_winner();
        QString temp = QString("Winners : ");
        for(int i = 0;i < 4; i++){
            if(players[i]->get_wins() >= 1){
                temp.append(QString::number(i)).append(" , ");
            }
        }
        ui->logText->setText(temp);
        return;
        //if all turns have been used end the game
    }
    updateDisplay();//everytime continue is clicked update no matter what
    //set the appropriate amount of humans
    if(!game_started){
        if(ui->gateChoice->currentText()=="1"){
                   players[0]->set_human(true);
               }
               else if(ui->gateChoice->currentText()=="2"){
                   players[0]->set_human(true);
                   players[1]->set_human(true);
               }
               else if(ui->gateChoice->currentText()=="3"){
                   players[0]->set_human(true);
                   players[1]->set_human(true);
                   players[2]->set_human(true);
               }
               else if (ui->gateChoice->currentText()=="4"){
                   players[0]->set_human(true);
                   players[1]->set_human(true);
                   players[2]->set_human(true);
                   players[3]->set_human(true);
               }
               else if(ui->gateChoice->currentText() == "0"){
                   game_started = false;
                   simulation = true;
               }
        qDebug() << players[0]->is_human();
        qDebug() << players[1]->is_human();
        qDebug() << players[2]->is_human();
        qDebug() << players[3]->is_human();
        //time for p1 to roll the dice
        rollmode = true;
        ui->logText->setText("Roll Die");
    }
    else{
        if(!rollmode && !minigamemode){
            //if the player has rolled then move until no more rolls
            if(players[cindex]->roll > 0){
                move_player();
            }
            else{
                //switch the cindex to refect the new current player
                cindex = cindex + 1;
                ui->gateChoice->clear();
                if(cindex == 4){
                    minigamemode = true;
                    cindex = 0;
                }
                else{
                    rollmode = true;
                }
                //qDebug() << cindex ;
                ui->playerLabel->setText(QString("Player: ").append(QString::number(cindex+1)));
                if(!minigamemode){
                    ui->logText->setText("Roll Die");
                    //qDebug() << "Weird ";
                    if(!players[cindex]->is_human()){
                        //qDebug() << "hmm" ;
                        simulate_turn();
                    }

                }
            }
        }
        else if(minigamemode){
            //plaly tictactoe and guessing game alternating every turn
            if(tictac){
                ui->guesserGame_2->hide();
                if(firstgame){
                    ui->logText->setText("P1 and P2 tic tac toe time");
                    tictac_minigame(players[0],players[1]);
                }
                else{
                    tictac_minigame(players[2],players[3]);
                }
            }
            else{
                if(firstgame){
                    guesser_game(players[0],players[1]);
                }
                else{
                    guesser_game(players[2],players[3]);//second game p2 p4
                }
            }
        }
    }

}

//operation used to simulate a turn by ai
void MainWindow::simulate_turn(){
    on_rollButton_clicked();
    while(players[cindex]->roll > 0){
        move_player();
    }
    //on_continueButton_clicked();
}
//create a new random dice roll
void MainWindow::on_rollButton_clicked()
{
    if(rollmode){
        if(!game_started && !simulation){
            game_started = true;
        }
        srand(time(0));
        int newroll = rand()%(6+players[cindex]->rollupgrade)+1;
        players[cindex]->roll = newroll;
        players[cindex]->rollupgrade = 0;
        ui->rollLabel->setText(QString("Roll: ").append(QString::number(newroll)));
        rollmode = false;
        ui->logText->setText("press continue until out of moves");
    }
}
void MainWindow::tictac_minigame(Player *p1, Player *p2){
    rollmode = false;
    min_game_current = 0;
    ui->tictac->show();
    counter = 0;
    reset_tic();
    minp1 = p1;
    minp2 = p2;
    int r = (rand()%4)+1;
//    p1->set_human(false);
//    p2->set_human(true);

    // ai randomizer

    if(!p2->is_human() && !p1->is_human()){
    if(r == 1 && !p1->is_human()&& ui->tic5->text()!="X" && ui->tic5->text()!="O"){
        ui->tic5->setText("X");
        counter ++;
        min_game_current = !min_game_current;
    }
    else if (r == 2 && !p1->is_human()&& ui->tic1->text()!="X" && ui->tic1->text()!="O") {
        ui->tic1->setText("X");
        counter ++;
        min_game_current = !min_game_current;
    }
    else if (r == 3 && !p1->is_human()&& ui->tic4->text()!="X" && ui->tic4->text()!="O") {
        ui->tic4->setText("X");
        counter ++;
        min_game_current = !min_game_current;
    }
    else if (r == 4 && !p1->is_human()&& ui->tic2->text()!="X" && ui->tic2->text()!="O") {
        ui->tic2->setText("X");
        counter ++;
        min_game_current = !min_game_current;
    }
    }

    //ai vs ai
    if(!p2->is_human() && !p1->is_human()){
        for(int i = 0; i<9 ;i++){
            if(!p1->is_human() && min_game_current == 0){
               if(ui->tic1->text()=="1"){
                   ui->tic1->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic2->text()=="2"){
                   ui->tic2->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic3->text()=="3"){
                   ui->tic3->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic4->text()=="4"){
                   ui->tic4->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic5->text()=="5"){
                   ui->tic5->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic6->text()=="6"){
                   ui->tic6->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic7->text()=="7"){
                   ui->tic7->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic8->text()=="8"){
                   ui->tic8->setText("X");
                   min_game_current = !min_game_current;

               }
               else if(ui->tic9->text()=="9"){
                   ui->tic9->setText("X");
                   min_game_current = !min_game_current;

               }
            }
            if(check_tictac(p1,p2)==1){
                break;
            }



               if(!p2->is_human() && min_game_current == 1){
                   //delay();
                   if(ui->tic1->text()=="1"){
                       ui->tic1->setText("O");
                       min_game_current = !min_game_current;

                   }
                   else if(ui->tic2->text()=="2"){
                       ui->tic2->setText("O");
                       min_game_current = !min_game_current;
                       \
                   }
                   else if(ui->tic3->text()=="3"){
                       ui->tic3->setText("O");
                       min_game_current = !min_game_current;

                   }
                   else if(ui->tic4->text()=="4"){
                       ui->tic4->setText("O");
                       min_game_current = !min_game_current;

                   }
                   else if(ui->tic5->text()=="5"){
                       ui->tic5->setText("O");
                       min_game_current = !min_game_current;
                   }
                   else if(ui->tic6->text()=="6"){
                       ui->tic6->setText("O");
                       min_game_current = !min_game_current;

                   }
                   else if(ui->tic7->text()=="7"){
                       ui->tic7->setText("O");
                       min_game_current = !min_game_current;

                   }
                   else if(ui->tic8->text()=="8"){
                       ui->tic8->setText("O");
                       min_game_current = !min_game_current;

                   }
                   else if(ui->tic9->text()=="9"){
                       ui->tic9->setText("O");
                       min_game_current = !min_game_current;

                   }
               }
               if (check_tictac(p1,p2)==1){
                   break;
               }


        }
    }

}

int MainWindow::check_tictac(Player *p1, Player *p2){
    int state = -1; //counts winning player
    counter ++;


       if(!p2->is_human() && p1->is_human() && min_game_current == 0){
           //delay();
           if(ui->tic1->text()=="1"){
               ui->tic1->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic2->text()=="2"){
               ui->tic2->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic3->text()=="3"){
               ui->tic3->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic4->text()=="4"){
               ui->tic4->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic5->text()=="5"){
               ui->tic5->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic6->text()=="6"){
               ui->tic6->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic7->text()=="7"){
               ui->tic7->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic8->text()=="8"){
               ui->tic8->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
           else if(ui->tic9->text()=="9"){
               ui->tic9->setText("O");
               min_game_current = !min_game_current;
               counter++;
           }
   }



   //check p1 win
           if (ui->tic1->text() == ui->tic2->text() && ui->tic2->text() == ui->tic3->text() && ui->tic3->text()=="X"){
               state =  0;
               }
           else if (ui->tic4->text() == ui->tic5->text() && ui->tic5->text() == ui->tic6->text() && ui->tic6->text()=="X"){
               state =  0;
               }
           else if (ui->tic7->text() == ui->tic8->text() && ui->tic8->text() == ui->tic9->text() && ui->tic9->text()=="X"){

               state =  0;
               }
           else if (ui->tic1->text() == ui->tic4->text() && ui->tic4->text() == ui->tic7->text() && ui->tic7->text()=="X"){

               state =  0;
               }
           else if (ui->tic2->text() == ui->tic5->text() && ui->tic5->text() == ui->tic8->text() && ui->tic8->text()=="X"){

               state =  0;
               }
           else if (ui->tic3->text() == ui->tic6->text() && ui->tic6->text() == ui->tic9->text()&& ui->tic9->text()=="X"){

               state =  0;
               }

           else if (ui->tic1->text() == ui->tic5->text() && ui->tic5->text() == ui->tic9->text() && ui->tic9->text()=="X"){
               state =  0;
               }

           else if (ui->tic3->text() == ui->tic5->text() && ui->tic5->text() == ui->tic7->text() && ui->tic7->text()=="X"){
               state =  0;
               }
           //qDebug() << state;
           if(state == 0){
               p1->add_coins(10);
               ui->tictac->hide();
               reset_tic();
               if(firstgame){
                   ui->logText->setText("p1 win : p3 and p4 play next game");
                   counter = 0;
                   firstgame = false;
                   min_game_current = 0;
                   return 1;
               }
               else{
                   ui->logText->setText("p1 win : roll die");
                   firstgame = true;
                   minigamemode = false;
                   rollmode = true;
                   tictac = false;
                   turns--;
                   return 1;
               }
           }
   //check p2 win
           if (ui->tic1->text() == ui->tic2->text() && ui->tic2->text() == ui->tic3->text() && ui->tic3->text()=="O"){

               state =  1;
               }
           else if (ui->tic4->text() == ui->tic5->text() && ui->tic5->text() == ui->tic6->text() && ui->tic6->text()=="O"){
               state =  1;
               }
           else if (ui->tic7->text() == ui->tic8->text() && ui->tic8->text() == ui->tic9->text() && ui->tic9->text()=="O"){

               state =  1;
               }
           else if (ui->tic1->text() == ui->tic4->text() && ui->tic4->text() == ui->tic7->text() && ui->tic7->text()=="O"){

               state =  1;
               }
           else if (ui->tic2->text() == ui->tic5->text() && ui->tic5->text() == ui->tic8->text() && ui->tic8->text()=="O"){

               state =  1;
               }
           else if (ui->tic3->text() == ui->tic6->text() && ui->tic6->text() == ui->tic9->text()&& ui->tic9->text()=="O"){

               state =  1;
               }

           else if (ui->tic1->text() == ui->tic5->text() && ui->tic5->text() == ui->tic9->text() && ui->tic9->text()=="O"){
               state =  1;
               }

           else if (ui->tic3->text() == ui->tic5->text() && ui->tic5->text() == ui->tic7->text() && ui->tic7->text()=="O"){
               state =  1;
               }
        //qDebug() << state;
        if(state == 0){
            p1->add_coins(10);
            ui->tictac->hide();
            reset_tic();
            if(firstgame){
                ui->logText->setText("p1 win : p3 and p4 play next game");
                counter = 0;
                firstgame = false;
                min_game_current = 0;
                return 1;
            }
            else{
                ui->logText->setText("p1 win : roll die");
                counter = 0;
                firstgame = false;
                min_game_current = 0;
                tictac = false;
                turns--;
                return 1;

            }

        }
        else if(state == 1){
            p2->add_coins(10);
            ui->tictac->hide();
            //ui->logText->setText("p2 win : roll die");
            reset_tic();
            ui->tictac->hide();
            if(firstgame){
                ui->logText->setText("p2 win : p3 and p4 play next game");
                counter = 0;
                firstgame = false;
                min_game_current = 0;
                return 1;
            }
            else{
                ui->logText->setText("p2 win : roll die");
                firstgame = true;
                minigamemode = false;
                rollmode = true;
                counter = 0;
                tictac = false;
                turns--;
                return 1;

            }

        }

        else if(counter >= 9 && state == -1){
            p1->add_coins(5);
            p2->add_coins(5);
            reset_tic();
            ui->tictac->hide();
            if(firstgame){
                ui->logText->setText("Tied Game : p3 and p4 play next game");
                counter = 0;
                firstgame = false;
                min_game_current = 0;
                counter = 0;
                return 1;
            }
            else{
                ui->logText->setText("Tied Game : roll die");
                firstgame = true;
                minigamemode = false;
                rollmode = true;
                counter = 0;
                tictac = false;
                turns--;
                return 1;
            }



        }



}



void MainWindow::on_tic1_clicked()
{

    if(ui->tic1->text()!="X" &&ui->tic1->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic1->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic1->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }
    qDebug() << "countbelow";
    qDebug() << counter;

    qDebug() <<"currentp";
    qDebug() << min_game_current;


}

void MainWindow::on_tic2_clicked()
{
    if(ui->tic2->text()!="X" &&ui->tic2->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic2->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic2->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }
    qDebug() << "countbelow";
    qDebug() << counter;

}

void MainWindow::on_tic3_clicked()
{
    if(ui->tic3->text()!="X" &&ui->tic3->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic3->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic3->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }
}

void MainWindow::on_tic4_clicked()
{
    if(ui->tic4->text()!="X" &&ui->tic4->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic4->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic4->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }
}

void MainWindow::on_tic5_clicked()
{
    if(ui->tic5->text()!="X" &&ui->tic5->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic5->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic5->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }


}

void MainWindow::on_tic6_clicked()
{
    if(ui->tic6->text()!="X" &&ui->tic6->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic6->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic6->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }


}

void MainWindow::on_tic7_clicked()
{
    if(ui->tic7->text()!="X" &&ui->tic7->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic7->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic7->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }


}

void MainWindow::on_tic8_clicked()
{
    if(ui->tic8->text()!="X" &&ui->tic8->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic8->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic8->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }
}

void MainWindow::on_tic9_clicked()
{
    if(ui->tic9->text()!="X" && ui->tic9->text()!="O"){
        if(min_game_current == 0 ){
            ui->tic9->setText("X");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
        else if(min_game_current == 1 ){
            ui->tic9->setText("O");
            check_tictac(minp1, minp2);
            min_game_current = !min_game_current;
        }
    }
}

void MainWindow::reset_tic(){
    ui->tic1->setText("1");
    ui->tic2->setText("2");
    ui->tic3->setText("3");
    ui->tic4->setText("4");
    ui->tic5->setText("5");
    ui->tic6->setText("6");
    ui->tic7->setText("7");
    ui->tic8->setText("8");
    ui->tic9->setText("9");
}

void MainWindow::on_simulateButton_clicked()
{
    if(simulation){
    ui->graphLayout->setVisible(true);
    int sturns = 20;
    simulation = true;
    if(!game_started){
        ui->gateChoice->clear();
        ui->gateChoice->addItem("0");
        game_started = true;
        on_continueButton_clicked();
        for(int i = 0; i < sturns; i ++){
            simulate_turn();
            on_continueButton_clicked();
            simulate_turn();
            on_continueButton_clicked();
            simulate_turn();
            on_continueButton_clicked();
            simulate_turn();
            if(tictac){
            on_continueButton_clicked();
            on_continueButton_clicked();
            }
            else{
                on_continueButton_clicked();
                on_checkGuess_clicked();
                on_continueButton_clicked();
                on_checkGuess_clicked();
            }
        }

        ui->simulateButton->setText("reset");
        //most_coins();


    }
    else{
        calculate_winner();
        update_graph(chartview);
        for(int i = 0; i < 4; i++){
            //cells[players[i]->get_row()][players[i]->get_col()]->set_color(cells[players[i]->get_row()][players[i]->get_col()]->get_norm());
            players[i]->set_col(1);
            players[i]->set_row(18);
            players[i]->add_coins(-players[i]->get_coins());
            players[i]->clear_stars();
            updateDisplay();
            players[i]->roll = 0;
            game_started = false;
            ui->simulateButton->setText("Simulate");

        }
        for(int i = 0; i <rows_; i++){
            for(int j = 0; j <cols_;j++){
                //qDebug() << "What";
                if(cells[i][j]->is_alive()){
                cells[i][j]->set_color(cells[i][j]->get_norm());
                cells[i][j]->is_star = false;
                }
            }
        }
        cells[1][8]->is_star = true;
        cells[1][8]->set_color(QColor(255,255,0));
    }

    scene2->update();
    scene->update();
//    for(int i = 0; i <4; i++){
//        qDebug() << players[i]->get_wins();
//    }
    }


}

//initialize guesser game
void MainWindow::guesser_game(Player * p1, Player * p2){
    ui->guesserGame_2->hide();
    ui->guesserGame_2->show();
    ui->actualnum->display(0);
    ui->p1choice->setValue(0);
    ui->p2choice->setValue(0);
    guess_answer = rand()%100+1;
    minp1 = p1;
    minp2 = p2;
    std::string sf = "P";
    sf.append(std::to_string(minp1->get_id()));
    sf.append(" plays P");
    sf.append(std::to_string(minp2->get_id()));
    sf.append(". Choose your numbers.");
    QString qsf = QString::fromStdString(sf);
    ui->logText->setText(qsf);

    std::string l1 = "P";
    l1.append(std::to_string(minp1->get_id()));
    QString ql1 = QString::fromStdString(l1);

    std::string l2 = "P";
    l2.append(std::to_string(minp2->get_id()));
    QString ql2 = QString::fromStdString(l2);


    ui->p1label->setText(ql1);
    ui->p2label->setText(ql2);

    //Ai chooses random number


    if(!players[0]->is_human() && !players[1]->is_human() && !players[2]->is_human() && !players[3]->is_human()){
        on_checkGuess_clicked();
    }
    can_check = true;


}

void MainWindow::on_checkGuess_clicked()
{

    if(!tictac && can_check){
        if(!minp1->is_human()){
            int p1rand = rand()%100+1;
            ui->p1choice->setValue(p1rand);
        }
        if(!minp2->is_human()){
            int p2rand = rand()%100+1;
            ui->p2choice->setValue(p2rand);
        }


    //Set strings to print
    std::string s2 = "P";
    s2.append(std::to_string(minp2->get_id()));
    if((minp1->get_id()==1) && (minp2->get_id()==2)){
        s2.append(" wins 10 coins. Now P3 and P4 play");
    }
    else {
        s2.append(" wins 10 coins. P1 roll the die");

    }
    QString qs2 = QString::fromStdString(s2);

    std::string s1 = "P";
    s1.append(std::to_string(minp1->get_id()));
    if((minp1->get_id()==1) && (minp2->get_id()==2)){
        s1.append(" wins 10 coins. Now P3 and P4 play");
    }
    else {
        s1.append(" wins 10 coins. P1 roll the die");

    }
     QString qs1 = QString::fromStdString(s1);

     std::string st = "Tied Game.";
     if((minp1->get_id()==1) && (minp2->get_id()==2)){
         st.append(" Now P3 and P4 play");
     }
     else {
         st.append(" P1 roll the die");

     }

     QString qst = QString::fromStdString(st);

    //calculate scores
    int p1score = abs(ui->p1choice->value() - guess_answer);
    int p2score = abs(ui->p2choice->value() - guess_answer);

    //check for winner or tie
    if(p1score > p2score){
        minp2->add_coins(10);
        ui->logText->setText(qs2);

        if(firstgame){
            firstgame = false;
        }
        else{
            firstgame = true;
            minigamemode = false;
            tictac = true;
            turns--;
        }

    }
    else if (p2score > p1score) {
        minp1->add_coins(10);
        ui->logText->setText(qs1);
        if(firstgame){
            firstgame = false;
        }
        else{
            firstgame = true;
            minigamemode = false;
            tictac = true;
            turns--;
        }

    }
    else {
        minp1->add_coins(5);
        minp2->add_coins(5);
        ui->logText->setText(qst);
        if(firstgame){
            firstgame = false;
        }
        else{
            firstgame = true;
            minigamemode = false;
            tictac = true;
            turns--;
        }

    }
    rollmode = true;

    ui->actualnum->display(guess_answer);
    }
    can_check = false;
}


void MainWindow::calculate_winner(){

    int max_coins = 0;
    for(int i = 0; i < 4; i++){
        if(players[i]->get_coins() > max_coins){
            max_coins = players[i]->get_coins();
        }
    }
    for(int i = 0; i < 4; i++){
        if(players[i]->get_coins() == max_coins){
            players[i]->add_stars();
            //qDebug() << "Player " << i + 1 << "GEts a star";
        }
    }
    int maxstars = 0;
    for(int i = 0; i < 4; i ++){
        if(players[i]->get_stars() > maxstars){
            maxstars = players[i]->get_stars();
        }
    }
    //qDebug() << "MAX STARS: " << maxstars;
    for(int i = 0; i < 4; i++){
        if(players[i]->get_stars() == maxstars){
            players[i]->add_wins();
            //qDebug() << "PLAYER: " << i << " WINS";
        }
    }
    return;

}

void MainWindow::update_graph(QGraphicsView * view2){

        scene2->clear();
        int tot_wins =0;
        for(int i = 0; i<4; i++){
            tot_wins += players[i]->get_wins();

        }
        ui->lcdNumber->display(players[0]->get_wins());
        ui->lcdNumber_2->display(players[1]->get_wins());
        ui->lcdNumber_3->display(players[2]->get_wins());
        ui->lcdNumber_4->display(players[3]->get_wins());

        int framewidth = view2->frameSize().width()/4-10;
        int frame_height = view2->frameSize().rheight();
        double bar_size = 200/tot_wins;
        for(int i = 0; i<4 ;i++){
            scene2->addRect(QRect(framewidth*i,frame_height- (players[i]->get_wins())*60,framewidth,(players[i]->get_wins()*60)));

        }



}

// a player can use either type of mushroom before a roll, they can only use the hammer if they are the player
//with the least amount of coins
void MainWindow::on_useItem_clicked()
{
    if(rollmode){
        if(!itemsfilled){
            for(int i =  0; i< 3; i++){
                if(!players[cindex]->items[i]->used_){
                    ui->itemChoice->addItem(players[cindex]->items[i]->name);
                }
            }
            itemsfilled = true;
        }
        else{
            if(ui->itemChoice->currentText() == "Large Mushroom"){
                for(int i = 0; i < 3; i++){
                    if(players[cindex]->items[i]->name == "Large Mushroom" && !players[cindex]->items[i]->used_){
                        players[cindex]->items[i]->used_ = true;
                        players[cindex]->rollupgrade = players[cindex]->items[i]->use();
                        qDebug() << players[cindex]->rollupgrade;
                        break;
                    }
                }
            }
            else if(ui->itemChoice->currentText() == "Small Mushroom"){
                for(int i = 0; i < 3; i++){
                    if(players[cindex]->items[i]->name == "Small Mushroom" && !players[cindex]->items[i]->used_){
                        players[cindex]->items[i]->used_ = true;
                        players[cindex]->rollupgrade = players[cindex]->items[i]->use();
                        qDebug() << players[cindex]->rollupgrade;
                        break;
                    }
                }
            }
            else if(ui->itemChoice->currentText() == "Hammer"){
                bool usehammer = true;
                int mincoins = players[cindex]->get_coins();
                for(int i = 0; i < 4;i++){
                    if(players[i]->get_coins() <mincoins){
                        usehammer=false;
                    }
                }
                if(usehammer){
                players[cindex]->items[0]->used_ = true;
                players[cindex]->add_coins(50);
                }
            }
            itemsfilled = false;
            ui->itemChoice->clear();

        }
    }
}
