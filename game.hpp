#ifndef _GAME_HPP_
#define _GAME_HPP
#include "utils.hpp"

class Game
{
public:

  Game(sf::RenderWindow* window);
  void play();
  void practice(int);
  
private:  
  
  sf::RenderWindow* _myWindow;
  
};

#endif