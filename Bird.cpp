#include"Bird.h"
Bird::Bird() {
	bird = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2,WIDTH,HEIGHT };
	angle = 0;
	speed = 0;
}
void Bird::handleEvent(SDL_Event& e,Mix_Chunk* a) {
	if (e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0) {
		bird.y-=75;
		Mix_PlayChannel(-1,a,0);
		angle = -25;
		speed=0;
	}
}
void Bird::move() {
	bird.y+=speed+0.5*2;
	speed+=1;
	if(speed>=10){
		angle+=10;
		if(angle>=90) angle = 90;
	}
}
void Bird::render(SDL_Renderer *renderer,LTexture &tex,SDL_Rect* a) {
	tex.render(bird.x, bird.y, renderer,a,angle);
}
SDL_Rect Bird::getBird(){
	return bird;
}