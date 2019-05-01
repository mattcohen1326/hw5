#ifndef ITEM_H
#define ITEM_H

#include <QColor>


class Item
{
public:
    Item();
    virtual ~Item();
    bool used_;
    QString name;
    virtual int use();
protected:

};

class Mushroom: public Item
{
public:
    Mushroom(bool large):
    Item(),
    is_large(large),
    is_small(!large)
    {}
    int use();
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
    int use();

};

#endif // ITEM_H
