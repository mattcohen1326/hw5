#ifndef CELL_H
#define CELL_H
#include <QColor>
#include <QGraphicsItem>
#include <vector>


class Cell: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Cell();
    int get_row() {return row_;}
    int get_column(){return col_;}
    QColor get_color(){return color_;}
    bool is_alive(){return alive_;}
    void set_alive(bool x){alive_ = x;}
    void set_row(int x){row_ = x;}
    void set_color(QColor x){color_ = x;}
    void set_col(int x){col_ = x;}
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    bool neighbors[8];
private:
    QColor color_;
    bool alive_;
    int col_;
    int row_;
    static const int width_ = 40;


};

#endif // CELL_H
