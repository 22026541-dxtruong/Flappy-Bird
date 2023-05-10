#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<vector>
#include<fstream>
using namespace std;

const int SCREEN_WIDTH = 360;
const int SCREEN_HEIGHT = 640;

static SDL_Window* cuaso = NULL;
static SDL_Renderer* but = NULL;

static TTF_Font* font = NULL;

static Mix_Chunk* die = NULL;
static Mix_Chunk* flap = NULL;
static Mix_Chunk* point = NULL;
static Mix_Chunk* swosh = NULL;

#endif
