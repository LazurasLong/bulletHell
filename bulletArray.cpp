#include "bulletArray.hpp"
#include "bullet.hpp"
#include <cmath>
#include <stdio.h>

BulletArray::BulletArray(){
    
    
    
}

void BulletArray::updateArray(sf::Vector2f playerIs){
    
    bool can_unpause = false;
    
    for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
        if ((*it).in_bounds()){
            (*it).updateBullet();
            if ((*it).getType()==15){
                if ((*it).canUnpause() or can_unpause){
                    can_unpause = true;
                    (*it).unpause();
                }
            }
            /*if ((*it).isFriendly() and enemyArray.collides((*it).pos.x,(*it).pos.y)){
                bullets.erase(it);
                it--;
            } else if (!(*it).isFriendly() and (*it).collides(playerpos.x,playerpos.y)){
                game.over();
            }*/
        } else {
            bullets.erase(it);
            it--;
        }
    }
    
    //if (playerIs.x != -100 playerIs.y != -100){
        playerpos.x = playerIs.x;
        playerpos.y = playerIs.y;
    //}

}

void BulletArray::addBullet(bool player, float ox, float oy, int bullet_type, int attack_type, int stage){
    
    if (player){
        Bullet newPlayerBullet(ox,oy-40,0,-15,true,bullet_type);
        bullets.push_back(newPlayerBullet);
    } else {
        //angle = 0.0174533*DEGREES
        if (attack_type==1){
            float difx = ox-playerpos.x;
            float dify = oy-playerpos.y;
            double angle = atan(dify/difx);
            
            //angle = 0.0174533*degrees;
            //angle *180/PI = degrees
            
            float bvx = (float)5*cos(angle);
            float bvy = (float)5*sin(angle);
            
            if (difx >= 0) {
                bvx = 0-bvx;
                bvy = 0-bvy;
            }
            
            Bullet newEnemyBullet(ox,oy,bvx,bvy,false,bullet_type+10);
            bullets.push_back(newEnemyBullet);
        }
        else if (attack_type==2){
            for (int i=0;i<5;i++){
                float difx = ox-playerpos.x+(-60+i*30);
                float dify = oy-playerpos.y;
                double angle = atan(dify/difx);
                
                float bvx = (float)10*cos(angle);
                float bvy = (float)10*sin(angle);
                
                if (difx >= 0) {
                    bvx = 0-bvx;
                    bvy = 0-bvy;
                }
                
                Bullet newEnemyBullet(ox,oy,bvx,bvy,false,bullet_type+10);
                bullets.push_back(newEnemyBullet);
            }
        }
        else if (attack_type==3){
            
                double angle = 0.0174533*(stage*15);
                float bvx = (float)5*cos(angle);
                float bvy = (float)5*sin(angle);
                
                Bullet newEnemyBullet(ox,oy,bvx,bvy,false,10+bullet_type);
                Bullet newEnemyBullet2(ox,oy,-bvx,bvy,false,10+bullet_type);
                bullets.push_back(newEnemyBullet);
                bullets.push_back(newEnemyBullet2);
                
        }
        else if (attack_type==4){
            
            double angle = 0.0174533*(stage*10);
            float bvx = (float)cos(angle);
            float bvy = (float)sin(angle);
            Bullet newEnemyBullet(ox,oy,bvx,bvy,false,10+bullet_type);
            bullets.push_back(newEnemyBullet);
            
            
        }
    }
}

int BulletArray::amountBullets(){
    
    return bullets.size();
    
}

sf::Vector2f BulletArray::getBulletPos(int i){
    
    std::list<Bullet>::iterator it = bullets.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    sf::Vector2f bulletpos;
    bulletpos.x = (*it).pos.x;
    bulletpos.y = (*it).pos.y;
    return bulletpos;
}

bool BulletArray::collides(sf::Vector2f pos, bool player){
    
    for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++){
        if (player xor (*it).isFriendly()){
            if ((*it).collides(pos.x,pos.y,player)){
                bullets.erase(it);
                return true;
            }
        }
    }    
}

bool BulletArray::isFriendly(int i){
    std::list<Bullet>::iterator it = bullets.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    return (*it).isFriendly();
}

int BulletArray::getType(int i){
    
    std::list<Bullet>::iterator it = bullets.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    return (*it).getType();
    
}