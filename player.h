#ifndef PLAYER_H
#define PLAYER_H
#include <QColor>
#include <QGraphicsItem>
#include <vector>

class Player{

public:
    Player();
    bool is_human(){return human;}
    int get_row(){return current_row;}
    int get_col(){return current_col;}
    void set_row(int x){current_row = x;}
    void set_col(int x){current_col = x;}
    std::string get_dir(){return direction;}
    void set_dir(std::string x){direction = x;}
    int roll = 15;
private:
    bool human;
    std::string direction; //direction for moving logic
    int current_row;
    int current_col;
    int coins;
    int stars;

};

#endif // PLAYER_H
