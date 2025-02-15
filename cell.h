#ifndef CELL_H
#define CELL_H
#include <QColor>
#include <QGraphicsItem>
#include <vector>
#include <player.h>

struct cellBuilding{
    Player * p;
    bool toll_built = false;
    bool castle_built = false;

};

class Cell: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Cell();
    int get_row() {return row_;}
    int get_column(){return col_;}
    QColor get_color(){return color_;}
    QColor get_norm() {return norm_color;}
    bool is_alive(){return alive_;}
    void set_alive(bool x){alive_ = x;}
    void set_row(int x){row_ = x;}
    void set_coin(int x){coin_value = x;}
    void set_color(QColor x){color_ = x;}
    void set_norm(QColor x){norm_color = x;}
    void set_col(int x){col_ = x;}
    int get_coins(){return coin_value;}
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    bool neighbors[8];
    bool is_star = false;
    bool is_gate = false;
    bool has_player = false;

private:
    cellBuilding status;
    int coin_value;
    QColor color_;
    QColor norm_color;
    bool alive_;
    int col_;
    int row_;
    static const int width_ = 40;


};

#endif // CELL_H
