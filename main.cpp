//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include "character.hpp"
//#include "bulletArray.hpp"
//#include "enemyArray.hpp"

#include "utils.hpp"

void menu(){
  
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), APP_NAME, sf::Style::None);
    sf::Texture menuTex;    
		if (!menuTex.loadFromFile(Menu_File)) print_error("Menu");
    sf::Texture bambooTex;
		if (!bambooTex.loadFromFile(Menu_Bamboo)) print_error("Bamboo");
    sf::Texture titleTex;
		if (!titleTex.loadFromFile(Menu_Title)) print_error("Title");
	sf::Texture spriTex;
		if (!spriTex.loadFromFile(Menu_Sprites)) print_error ("MenuSprites");
	
	
    sf::RectangleShape menuBG(sf::Vector2f(W_WIDTH,W_HEIGHT));
		menuBG.setTexture(&menuTex);
	sf::Sprite menuBamboo;
		menuBamboo.setTexture(bambooTex);
		menuBamboo.setTextureRect(sf::IntRect(0,705,790,690));
		menuBamboo.setPosition(5,5);
	sf::Sprite menuTitle;
		menuTitle.setTexture(titleTex);
		menuTitle.setPosition(25,25);
		
	sf::Sprite menuButton1;
		menuButton1.setTexture(spriTex);
		menuButton1.setTextureRect(sf::IntRect(0,256,397,75));
		menuButton1.setPosition(75,300);
	sf::Sprite menuButton2;
		menuButton2.setTexture(spriTex);
		menuButton2.setTextureRect(sf::IntRect(397,256,397,75));
		menuButton2.setPosition(75,400);
	sf::Sprite menuButton3;
		menuButton3.setTexture(spriTex);
		menuButton3.setTextureRect(sf::IntRect(794,256,397,75));
		menuButton3.setPosition(75,500);
	sf::Sprite selectButton;
		selectButton.setTexture(spriTex);
		selectButton.setTextureRect(sf::IntRect(1290,256,30,75));
		selectButton.setPosition(30,300);
		
    
    int selection = 0;
    int selectPractice = 0;
    bool onPractice = false;
    
	sf::Vector2i grabbedOffset;
    bool grabbedWindow = false;
	
	
    while (window.isOpen()){
		window.clear();
		window.draw(menuBG);
		window.draw(menuBamboo);
		window.draw(menuTitle);
		window.draw(menuButton1);
		window.draw(menuButton2);
		window.draw(menuButton3);
		window.draw(selectButton);
		
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::KeyPressed){
				if (not onPractice){ //On main menu
					if (event.key.code == sf::Keyboard::Return){
						if (selection==0){
							Game game(&window);
							game.play();
						}
						else if (selection==1){
							onPractice = true;
							selectPractice = 0;
							for (int i=0; i<36;i++){
								menuBamboo.setTextureRect(sf::IntRect(0,705-i*20,790,690));
								menuButton1.setPosition(75,300+20*i);
								menuButton2.setPosition(75,400+20*i);
								menuButton3.setPosition(75,500+20*i);
								selectButton.setPosition(30,(300+selection*100)+20*i);
								//Baixar botons
								//Ensenyar captures de pantalla de escenaris
								window.clear();
								window.draw(menuBG);
								window.draw(menuBamboo);
								window.draw(menuTitle);
								window.draw(menuButton1);
								window.draw(menuButton2);
								window.draw(menuButton3);
								window.draw(selectButton);
								//window.draw(captures);
								window.display();
							}
							//Move buttons
						}
						else if (selection==2){
							window.close();
						}
					}
					else if (event.key.code == sf::Keyboard::Escape){
						window.close();
					}
					
					if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right){
						selection = (selection+1)%3;
						selectButton.setPosition(30,300+selection*100);
					}
					else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left){
						selection = (selection+2)%3;
						selectButton.setPosition(30,300+selection*100);
					}
				}
				else { //On practice menu
					if (event.key.code == sf::Keyboard::Return){
						Game game(&window);
						game.practice(selectPractice+1);
					}
					else if (event.key.code == sf::Keyboard::Escape){
						onPractice = false;
						for (int i=0; i<36;i++){
							menuBamboo.setTextureRect(sf::IntRect(0,5+i*20,790,690));
							menuButton1.setPosition(75,300+700-20*i);
							menuButton2.setPosition(75,400+700-20*i);
							menuButton3.setPosition(75,500+700-20*i);
							selectButton.setPosition(30,(300+selection*100)+700-20*i);
							//Baixar botons
							//Ensenyar captures de pantalla de escenaris
							window.clear();
							window.draw(menuBG);
							window.draw(menuBamboo);
							window.draw(menuTitle);
							window.draw(menuButton1);
							window.draw(menuButton2);
							window.draw(menuButton3);
							window.draw(selectButton);
							//window.draw(captures);
							window.display();
						}
					}
					
					if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right){
						selectPractice = (selectPractice+1)%5;
					}
					else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left){
						selectPractice = (selectPractice-1)%5;
					} 
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
            }
			
		}
		grabbedWindow = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (grabbedWindow) window.setPosition(sf::Mouse::getPosition() + grabbedOffset);

        window.display();
		
		
    }
  
}


int main(){
  
    menu();
    return -1;
}