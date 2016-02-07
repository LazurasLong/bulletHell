#include "utils.hpp"


Character::Character(sf::Sprite &player){

    sprx = 384;
    spry = 0;
    
    player.setTextureRect(sf::IntRect(sprx,spry,16,45));
    player.setOrigin(8,17);
    
    pos.x = G_WIDTH/2;
    pos.y = G_HEIGHT-100;
    
    timeAlive=0;
    shootTimeout = 0;
    focused = false;
}

void Character::update(sf::Sprite& player, BulletArray &bullets){

	timeAlive++;
	move(player);
	shoot(bullets);
	
}

void Character::move(sf::Sprite &player){
    
    float travelpos;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        focused = true;
        travelpos = 1;
    } else {
        focused = false;
        travelpos = 5;
    }
    
    //X
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if (pos.x <= G_WIDTH-travelpos-16) pos.x += travelpos;
        spry = 64;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if (pos.x >= travelpos+16) pos.x -= travelpos;
        spry = 128;
    } else {
        spry = 0;
    }
    
    sprx = 384+32*(timeAlive/8%4);
    
    player.setTextureRect(sf::IntRect(sprx,spry,32,45));
    player.setOrigin(16,22);
    
    //Y
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if (pos.y >= travelpos+32) pos.y -= travelpos;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if (pos.y <= G_HEIGHT-travelpos-32) pos.y += travelpos;
    }

}

void Character::shoot(BulletArray &bullets){
    

    if (shootTimeout == 0){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            bullets.addBullet(true,pos.x,pos.y,9,0,0);
            shootTimeout = shootFreq;
        }
    } else {
        shootTimeout--;
    }
    
}

bool Character::isFocused(){
    return focused;
}