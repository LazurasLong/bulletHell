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


#define W_WIDTH 800
#define W_HEIGHT 700
#define G_WIDTH 400
#define G_HEIGHT 600
#define G_ORIGIN 50

#define APP_NAME "My game"

#define M_VOLUME 20
#define S_VOLUME 20

using namespace std;

static const char* Menu_File = "./resources/images/MenuBG.png";
static const char* Menu_Bamboo = "./resources/images/Bamboo.png";
static const char* Menu_Title = "./resources/images/MenuTitle.png";
static const char* Menu_Sprites = "./resources/images/MenuSprites.png";

static const char* BG_File1 = "./resources/images/BGTexture.png";
static const char* BG_File2 = "./resources/images/BGTexture2.png";
static const char* Play_BG = "./resources/images/GameBG.png";
static const char* Practice_BG = "./resources/images/GameBGPractice.png";
static const char* Sprite_File = "./resources/images/Sprites.png";

static const char* Font_File = "./resources/ChaparralPro.ttf";



static const char* Menu_Music = "./resources/music/menu.ogg";
static const char* Game_Music = "./resources/music/game1.ogg";
static const char* Game_Loop_Music = "./resources/music/game2.ogg";
static const char* Select_Sound = "./resources/music/select.ogg";
static const char* Death_Sound = "./resources/music/death.ogg";
static const char* Shoot_Sound = "./resources/music/shoot.wav";
static const char* Hit_Sound = "./resources/music/hit.ogg";
static const char* Kill_Sound = "./resources/music/kill.wav";


static int maxim(int a, int b) {
    return (a>b)?a : b;
}
static int minim(int a, int b) {
	return (a<b)?a : b;
}

static void print_error(string text) {
    std::cout << "Failed to load " << text << std::endl;
}

#endif // UTILS_HPP
