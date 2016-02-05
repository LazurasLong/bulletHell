#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

//#include "bulletArray.hpp"
#include "utils.hpp"

class Enemy
{
public:
    sf::Vector2f pos;
    
    Enemy(int,bool,int);
    ~Enemy();
    
    void update(BulletArray&);
    void move();
    void shoot(BulletArray&);    
    
    sf::Vector2f getSprite();
    void getsHit();
    
    bool isDead();
    bool canDelete();
    bool isMirror();
    bool in_bounds();

    
private:    
    
    int type;
    int modified;
    int hp;
    int timeAlive;
    int timeDead;
    int shootTimeout;
    int stage;
    
    bool mirror;
    bool in_bounds_shoot();
    bool canShoot();
    
    
};

#endif