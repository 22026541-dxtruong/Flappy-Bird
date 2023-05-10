#ifndef BIRD_H
#define BIRD_H

#include"LTexture.h"

class Bird {
	private:
		SDL_Rect bird;
		double angle;
		int speed;
	public:
		static const int WIDTH = 45;
		static const int HEIGHT = 32;
		Bird();
		void handleEvent(SDL_Event& e,Mix_Chunk* a);
		void move();
		void render(SDL_Renderer* renderer,LTexture &tex,SDL_Rect* a);
		SDL_Rect getBird();
};

#endif