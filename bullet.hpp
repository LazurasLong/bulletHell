#ifndef _BULLET_HPP_
#define _BULLET_HPP_
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    
    Bullet(float,float,float,float,bool,int);
    ~Bullet();
    void updateBullet();
    bool in_bounds();
    bool isFriendly();
    bool collides(float,float,bool);
    int getType();
    
    sf::Vector2f pos;

private:
    int type;
    bool friendly;
    sf::Vector2f vel;
    
};

#endif