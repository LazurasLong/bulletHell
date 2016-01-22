#include <iostream>
#include <SFML/Graphics.hpp>
#include "character.hpp"
#include "bulletArray.hpp"
#include "enemyArray.hpp"

int main(){
    
    sf::RenderWindow window(sf::VideoMode(400, 600), "Game 1");
    
    sf::Texture bgTexture;    
    if (!bgTexture.loadFromFile("./images/BGTexture.png")) std::cout << "Error loading background texture" << std::endl;
    sf::RectangleShape background(sf::Vector2f(400.f,600.f));
    background.setTexture(&bgTexture);
    //background.setFillColor(sf::Color(50,50,250));
    background.setFillColor(sf::Color(50,250,250));    
    
    
    
    
    sf::Texture bgTexture2;    
    if (!bgTexture2.loadFromFile("./images/BGTexture2.png")) std::cout << "Error loading background texture 2" << std::endl;
    sf::RectangleShape background2(sf::Vector2f(400.f,600.f));
    background2.setTexture(&bgTexture2);
    background2.setFillColor(sf::Color(255, 255, 255,128));
    
    
    sf::Texture spriteTextures;
    if (!spriteTextures.loadFromFile("./images/Sprites.png")) std::cout << "Error loading sprite texture" << std::endl;
    
    sf::Sprite sprites;
    sprites.setTexture(spriteTextures);
    
    sf::Sprite player;
    player.setTexture(spriteTextures);
    Character character(player);
    
    sf::Sprite focusPoint;
    focusPoint.setTexture(spriteTextures);
    focusPoint.setTextureRect(sf::IntRect(112,172,12,12));
    focusPoint.setOrigin(6,6);
    
    
    BulletArray bullets;
    sf::Sprite bulletImg;
    bulletImg.setTexture(spriteTextures);
    //bulletImg.setScale(2.f,2.f);
    //bulletImg.setTexture(sf::Color::Blue);
    //bulletImg.setPosition(0,0);
    
    EnemyArray enemies;
    sf::Sprite baddie;
    baddie.setTexture(spriteTextures);
    //z = atan(y/x)
    //Vx = V*cos(z) = V * sqr(x²/x²+y²)
    //Vy = V*sin(z)
    
    bool alive = true;
    int bgpos = 0;
    
    while (window.isOpen()){
        bgpos++;
        
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }
        }
        
        bullets.updateArray(character.pos);
        enemies.updateArray(bullets,alive);
        
        if (alive) {
            character.move(player);
            character.shoot(bullets);
            if (bullets.collides(character.pos,true) or enemies.collides(character.pos)){
                alive = false;
            }
            
            player.setPosition(character.pos.x, character.pos.y);
            

        } //else player.setPosition(-100,-100);
        
        
        window.clear();
        
        //Draw backgrounds
        window.draw(background);
        if (bgpos>=600) bgpos -= 600;
        background2.setPosition(0,bgpos-600);
        window.draw(background2);
        background2.setPosition(0,bgpos);
        window.draw(background2);
        
        if (alive) { //Draw player + focus point
            window.draw(player);
            if (character.isFocused()) {
                focusPoint.setPosition(character.pos.x,character.pos.y);
                window.draw(focusPoint);
            }
        }
        
        
        for (int i = 0;i<enemies.amountEnemies();i++){  //Draw enemies
            sf::Vector2f spr=enemies.getSpritePos(i);
            baddie.setTextureRect(sf::IntRect(spr.x,spr.y,32,32));
            baddie.setOrigin(16,16);
            
            if (enemies.isMirror(i)) baddie.setScale(-1.f,1.f);
            else baddie.setScale(1.f,1.f);

            baddie.setPosition(enemies.getEnemyPos(i));
            window.draw(baddie);
        }
        
        for (int i = 0;i<bullets.amountBullets();i++){ //Draw bullets
            sf::Vector2f bullet_Position;
            bullet_Position = bullets.getBulletPos(i);
            bulletImg.setPosition(bullet_Position);
            if (bullets.isFriendly(i)) {
                bulletImg.setTextureRect(sf::IntRect(64+12*7,160,12,12));
            } else {
                int bulletType = bullets.getType(i);
                if (bulletType < 10) bulletImg.setTextureRect(sf::IntRect(64+12*bulletType,160,12,12));
                else bulletImg.setTextureRect(sf::IntRect(64+12*(bulletType-10),172,12,12));
                bulletImg.setOrigin(6,6);
            }
            
            window.draw(bulletImg);
        }

        window.display();
    }
    return -1;
}