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

}

void Player::add_coins(int x){
    coins += x;
}

