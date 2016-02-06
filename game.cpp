#include "utils.hpp"

Game::Game(sf::RenderWindow* window): _myWindow(window){
	
}

void Game::play(){
    
    sf::Texture bgTexture;    
      if (!bgTexture.loadFromFile(BG_File1)) print_error("BG1");
    sf::Texture bgTexture2;    
      if (!bgTexture2.loadFromFile(BG_File2)) print_error("BG2");
	sf::Texture gameBG;
	  if (!gameBG.loadFromFile(Play_BG)) print_error("Game BG");
    sf::Texture spriteTextures;
      if (!spriteTextures.loadFromFile(Sprite_File)) print_error("Sprites");

      
    sf::RectangleShape background(sf::Vector2f(G_WIDTH,G_HEIGHT));
      background.setTexture(&bgTexture);
      background.setFillColor(sf::Color(50,250,250));
	  background.setPosition(G_ORIGIN,G_ORIGIN);
    
    sf::RectangleShape background2(sf::Vector2f(G_WIDTH,G_HEIGHT));
      background2.setTexture(&bgTexture2);
      background2.setFillColor(sf::Color(255, 255, 255,128));
	  background2.setPosition(G_ORIGIN,G_ORIGIN);
	 
	sf::RectangleShape Gbackground(sf::Vector2f(W_WIDTH,W_HEIGHT));
	  Gbackground.setTexture(&gameBG);
    
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
    
    EnemyArray enemies;
    sf::Sprite baddie;
      baddie.setTexture(spriteTextures);
      
    //z = atan(y/x)
    //Vx = V*cos(z) = V * sqr(x²/x²+y²)
    //Vy = V*sin(z)
    
    bool alive = true;
    int bgpos = 0;
    bool canExit = false;
    
    while (_myWindow->isOpen() and not canExit){
        
        bgpos++;
        _myWindow->clear();
	
        //Draw backgrounds
        _myWindow->draw(background);
        if (bgpos>=G_HEIGHT) bgpos -= G_HEIGHT;
		//Bottom bg2 copy
        background2.setPosition(G_ORIGIN,G_ORIGIN+bgpos-G_HEIGHT);
        _myWindow->draw(background2);
		//Top bg2 copy
        background2.setPosition(G_ORIGIN,G_ORIGIN+bgpos);
        _myWindow->draw(background2);
	
	
        sf::Event gameEvent;
        while (_myWindow->pollEvent(gameEvent)){
            if (gameEvent.type == sf::Event::Closed) _myWindow->close();
            if (gameEvent.type == sf::Event::KeyPressed){
                if (gameEvent.key.code == sf::Keyboard::Escape){
                    canExit = true;
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
		//play death sound
            }
            
            player.setPosition(G_ORIGIN+character.pos.x,G_ORIGIN+character.pos.y);
			_myWindow->draw(player);
            

        }

        for (int i = 0;i<enemies.amountEnemies();i++){  //Draw enemies
            sf::Vector2f spr=enemies.getSpritePos(i);
				baddie.setTextureRect(sf::IntRect(spr.x,spr.y,32,32));
				baddie.setOrigin(16,16);
            
            if (enemies.isMirror(i)) baddie.setScale(-1.f,1.f);
            else baddie.setScale(1.f,1.f);
			
			sf::Vector2f baddie_Position;
				baddie_Position = enemies.getEnemyPos(i);
				baddie.setPosition(G_ORIGIN+baddie_Position.x,G_ORIGIN+baddie_Position.y);
			
            _myWindow->draw(baddie);
        }
        
        for (int i = 0;i<bullets.amountBullets();i++){ //Draw bullets

            if (bullets.isFriendly(i)) {
                bulletImg.setTextureRect(sf::IntRect(64+12*7,160,12,12));
            } else {
                int bulletType = bullets.getType(i);
                if (bulletType < 10) bulletImg.setTextureRect(sf::IntRect(64+12*bulletType,160,12,12));
                else bulletImg.setTextureRect(sf::IntRect(64+12*(bulletType-10),172,12,12));
                bulletImg.setOrigin(6,6);
            }
            sf::Vector2f bullet_Position;
				bullet_Position = bullets.getBulletPos(i);
				bulletImg.setPosition(G_ORIGIN+bullet_Position.x,G_ORIGIN+bullet_Position.y);

			_myWindow->draw(bulletImg);
        }
        
        if (alive) { //Focus point
            if (character.isFocused()) {
                focusPoint.setPosition(G_ORIGIN+character.pos.x,G_ORIGIN+character.pos.y);
                _myWindow->draw(focusPoint);
            }
        } else {
	    if (enemies.amountEnemies()==0){
			print_error("Game over!");
			canExit = true;
	    }
	}
		_myWindow->draw(Gbackground);
        _myWindow->display();
    }
}

void Game::practice(int stage){
   
    sf::Texture bgTexture;    
      if (!bgTexture.loadFromFile(BG_File1)) print_error("BG1");
    sf::Texture bgTexture2;    
      if (!bgTexture2.loadFromFile(BG_File2)) print_error("BG2");
	sf::Texture gameBG;
	  if (!gameBG.loadFromFile(Practice_BG)) print_error("Game BG");
    sf::Texture spriteTextures;
      if (!spriteTextures.loadFromFile(Sprite_File)) print_error("Sprites");

      
    sf::RectangleShape background(sf::Vector2f(G_WIDTH,G_HEIGHT));
      background.setTexture(&bgTexture);
      background.setFillColor(sf::Color(50,50,250));
	  background.setPosition(G_ORIGIN,G_ORIGIN);
    
    sf::RectangleShape background2(sf::Vector2f(G_WIDTH,G_HEIGHT));
      background2.setTexture(&bgTexture2);
      background2.setFillColor(sf::Color(255, 255, 255,128));
	  background2.setPosition(G_ORIGIN,G_ORIGIN);
    
	sf::RectangleShape Gbackground(sf::Vector2f(W_WIDTH,W_HEIGHT));
	  Gbackground.setTexture(&gameBG);
	  
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
    
    EnemyArray enemies;
    sf::Sprite baddie;
      baddie.setTexture(spriteTextures);
      
    //z = atan(y/x)
    //Vx = V*cos(z) = V * sqr(x²/x²+y²)
    //Vy = V*sin(z)
    
    bool alive = true;
    int bgpos = 0;
    bool canExit = false;
    enemies.startPractice(stage);
    
    while (_myWindow->isOpen() and not canExit){
        
        bgpos++;
        _myWindow->clear();
	
	
        //Draw backgrounds
        _myWindow->draw(background);
        if (bgpos>=G_HEIGHT) bgpos -= G_HEIGHT;
		//Bottom bg2 copy
        background2.setPosition(G_ORIGIN,G_ORIGIN+bgpos-G_HEIGHT);
        _myWindow->draw(background2);
		//Top bg2 copy
        background2.setPosition(G_ORIGIN,G_ORIGIN+bgpos);
        _myWindow->draw(background2);
	
	
        sf::Event gameEvent;
        while (_myWindow->pollEvent(gameEvent)){
            if (gameEvent.type == sf::Event::Closed) _myWindow->close();
            if (gameEvent.type == sf::Event::KeyPressed){
                if (gameEvent.key.code == sf::Keyboard::Escape){
                    canExit = true;
                }
            }
        }
        
        

        bullets.updateArray(character.pos);
        enemies.updatePractice(bullets,alive);
        
        if (alive) {
            character.move(player);
            character.shoot(bullets);
            if (bullets.collides(character.pos,true) or enemies.collides(character.pos)){
                alive = false;
		//play death sound
            }
            
            player.setPosition(G_ORIGIN+character.pos.x,G_ORIGIN+character.pos.y);
	    _myWindow->draw(player);
            

        }

        for (int i = 0;i<enemies.amountEnemies();i++){  //Draw enemies
            sf::Vector2f spr=enemies.getSpritePos(i);
				baddie.setTextureRect(sf::IntRect(spr.x,spr.y,32,32));
				baddie.setOrigin(16,16);
            
            if (enemies.isMirror(i)) baddie.setScale(-1.f,1.f);
            else baddie.setScale(1.f,1.f);

			sf::Vector2f baddie_Position;
				baddie_Position = enemies.getEnemyPos(i);
				baddie.setPosition(G_ORIGIN+baddie_Position.x,G_ORIGIN+baddie_Position.y);
				
            _myWindow->draw(baddie);
        }
        
        for (int i = 0;i<bullets.amountBullets();i++){ //Draw bullets

            if (bullets.isFriendly(i)) {
                bulletImg.setTextureRect(sf::IntRect(64+12*7,160,12,12));
            } else {
                int bulletType = bullets.getType(i);
                if (bulletType < 10) bulletImg.setTextureRect(sf::IntRect(64+12*bulletType,160,12,12));
                else bulletImg.setTextureRect(sf::IntRect(64+12*(bulletType-10),172,12,12));
                bulletImg.setOrigin(6,6);
            }
            sf::Vector2f bullet_Position;
				bullet_Position = bullets.getBulletPos(i);
				bulletImg.setPosition(G_ORIGIN+bullet_Position.x,G_ORIGIN+bullet_Position.y);

			_myWindow->draw(bulletImg);
        }
        
        if (alive) { //Focus point
            if (character.isFocused()) {
                focusPoint.setPosition(G_ORIGIN+character.pos.x,G_ORIGIN+character.pos.y);
                _myWindow->draw(focusPoint);
            }
        } else {
	    if (enemies.amountEnemies()==0){
			print_error("Game over!");
			canExit = true;
	    }
	}
	
	if (enemies.finishPractice()){
	    canExit = true;
	}
		_myWindow->draw(Gbackground);
        _myWindow->display();
    }    
}