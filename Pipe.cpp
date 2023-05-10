#include"Pipe.h"

Pipe::Pipe(int y) {
	rect1 = {SCREEN_WIDTH,y,WIDTH,HEIGHT};
	rect2 = {SCREEN_WIDTH,y-550,WIDTH,HEIGHT};
}
void Pipe::update(){
	rect1.x-=5;
	rect2.x-=5;
}
void Pipe::render(SDL_Renderer* renderer,LTexture &anh1,LTexture &anh2) {
	anh1.render(rect1.x, rect1.y, renderer);
	anh2.render(rect2.x, rect2.y, renderer);
}
SDL_Rect Pipe::getRect1() {
	return rect1;
}
SDL_Rect Pipe::getRect2(){
	return rect2;
}