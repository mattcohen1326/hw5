#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene; //make a new scene
    QGraphicsView * view = ui->graphicsView;
    view->setScene(scene); //make the graphics  view the scene
    srand(time(0)); //initialize random
    rows_ = 20;
    cols_ = 20;
    for(int i = 0; i < rows_; i++){
        for(int j = 0;j< cols_;j++){
            cells[i][j] = new Cell();
            cells[i][j]->set_row(i*40);
            cells[i][j]->set_col(j*40);

            scene->addItem(cells[i][j]);
        }
    }
    qt_party();
    for(int i = 0; i < rows_;i++){
        for(int j = 0; j< cols_;j++){
            if(cells[i][j]->is_alive()){
                QColor color = QColor(0,0,255);
                cells[i][j]->set_color(color);
            }
            else{
                QColor color = QColor(211,211,211);
                cells[i][j]->set_color(color);
            }
        }
    }
    scene->update();

}
void MainWindow::qt_party(){
    cells[0][0]->set_alive(true);
    cells[0][1]->set_alive(true);
    cells[0][2]->set_alive(true);
    cells[0][3]->set_alive(true);
    cells[0][8]->set_alive(true);
    cells[0][9]->set_alive(true);
    cells[0][10]->set_alive(true);
    cells[0][11]->set_alive(true);
    cells[0][12]->set_alive(true);
    cells[0][13]->set_alive(true);
    cells[0][14]->set_alive(true);
    cells[0][15]->set_alive(true);
    cells[0][16]->set_alive(true);
    cells[0][17]->set_alive(true);
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
    cells[8][8]->set_alive(true);
    cells[8][9]->set_alive(true);
    cells[8][10]->set_alive(true);
    cells[8][11]->set_alive(true);
    cells[8][12]->set_alive(true);
    cells[8][15]->set_alive(true);
    cells[8][16]->set_alive(true);
    cells[8][17]->set_alive(true);
    cells[8][18]->set_alive(true);
    cells[9][7]->set_alive(true);
    cells[9][8]->set_alive(true);
    cells[9][10]->set_alive(true);
    cells[9][12]->set_alive(true);
    cells[9][13]->set_alive(true);
    cells[10][6]->set_alive(true);
    cells[10][7]->set_alive(true);
    cells[10][10]->set_alive(true);
    cells[10][13]->set_alive(true);
    cells[10][14]->set_alive(true);
    cells[11][5]->set_alive(true);
    cells[11][6]->set_alive(true);
    cells[11][9]->set_alive(true);
    cells[11][10]->set_alive(true);
    cells[11][11]->set_alive(true);
    cells[11][14]->set_alive(true);
    cells[11][15]->set_alive(true);
    cells[12][4]->set_alive(true);
    cells[12][5]->set_alive(true);
    cells[12][8]->set_alive(true);
    cells[12][10]->set_alive(true);
    cells[12][12]->set_alive(true);
    cells[12][15]->set_alive(true);
    cells[12][16]->set_alive(true);
    cells[13][4]->set_alive(true);
    cells[13][7]->set_alive(true);
    cells[13][10]->set_alive(true);
    cells[13][13]->set_alive(true);
    cells[13][16]->set_alive(true);
    cells[14][0]->set_alive(true);
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
    cells[15][0]->set_alive(true);
    cells[15][4]->set_alive(true);
    cells[15][7]->set_alive(true);
    cells[15][10]->set_alive(true);
    cells[15][13]->set_alive(true);
    cells[15][16]->set_alive(true);
    cells[16][0]->set_alive(true);
    cells[16][4]->set_alive(true);
    cells[16][5]->set_alive(true);
    cells[16][8]->set_alive(true);
    cells[16][10]->set_alive(true);
    cells[16][12]->set_alive(true);
    cells[16][15]->set_alive(true);
    cells[16][16]->set_alive(true);
    cells[17][0]->set_alive(true);
    cells[17][5]->set_alive(true);
    cells[17][6]->set_alive(true);
    cells[17][9]->set_alive(true);
    cells[17][10]->set_alive(true);
    cells[17][11]->set_alive(true);
    cells[17][14]->set_alive(true);
    cells[17][15]->set_alive(true);
    cells[18][0]->set_alive(true);
    cells[18][6]->set_alive(true);
    cells[18][7]->set_alive(true);
    cells[18][10]->set_alive(true);
    cells[18][13]->set_alive(true);
    cells[18][14]->set_alive(true);
    cells[19][0]->set_alive(true);
    cells[19][7]->set_alive(true);
    cells[19][8]->set_alive(true);
    cells[19][9]->set_alive(true);
    cells[19][10]->set_alive(true);
    cells[19][11]->set_alive(true);
    cells[19][12]->set_alive(true);
    cells[19][13]->set_alive(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
