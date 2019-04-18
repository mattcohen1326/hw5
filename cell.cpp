#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "cell.h"

Cell::Cell()
{
    alive_ = false;
    color_ = QColor(255,0,0);
    for(int i = 0; i < 8;i++){
            neighbors[i] = 0;
    }

}
QRectF Cell::boundingRect() const //creates a bound to draw the cell in
{
    return QRectF(col_, row_, width_, width_);
}

QPainterPath Cell::shape() const //creates the shape of the actual cell
{
    QPainterPath path;
    path.addRect(col_, row_, width_, width_);
    return path;

}


void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //paints a cell
{
    Q_UNUSED(widget);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
    painter->drawRect(QRect(this->col_, this->row_, this->width_, this->width_));
    painter->setBrush(b);
}


