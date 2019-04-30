#ifndef PLAYER_H
#define PLAYER_H

#include <QColor>
#include <QGraphicsItem>
#include <vector>
#include <item.h>

class Player{

public:
    Player();
    bool is_human(){return human;}
    int get_row(){return current_row;}
    int get_col(){return current_col;}
    void set_row(int x){current_row = x;}
    void set_col(int x){current_col = x;}
    int get_coins() {return coins;}
    int get_stars() {return stars;}
    void add_stars(){stars+=1;}
    std::string get_first(){return first_choice;}
    void set_first(std::string s){first_choice = s;}
    std::string get_dir(){return direction;}
    void set_dir(std::string x){direction = x;}
    QColor get_color(){return color_;}
    void set_color(QColor x){color_ = x;}
    void itemFactory();
    int roll = 0;
    void set_human(bool x){human = x;}
    int id;
    void clear_stars(){stars = 0;}
    void add_coins(int x);
    Item * items[3];
private:
    std::string first_choice = "";
    bool human;
    QColor color_;
    std::string direction; //direction for moving logic
    int current_row;
    int current_col;
    int coins;
    int stars;

};

#endif // PLAYER_H
