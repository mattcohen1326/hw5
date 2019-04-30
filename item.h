#ifndef ITEM_H
#define ITEM_H

#include <QColor>

class Item
{
public:
    Item();
    virtual ~Item();
    //virtual void use();
protected:
    bool used_;
};

class Mushroom: public Item
{
public:
    Mushroom(bool large):
    Item(),
    is_large(large),
    is_small(!large)
    {}
    //void use();
    ~Mushroom();
private:
    bool is_large;
    bool is_small;


};

class Hammer: public Item
{
public:
    Hammer():
    Item()
    {}
    ~Hammer();
    //void use();
    //void build();

};

#endif // ITEM_H
