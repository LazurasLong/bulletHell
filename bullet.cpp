#include "bullet.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

Bullet::Bullet(float x, float y, float xvel, float yvel, bool playerShot, int bullet_type, int mod){
    
    pos.x = x;
    pos.y = y;
    vel.x = (float)xvel;
    vel.y = (float)yvel;

    friendly = playerShot;
    type = bullet_type;
    modifier = mod;
    
    time = 0;
    paused = false;
    if (type==15 or type==16) bounce = true;
    else bounce = false;
    
    if (type==17){
        plpos.x = (float)xvel;
        plpos.y = (float)yvel;
    }
}

Bullet::~Bullet() {}

void Bullet::updateBullet(){
    
    if (type==15 or type==16){
        if (not paused){
            pos.x += vel.x;
            pos.y += vel.y;
            if (bounce){
                if(pos.x>=400){
                    vel.x = -vel.x;
                    pos.x += vel.x;
                    bounce = false;
                }
                else if (pos.x<=0){
                    vel.x = -vel.x;
                    pos.x += vel.x;
                    bounce = false;
                }
                if (pos.y<=0){
                    vel.y = -vel.y;
                    pos.y += vel.y;
                    bounce = false;
                }
            }
            if (type==15 and time>=15 and time<300) paused = true;
            else if (type==16 and time>=10 and time<300) paused = true;
        }
    }
    else if (type==17){
        int spd1 = 10, spd2 = 2;
        int dist1 = 10, dist2 = 50;
        
        
        double angle1 = 0.0174533*(time*spd1+60*(modifier/10));
        double angle2 = 0.0174533*(time*spd2+60*(modifier%10));
        
        pos.x = (float)dist1*cos(angle1)+dist2*cos(angle2)+plpos.x;
        pos.y = (float)dist1*sin(angle1)+dist2*sin(angle2)+plpos.y;
    }
    else{
        pos.x += vel.x; 
        pos.y += vel.y;
    }
    
    time++;
}

bool Bullet::in_bounds(){
    return(pos.x >= -10 and pos.x <= 410 and pos.y >= -10 and pos.y <= 610);
}

bool Bullet::isFriendly(){
    return friendly;
}

bool Bullet::collides(float centerx,float centery,bool player){

    int aux = type/10; //Big or small bullet
    
    
    sf::FloatRect b1(pos.x-2-aux,pos.y-1,4+2*aux,2);
    sf::FloatRect b2(pos.x-1.5+0.5*aux,pos.y-1.5+0.5*aux,3+aux,3+aux);
    sf::FloatRect b3(pos.x-1,pos.y-2-aux,2,4+2*aux);
    
    
    if (player){
        sf::FloatRect player1(centerx-2,centery-1,4,2);
        sf::FloatRect player2(centerx-1.5,centery-1.5,3,3);
        sf::FloatRect player3(centerx-1,centery-2,2,4); 
        
        return (b1.intersects(player1) or b1.intersects(player2) or b1.intersects(player3) or
                b2.intersects(player1) or b2.intersects(player2) or b2.intersects(player3) or
                b3.intersects(player1) or b3.intersects(player2) or b3.intersects(player3));
        
    } else {
        sf::FloatRect enemy1(centerx-16,centery-16,32,32);
        
        return (b1.intersects(enemy1) or b2.intersects(enemy1) or b3.intersects(enemy1));
        
    }
}

int Bullet::getType(){
    
    return type-1;
    
}

/*int Bullet::getTime(){
    
    return time;
    
}*/

bool Bullet::canUnpause(){

    return (paused and time>=50 and time<300);
    
}

void Bullet::unpause(){
    
    if (time>10){
        paused = false;
        time = 300;
    }
    
}


void Bullet::newPlayerPos17(sf::Vector2f playerpos){
    
    vel = playerpos;
    
}