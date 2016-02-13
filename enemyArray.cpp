#include "utils.hpp"

EnemyArray::EnemyArray(){
    
    routineTime = 150;
    stdTime = 50;
    routineType = 0;
    
    stagesCleared = 0;
    
}

void EnemyArray::updateArray(BulletArray &bullets, bool playerAlive, double &score, sf::Sound &hit, sf::Sound &kill){
    
    if (enemies.size()>0){ //Check for collisions
        for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++){
            if ((*it).in_bounds() or ((*it).pos.x == -50 and (*it).pos.y == -50)){
                (*it).update(bullets);
                if (not (*it).isDead()){
                    if (bullets.collides((*it).pos,false)){
                        (*it).getsHit();
                        hit.play();
						if ((*it).isDead()) kill.play();
                    }
                }
                else if ((*it).canDelete()){
					score+=10;
                    enemies.erase(it);
                    it--;
                }
            } else {
                enemies.erase(it);
                it--;
            }
        }
    } 
    if (playerAlive){
        if (canStart()){
            if (stagesCleared<5){
                if (routineEnded()) {
					if (stagesCleared!=0) score += 20;
                    stagesCleared++;
                    startRoutine(stagesCleared);
                }
            }
            else {
                stagesCleared++;
				int nextRout = routineType;
				while (nextRout == routineType){
					nextRout = rand()%5+1;
				}
				
                startRoutine(nextRout);
            }
        }
    }
    updateRoutine();
}

void EnemyArray::startPractice(int stage){
    
    if (enemies.size()==0){
		startRoutine(stage);
    }
    
}

void EnemyArray::updatePractice(BulletArray &bullets, bool playerAlive,sf::Sound &hit, sf::Sound &kill){
    
    if (enemies.size()>0){ //Check for collisions
        for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++){
            if ((*it).in_bounds() or ((*it).pos.x == -50 and (*it).pos.y == -50)){
                (*it).update(bullets);
                if (not (*it).isDead()){
                    if (bullets.collides((*it).pos,false)){
                        (*it).getsHit();
						hit.play();
						if ((*it).isDead()) kill.play();
                    }
                }
                else if ((*it).canDelete()){
                    enemies.erase(it);
                    it--;
                }
            }
            else {
                enemies.erase(it);
                it--;
			}
		}
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
    
    if (type==0) routineTime = stdTime;
    else if (type==1) routineTime = stdTime*10;
    else if (type==2) routineTime = stdTime*10;
    else if (type==3) routineTime = stdTime*10;
    else if (type==4) routineTime = stdTime*12;
    else if (type==5) routineTime = stdTime*5;

    //std::cout << "routine started " << routineType << " " << routineTime << std::endl;
    
}

void EnemyArray::updateRoutine(){
    
    if (routineType==1){
        if (routineTime==stdTime*10){
            Enemy newEnemy(1,false,0);
            Enemy newEnemy2(1,true,0);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
        else if (routineTime==stdTime*9){
            Enemy newEnemy(1,false,1);
            Enemy newEnemy2(1,true,1);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
        else if (routineTime==stdTime*8){
            Enemy newEnemy(1,false,2);
            Enemy newEnemy2(1,true,2);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
    }
    else if (routineType==2){
        if (routineTime==stdTime*10 or routineTime==stdTime*8 or routineTime==stdTime*6){
            Enemy newEnemy(2,false,0);
            enemies.push_back(newEnemy);
        }
        else if (routineTime==stdTime*9 or routineTime==stdTime*7 or routineTime==stdTime*5){
            Enemy newEnemy(2,true,0);
            enemies.push_back(newEnemy);
        }
    }
    else if (routineType==3){
        if (routineTime==stdTime*10){
            Enemy newEnemy(3,false,1);
            enemies.push_back(newEnemy);
        }
        else if (routineTime==stdTime*9){
            Enemy newEnemy(3,false,0);
            Enemy newEnemy2(3,false,2);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
    }
    else if (routineType==4){
        if (routineTime==stdTime*12){
            Enemy newEnemy(4,false,0);
            enemies.push_back(newEnemy);
        }
        
    }
    else if (routineType==5){
        if (routineTime==stdTime*5){
            Enemy newEnemy(5,false,0);
            Enemy newEnemy2(5,true,0);
            enemies.push_back(newEnemy);
            enemies.push_back(newEnemy2);
        }
    }
    
    if (routineTime!=0) routineTime--;
    
}

bool EnemyArray::canStart(){
    
    if (routineEnded()) return true;
    else if (routineType==1 and routineTime<stdTime*4) return true;
    else if (routineType==2 and routineTime<stdTime*2) return true;
    else if (routineType==3 and routineTime<stdTime*3) return true;
    else if (routineType==4 and routineTime<stdTime*2) return true;
    else return false;
    
}

sf::Vector2f EnemyArray::getSpritePos(int i){
    
    std::list<Enemy>::iterator it = enemies.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    
    return (*it).getSprite();
    
    
}

int EnemyArray::getStages(){
	
	if (stagesCleared < 1) return 0;
	else return stagesCleared-1	;
	
}

bool EnemyArray::isMirror(int i){
    
    std::list<Enemy>::iterator it = enemies.begin();
    for (int j = 0;j<i;j++){
        it++;
    }
    return (*it).isMirror();
    
}

bool EnemyArray::finishPractice(){
    
    return (enemies.size() == 0 and canStart());
    
}
