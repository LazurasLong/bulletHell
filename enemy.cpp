#include <SFML/Graphics.hpp>
#include <cmath>
#include "enemy.hpp"
#include "bullet.hpp"
#include "bulletArray.hpp"


Enemy::Enemy(int t, bool m, int mod){
    
    type = t;
    mirror = m;
    modified = mod;
    timeAlive = 0;
    timeDead = 0;
    pos.x = -50;
    pos.y = -50;
    shootTimeout = 0; 
    stage = 1;
    
    if (t==1) hp = 1;
    else if (t==2) hp = 1;
    else if (t==3) hp = 5;
    else if (t==4) hp = 20;
    
}

Enemy::~Enemy(){}

void Enemy::update(BulletArray& bullets){
    
    if (isDead()) {
        timeDead++;
    }
    else {
        timeAlive++;
        move();
        shoot(bullets);
    }
    
}

void Enemy::move(){
    
    if (type==1){ //Line
        if (timeAlive<50){
            pos.x = (timeAlive)*2;
        } else if (timeAlive>100){
            pos.x = (timeAlive)*2-100;
        }
        else pos.x = 100;
        
        pos.y = 100+modified*10;
    }
    else if (type==2){ //SemiCircle
        float radius = 100;
        
        pos.y = timeAlive+150;
        if (pos.y<=150+radius) pos.x = (float)sqrt(radius*radius-(pos.y-(150+radius))*(pos.y-(150+radius)))-16;
        else pos.x = (float)sqrt(radius*radius-(pos.y-(150+radius))*(pos.y-(150+radius)))-16;
    }
    else if (type==3){
        
        pos.x = 100+modified*100;
        if (timeAlive<100) pos.y = timeAlive*2;
        else if (timeAlive>200) pos.y = (timeAlive-100)*2;
        
    }
    else if (type==4){
        if (timeAlive<100){
            pos.x = timeAlive*2;
            pos.y = 150+15*sin(0.0174533*timeAlive);
        }
        else if (timeAlive>300){
            pos.x = (timeAlive-200)*2;
            pos.y = 150+15*sin(0.0175433*(timeAlive-200));
        }
    }
        
    if (mirror){
        pos.x = 400-pos.x;
    }
}

void Enemy::shoot(BulletArray &bullets){
    
    if (canShoot()){            
        if (type==1) {
            bullets.addBullet(false,pos.x,pos.y,1,type,0);
            shootTimeout = 20;
        }
        else if (type==2){
            bullets.addBullet(false,pos.x,pos.y,2,type,0);
            stage++;
            shootTimeout = 15;
        }
        else if (type==3){
            if (modified==0 or modified==2) bullets.addBullet(false,pos.x,pos.y,3,type,stage);
            else bullets.addBullet(false,pos.x,pos.y,4,type,stage);
            stage++;
            shootTimeout = 1;
        }
        else if (type==4){
            if (stage<=9) bullets.addBullet(false,pos.x,pos.y,5,type,stage);
            if (timeAlive>=100 and timeAlive<=300) stage++;
            if (timeAlive==200) stage=0;
            shootTimeout = 0;
        }
    } else if (shootTimeout > 0){
        shootTimeout--;
    }
    
}


sf::Vector2f Enemy::getSprite(){
    
    sf::Vector2f spr;
    
    if (isDead()){
        if (timeDead%8<2){
            spr.x = 0;
            spr.y = 160;
        }
        else if (timeDead%8<4){
            spr.x = 32;
            spr.y = 160;
        }
        else if (timeDead%8<6){
            spr.x = 0;
            spr.y = 192;
        }
        else if (timeDead%8<8){
            spr.x = 32;
            spr.y = 192;
        }
    }
    else {
        spr.y = (type-1)*32;
    
        if (type==1){
            if (timeAlive<35 or timeAlive>108){
                if (timeAlive%15<5) spr.x = 9*32;
                else if (timeAlive%15<10) spr.x = 10*32;
                else spr.x = 11*32;
            }
            else if (timeAlive < 38 or timeAlive > 104) spr.x = 7*32;
            else if (timeAlive < 41 /*or timeAlive > 106*/) spr.x = 6*32;
            else if (timeAlive < 44 or timeAlive > 102) spr.x = 5*32;
            else if (timeAlive < 47 /*or timeAlive > 102*/) spr.x = 4*32;
            else if (timeAlive < 50 or timeAlive > 100) spr.x = 3*32;
            else spr.x = timeAlive%4*32;
        }
        else if (type==2){
            if (timeAlive<20 or timeAlive>130){
                if (timeAlive%15<5) spr.x = 9*32;
                else if (timeAlive%15<10) spr.x = 10*32;
                else spr.x = 11*32;
            }
            else if (timeAlive < 27 or timeAlive > 123) spr.x = 7*32;
            else if (timeAlive < 34 or timeAlive > 116) spr.x = 6*32;
            else if (timeAlive < 41 or timeAlive > 109) spr.x = 5*32;
            else if (timeAlive < 48 or timeAlive > 102) spr.x = 4*32;
            else if (timeAlive < 55 or timeAlive > 95) spr.x = 3*32;
            else {
                spr.x = (timeAlive-55)/10*32;
            }
        }
        else if (type==3){
        
            if (timeAlive<100 or timeAlive>200) spr.x = timeAlive%4*32;
            else spr.x = (timeAlive/2)%4*32;
            
        }
        else if (type==4){
            
            if (timeAlive<90 or timeAlive>310){
                if (timeAlive%15<5) spr.x = 9*32;
                else if (timeAlive%15<10) spr.x = 10*32;
                else spr.x = 11*32;
            }
            else if (timeAlive<92 or timeAlive>308) spr.x = 7*32;
            else if (timeAlive<94 or timeAlive>306) spr.x = 6*32;
            else if (timeAlive<96 or timeAlive>304) spr.x = 5*32;
            else if (timeAlive<98 or timeAlive>302) spr.x = 4*32;
            else if (timeAlive<100 or timeAlive>300) spr.x = 3*32;
            else spr.x = (timeAlive/2)%4*32;
            
        }
    }
    return spr;
}

void Enemy::getsHit(){
    
    if (hp>0){
        if (type!=3){
            hp--;
        }
        else if (timeAlive>200){
            hp--;
        }
    }
    
}

bool Enemy::isDead(){

    return (hp==0);
    
}

bool Enemy::canDelete(){
 
    if (isDead()) return (timeDead>16);
    else return false;
    
}

bool Enemy::isMirror(){
    if (type==2 and timeAlive>50) return not mirror;
    else return mirror;
}

bool Enemy::in_bounds(){
    return(pos.x >= -16 and pos.x <= 416 and pos.y >= -16 and pos.y <= 616);
}

//-----------------------------------PRIVATES---------------------------------------

bool Enemy::in_bounds_shoot(){
    return(pos.x >= 0 and pos.x <= 400 and pos.y >= 0 and pos.y <= 600);
}

bool Enemy::canShoot(){
    
    bool shootTime = false;
    if (type==1){
        if (timeAlive>=50 and timeAlive<=100) shootTime = true; 
    }
    else if (type==2){
        if (timeAlive>=50 and timeAlive<=100) shootTime = true;
    }
    else if (type==3){
        if (timeAlive>=100 and timeAlive<=200) shootTime = true;
    }
    else if (type==4){
        if ((timeAlive>=100 and timeAlive<=300)) shootTime = true;
    }
        
    return (shootTime and shootTimeout==0 and in_bounds_shoot());
    
}