#ifndef _BARRAY_HPP_
#define _BARRAY_HPP_

//#include <iostream>
//#include <list>
//#include "bullet.hpp"
#include "utils.hpp"

class BulletArray
{
public:
    
    BulletArray();
    void updateArray(sf::Vector2f);
    void addBullet(bool,float,float,int,int,int);
    int amountBullets();
    sf::Vector2f getBulletPos(int);
    bool isFriendly(int);
    bool collides(sf::Vector2f,bool);
    int getType(int);
    
private:
    
    std::list<Bullet> bullets;
    sf::Vector2f playerpos;

    
};


#endif