#include "player.h"

Player::Player()
{
    human = false;
    coins = 0;
    stars = 0;
    direction = "up";
    current_col = 1;
    current_row = 18;
    roll = 0;
    itemFactory();

}

void Player::add_coins(int x){
    coins += x;
}

void Player::itemFactory(){
    srand(time(0));
    int item_2 = rand()%2+1;
    int item_3 = rand()%2+1;
    //items[0] = Hammer();
    if(item_2 == 1){
        items[1] = Mushroom(true);

    }
    else{
        items[1] = Mushroom(false);
    }
    if(item_3 == 1){
        items[2] = Mushroom(true);
    }
    else{
        items[2] = Mushroom(false);
    }

}
