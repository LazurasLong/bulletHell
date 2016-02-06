//#include "bullet.hpp"
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <cmath>
#include "utils.hpp"

Bullet::Bullet(float x, float y, float xvel, float yvel, bool playerShot, int bullet_type, int mod){
    
    pos.x = x;
    pos.y = y;
    vel.x = xvel;
    vel.y = yvel;

    friendly = playerShot;
    type = bullet_type;
    modifier = mod;
    
    time = 0;
    paused = false;
    if (type==15 or type==16) bounce = true;
    else bounce = false;

}

Bullet::~Bullet() {}

void Bullet::updateBullet(){
    
    if (type==15 or type==16){
        if (not paused){
            pos.x += vel.x;
            pos.y += vel.y;
            if (bounce){
                if(pos.x>=G_WIDTH){
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
    else if (type==17 or type==18){
        int spd1 = 10, spd2 = 5;
        int dist1 = 10, dist2 = 50;
        int axisX = (time+5)*20/9, axisY = 500*sin(0.0174533*(time+5));
        
        if (vel.x == 2) { //Mirrored enemy, spaghetti code
            axisX = G_WIDTH-axisX;
            axisY = G_HEIGHT-axisY;
        }
        
        
        if (time<20) dist2 = time*2.5;
        
        double angle1 = 0.0174533*(time*spd1+60*(modifier/10));
        double angle2 = 0.0174533*(time*spd2+60*(modifier%10));
        
        pos.x = (float)dist1*cos(angle1)+dist2*cos(angle2)+axisX;
        pos.y = (float)dist1*sin(angle1)+dist2*sin(angle2)+axisY;
    }
    else{
        pos.x += vel.x; 
        pos.y += vel.y;
    }
    
    time++;
}

bool Bullet::in_bounds(){
    return(pos.x >= -10 and pos.x <= G_WIDTH+10 and pos.y >= -10 and pos.y <= G_HEIGHT+10);
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
    
    if (type==17 or type==18) return 16;
    else return type-1;
    
}

bool Bullet::canUnpause(){

    return (paused and time>=50 and time<300);
    
}

void Bullet::unpause(){
    
    if (time>10){
        paused = false;
        time = 300;
    }
    
}