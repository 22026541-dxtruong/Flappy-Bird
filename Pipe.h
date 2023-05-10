#ifndef PIPE_H
#define PIPE_H

#include"LTexture.h"

class Pipe {
private:
	SDL_Rect rect1;
	SDL_Rect rect2;
public:
	static const int WIDTH = 65;
	static const int HEIGHT = 400;
	Pipe(int y);
	void update();
	void render(SDL_Renderer* renderer,LTexture &anh1,LTexture &anh2);
	SDL_Rect getRect1();
	SDL_Rect getRect2();
};

#endif