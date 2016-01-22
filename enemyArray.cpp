#include <SFML/Graphics.hpp>
#include "enemy.hpp"
#include "enemyArray.hpp"


EnemyArray::EnemyArray(){
    
    routineTime = 100;
    routineType = 0;
    
}

void EnemyArray::updateArray(BulletArray &bullets, bool playerAlive){
        
    if (enemies.size()>0){
        for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++){
            if ((*it).in_bounds() or ((*it).pos.x == -50 and (*it).pos.y == -50)){
                (*it).update(bullets);
                
                if (not (*it).isDead()){
                    if (bullets.collides((*it).pos,false)){
                        (*it).getsHit();
                        //Play sound
                        it--;
                    }
                    
                }
                else if ((*it).canDelete()){
                    enemies.erase(it);
                    it--;
                }
            } else {
                enemies.erase(it);
                it--;
            }
        }
    } else if (canEnd()){
        startRoutine(0);
    } else if (routineEnded() and playerAlive){

        startRoutine(
            //1
            //2
            //3
            4
            //rand()%3+1
            );
    }
    updateRoutine();

}

sf::Vector2f EnemyArray::getEnemyPos(int i){
    
    std::list<Enemy>::iterator it = enemies.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    sf::Vector2f enemypos;
    enemypos.x = (*it).pos.x;
    enemypos.y = (*it).pos.y;
    
    return enemypos;    
    
}

int EnemyArray::amountEnemies(){
    return enemies.size();
}

bool EnemyArray::collides(sf::Vector2f p){
    
    sf::FloatRect pl(p.x-8,p.y-16,16,32);
    
    for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++){
        sf::FloatRect e((*it).pos.x-8,(*it).pos.y-8,16,20);
        if (e.intersects(pl)){
            return true;
        }
    }
}

bool EnemyArray::routineEnded(){
    
    return (routineTime==0);
    
}

void EnemyArray::startRoutine(int type){
    
    routineType = type;
    //std::cout << type << std::endl;
    if (type==0) routineTime = 50;
    else if (type==1) routineTime = 500;
    else if (type==2) routineTime = 500;
    else if (type==3) routineTime = 500;
    else if (type==4) routineTime = 750;

    std::cout << "routine started " << routineType << " " << routineTime << std::endl;
    
}

void EnemyArray::updateRoutine(){
    
    //  if (routineType==0);
    if (routineType==1){
        if (routineTime==500){
            Enemy newEnemy(1,false,0);
            Enemy newEnemy2(1,true,0);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
        else if (routineTime==450){
            Enemy newEnemy(1,false,1);
            Enemy newEnemy2(1,true,1);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
        else if (routineTime==400){
            Enemy newEnemy(1,false,2);
            Enemy newEnemy2(1,true,2);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
    }
    else if (routineType==2){
        if (routineTime==500 or routineTime==400 or routineTime==300){
            Enemy newEnemy(2,false,0);
            enemies.push_back(newEnemy);
        }
        else if (routineTime==450 or routineTime==350 or routineTime==250){
            Enemy newEnemy(2,true,0);
            enemies.push_back(newEnemy);
        }
    }
    else if (routineType==3){
        if (routineTime==500){
            Enemy newEnemy(3,false,1);
            enemies.push_back(newEnemy);
        }
        else if (routineTime==450){
            Enemy newEnemy(3,false,0);
            Enemy newEnemy2(3,false,2);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
    }
    else if (routineType==4){
        Enemy newEnemy(4,false,0);
        enemies.push_back(newEnemy);
        
    }
    
    if (routineTime!=0) routineTime--;
    
}

bool EnemyArray::canEnd(){
    
    if (routineType==1 and routineTime<350) return true;
    else if (routineType==2 and routineTime<250) return true;
    else return false;
    
}

sf::Vector2f EnemyArray::getSpritePos(int i){
    
    std::list<Enemy>::iterator it = enemies.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    
    return (*it).getSprite();
    
    
}

bool EnemyArray::isMirror(int i){
    
    std::list<Enemy>::iterator it = enemies.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    return (*it).isMirror();
    
}