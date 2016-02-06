#ifndef _EARRAY_HPP_
#define _EARRAY_HPP_

//#include <iostream>
//#include <list>
//#include "enemy.hpp"

#include "utils.hpp"

class EnemyArray
{
public:
    
    EnemyArray();
    void updateArray(BulletArray &bullets,bool,double&);
    void addEnemy(float,float,int);
    int amountEnemies();
    bool collides(sf::Vector2f);
    
    sf::Vector2f getEnemyPos(int);
    sf::Vector2f getSpritePos(int);
    
    bool isMirror(int);
    
    void startPractice(int);
    void updatePractice(BulletArray &bullets,bool);
    bool finishPractice();
	
	int getStages();
    
private:
    
    std::list<Enemy> enemies;
    sf::Vector2f playerpos;
    int routineTime;
    int stdTime;
    int routineType;
    int stagesCleared;
    void startRoutine(int);
    void updateRoutine();
    bool routineEnded();
    bool canStart();
};


#endif