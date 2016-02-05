//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include "character.hpp"
//#include "bulletArray.hpp"
//#include "enemyArray.hpp"

#include "utils.hpp"

void menu(){
  
    sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HEIGHT), APP_NAME);
    sf::Texture menuTexture;    
	if (!menuTexture.loadFromFile(Menu_File)) print_error("Menu");
    sf::RectangleShape menuBG(sf::Vector2f(W_WIDTH,W_HEIGHT));
	menuBG.setTexture(&menuTexture);
    int selection = 0;
    bool onPractice = false;
    
    while (window.isOpen()){
	window.clear();
	
	
	sf::Event event;
	while (window.pollEvent(event)){
	    if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed){
		if (not onPractice){
		    if (event.key.code == sf::Keyboard::Return){
			if (selection==0){
			    Game game(&window);
			    game.play();
			}
			else if (selection==1){
			    onPractice = true;
			    //Move buttons
			}
			else if (selection==2){
			    window.close();
			   }
		    } else if (event.key.code == sf::Keyboard::Escape){
			    window.close();
		    }
		}
		else { //On practice menu
		    if (event.key.code == sf::Keyboard::Return){
			Game game(&window);
			game.practice(selection+1);
		    }
		    else if (event.key.code == sf::Keyboard::Escape){
			onPractice = false;
		    }
		}
		
		if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::Right){
		    selection = (selection+1)%3;
		}
		else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left){
		    selection = (selection-1)%3;
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