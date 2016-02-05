#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <cmath>
#include <utility>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


#include "bullet.hpp"
#include "bulletArray.hpp"
#include "enemy.hpp"
#include "enemyArray.hpp"
#include "character.hpp"
#include "game.hpp"


#define W_WIDTH 400
#define W_HEIGHT 600

#define APP_NAME "My game"
using namespace std;

static const char* Menu_File = "./images/Menu.png";
static const char* BG_File1 = "./images/BGTexture.png";
static const char* BG_File2 = "./images/BGTexture2.png";
static const char* Sprite_File = "./images/Sprites.png";


//static const char* file_titleHTP = "./resources/images/howToPlay/howToPlayTitle.png";
//static const char* file_bgHTP = "./resources/images/howToPlay/bg.png";

//static const std::vector<float> vel = {1.0, 0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1};

static int maxim(int a, int b) {
    return (a>b)?a : b;
}

static void print_error(string text) {
    std::cout << "Failed to load " << text << std::endl;
}

#endif // UTILS_HPP
