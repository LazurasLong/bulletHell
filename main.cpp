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
	
	
    sf::RectangleShape menuBG(sf::Vector2f(W_WIDTH,W_HEIGHT));
		menuBG.setTexture(&menuTex);
	sf::Sprite menuBamboo;
		menuBamboo.setTexture(bambooTex);
		menuBamboo.setTextureRect(sf::IntRect(0,705,790,690));
		menuBamboo.setPosition(5,5);
	sf::Sprite menuTitle;
		menuTitle.setTexture(titleTex);
		menuTitle.setPosition(25,25);
    
    int selection = 0;
    int selectPractice = 0;
    bool onPractice = false;
    
    while (window.isOpen()){
		window.clear();
		window.draw(menuBG);
		window.draw(menuBamboo);
		window.draw(menuTitle);
		
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
				if (event.type == sf::Event::KeyPressed){
				if (not onPractice){ //On main menu
					if (event.key.code == sf::Keyboard::Return){
					if (selection==0){
						Game game(&window);
						game.play();
					}
					else if (selection==1){
						onPractice = true;
						selectPractice = 0;
						for (int i=0; i<35;i++){
							menuBamboo.setTextureRect(sf::IntRect(0,705-i*20,790,690));
							//Baixar botons
							//Ensenyar captures de pantalla de escenaris
							window.clear();
							window.draw(menuBG);
							window.draw(menuBamboo);
							window.draw(menuTitle);
							//window.draw(buttons);
							//window.draw(captures);
							window.display();
						}
						//Move buttons
					}
					else if (selection==2){
						window.close();
					}
					} else if (event.key.code == sf::Keyboard::Escape){
						window.close();
					}
					if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right){
						selection = (selection+1)%3;
					}
					else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left){
						selection = (selection-1)%3;
					}
				}
				else { //On practice menu
					if (event.key.code == sf::Keyboard::Return){
						Game game(&window);
						game.practice(selectPractice+1);
					}
					else if (event.key.code == sf::Keyboard::Escape){
						onPractice = false;
						for (int i=0; i<35;i++){
							menuBamboo.setTextureRect(sf::IntRect(0,5+i*20,790,690));
							//Baixar botons
							//Ensenyar captures de pantalla de escenaris
							window.clear();
							window.draw(menuBG);
							window.draw(menuBamboo);
							window.draw(menuTitle);
							//window.draw(buttons);
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
		}
		
		window.display();
    }
  
}


int main(){
  
    menu();
    return -1;
}