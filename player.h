#ifndef PLAYER_H
#define PLAYER_H
#include <QColor>
#include <QGraphicsItem>
#include <vector>

class player: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    player();
private:
    bool going_right;
    int current_row;
    int current_col;
    int coins;
    int stars;

};

#endif // PLAYER_H
