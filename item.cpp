#include <item.h>

Item::Item(){
    used_ = false;
}
Item::~Item(){

}

Hammer::~Hammer(){

}
int Item::use(){
    return 0;
}
Mushroom::~Mushroom(){

}

int Mushroom::use(){
    if(is_large){
        return 4;
    }
    else{
        return 2;
    }
}

int Hammer::use(){
    return 30;
}
