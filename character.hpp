#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_
#include "bullet.hpp"
#include "bulletArray.hpp"

class Character
{
public:
    
    Character(sf::Sprite&);
    void move(sf::Sprite&);
    void shoot(BulletArray&);
    bool isFocused();
    
    sf::Vector2f pos;
    int timeAlive;
    
private:
    
    int sprx, spry;

    bool focused;
    int shootTimeout;
    static const int shootFreq = 3;
    
};

#endif