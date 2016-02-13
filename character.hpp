#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_

#include "utils.hpp"

class Character
{
public:
    
    Character(sf::Sprite&);
	void update(sf::Sprite&, BulletArray&, sf::Sound&, bool);
    bool isFocused();
    
    sf::Vector2f pos;
	
private:
    
    int sprx, spry, shootTimeout, timeAlive, timeDead;
    bool focused;
    static const int shootFreq = 3;
	
	
	void move();
    void shoot(BulletArray&,sf::Sound&);
    
};

#endif