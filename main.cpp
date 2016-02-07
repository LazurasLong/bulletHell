//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include "character.hpp"
//#include "bulletArray.hpp"
//#include "enemyArray.hpp"

#include "utils.hpp"

void menu(){
  
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), APP_NAME, sf::Style::None);
		window.setFramerateLimit(60);
	
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
		selectButton.setTextureRect(sf::IntRect(1291,256,30,75));
		selectButton.setPosition(30,300);
		
	sf::Sprite enemyPractice;
		enemyPractice.setTexture(spriTex);
		enemyPractice.setTextureRect(sf::IntRect(0,0,397,256));
		enemyPractice.setPosition(400,350-700);
		enemyPractice.setOrigin(198,128);
	sf::Sprite practiceButton1;
		practiceButton1.setTexture(spriTex);
		practiceButton1.setTextureRect(sf::IntRect(1241,256,50,75));
		practiceButton1.setPosition(150,350-700);
		practiceButton1.setOrigin(25,37);
	sf::Sprite practiceButton2;
		practiceButton2.setTexture(spriTex);
		practiceButton2.setTextureRect(sf::IntRect(1191,256,50,75));
		practiceButton2.setPosition(650,350-700);
		practiceButton2.setOrigin(25,37);
    
	sf::SoundBuffer bufMenu;
		if (!bufMenu.loadFromFile(Menu_Music)) print_error("Death sound");
	sf::SoundBuffer bufSelect;
		if (!bufSelect.loadFromFile(Select_Sound)) print_error("Select sound");
    sf::Sound menuMusic;
		menuMusic.setBuffer(bufMenu);
		menuMusic.setVolume(M_VOLUME);
		menuMusic.setLoop(true);
		menuMusic.play();
	sf::Sound selectSound;
		selectSound.setBuffer(bufSelect);
		selectSound.setVolume(S_VOLUME);
	
		
    int selection = 0;
    int selectPractice = 0;
    bool onPractice = false;
    
	sf::Vector2i grabbedOffset;
    bool grabbedWindow = false;
	bool windowFocused = false;
	
    while (window.isOpen()){
		window.clear();
		window.draw(menuBG);
		window.draw(menuBamboo);

		
		if (not onPractice) selectButton.setPosition(30,300+selection*100);
		window.draw(menuButton1);
		window.draw(menuButton2);
		window.draw(menuButton3);
		window.draw(selectButton);
		
		if (onPractice) enemyPractice.setTextureRect(sf::IntRect(397*selectPractice,0,397,256));
		window.draw(enemyPractice);
		window.draw(practiceButton1);
		window.draw(practiceButton2);
		
		window.draw(menuTitle);
		
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::KeyPressed){
				if (not onPractice){ //On main menu
					if (event.key.code == sf::Keyboard::Return){
						if (selection==0){
							menuMusic.stop();
							Game game(&window);
							game.play();
							menuMusic.play();
						}
						else if (selection==1){
							onPractice = true;
							selectPractice = 0;
							selectSound.setPitch(10);
							enemyPractice.setTextureRect(sf::IntRect(397*selectPractice,0,397,256));
							for (int i=0; i<36;i++){
								window.clear();
								window.draw(menuBG);
								window.draw(menuBamboo);
								window.draw(menuButton1);
								window.draw(menuButton2);
								window.draw(menuButton3);
								window.draw(selectButton);
								window.draw(enemyPractice);
								window.draw(practiceButton1);
								window.draw(practiceButton2);
								window.draw(menuTitle);
								window.display();
								
								menuBamboo.setTextureRect(sf::IntRect(0,705-i*20,790,690));
								menuButton1.setPosition(75,300+20*i);
								menuButton2.setPosition(75,400+20*i);
								menuButton3.setPosition(75,500+20*i);
								selectButton.setPosition(30,(300+selection*100)+20*i);
								enemyPractice.setPosition(400,350-700+20*i);
								practiceButton1.setPosition(150,350-700+20*i);
								practiceButton2.setPosition(650,350-700+20*i);
								
								menuMusic.setVolume(M_VOLUME-i/2);
								
								
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
						selectSound.play();
						selection = (selection+1)%3;
					}
					else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left){
						selectSound.play();
						selection = (selection+2)%3;
					}
				}
				else { //On practice menu
					if (event.key.code == sf::Keyboard::Return){
						menuMusic.stop();
						Game game(&window);
						game.practice(selectPractice+1);
						menuMusic.play();
					}
					else if (event.key.code == sf::Keyboard::Escape){
						onPractice = false;
						selectSound.setPitch(1);
						for (int i=0; i<36;i++){
							window.clear();
							window.draw(menuBG);
							window.draw(menuBamboo);
							window.draw(menuButton1);
							window.draw(menuButton2);
							window.draw(menuButton3);
							window.draw(selectButton);
							window.draw(enemyPractice);
							window.draw(practiceButton1);
							window.draw(practiceButton2);
							window.draw(menuTitle);
							window.display();
							
							menuBamboo.setTextureRect(sf::IntRect(0,5+i*20,790,690));
							menuButton1.setPosition(75,300+700-20*i);
							menuButton2.setPosition(75,400+700-20*i);
							menuButton3.setPosition(75,500+700-20*i);
							selectButton.setPosition(30,(300+selection*100)+700-20*i);
							enemyPractice.setPosition(400,350-20*i);
							practiceButton1.setPosition(150,350-20*i);
							practiceButton2.setPosition(650,350-20*i);
							
							
							menuMusic.setVolume(M_VOLUME-36/2+i/2);
							
						}
					}
					
					if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right){
						selectSound.play();
						selectPractice = (selectPractice+1)%5;
					}
					else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left){
						selectSound.play();
						selectPractice = (selectPractice+4)%5;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left and windowFocused) grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
            }
			else if (event.type == sf::Event::LostFocus){
				windowFocused = false;
			}
			else if (event.type == sf::Event::GainedFocus){
				windowFocused = true;
			}
		}
		if (windowFocused){
			grabbedWindow = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			if (grabbedWindow) window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
		}
        window.display();
		
		
    }	
  
}


int main(){
  
    menu();
    return -1;
}