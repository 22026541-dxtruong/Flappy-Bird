
#include"LTexture.h"
#include"Pipe.h"
#include"Bird.h"

LTexture flappyBird;
LTexture pipe1;
LTexture pipe2;
LTexture background;
LTexture ground;
LTexture start;
LTexture score;
LTexture bestScore;
LTexture gameOver;
SDL_Rect imageBird[3];
SDL_Rect g_ground = {0,SCREEN_HEIGHT-120,360,120};
vector<Pipe> pipe;

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL_Init\n";
		SDL_GetError();
		success = false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	cuaso = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (cuaso == NULL) {
		cout << "window\n";
		SDL_GetError();
		success = false;
	}
	else {
		but = SDL_CreateRenderer(cuaso, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (but == NULL) {
			cout << "renderer\n";
			SDL_GetError();
			success = false;
		}
		else {
			SDL_SetRenderDrawColor(but, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) {
				cout << "IMG_Init\n";
				IMG_GetError();
				success = false;
			}
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
				cout<<"Mix_Init\n";
				Mix_GetError();
				success = false;
			}
			if( TTF_Init() == -1 ){
                cout<<"TTF_Init\n";
				TTF_GetError();
				success = false;
            }
		}
	}
	return success;
}
bool loadMedia() {
	bool success = true;
	font = TTF_OpenFont("font.ttf",60);
	if(font == NULL){
		cout<<"font\n";
		TTF_GetError();
		success = false;
	}
	if (!flappyBird.loadIMG("image/Bird.png",but)) {
		cout << "flappyBird\n";
		success = false;
	}
	else {
		imageBird[0] = { 0,0,44,32 };
		imageBird[1] = { 0,32,44,32 };
		imageBird[2] = {0,64,44,32};
	}
	if (!pipe1.loadIMG("image/Pipe1.png",but)) {
		cout << "pipe1\n";
		success = false;
	}
	if (!pipe2.loadIMG("image/Pipe2.png", but)) {
		cout << "pipe12\n";
		success = false;
	}
	if (!background.loadIMG("image/Background.png", but)) {
		cout << "background\n";
		success = false;
	}
	if (!ground.loadIMG("image/Ground.png", but)) {
		cout << "ground\n";
		success = false;
	}
	if(!start.loadIMG("image/start.png",but)){
		cout<<"start\n";
		success = false;
	}
	if(!gameOver.loadIMG("image/GameOver.png",but)){
		cout<<"diem\n";
		success = false;
	}
	die = Mix_LoadWAV("music/die.wav");
	if(die == NULL){
		cout<<"die\n";
		Mix_GetError();
		success = false;
	}
	flap = Mix_LoadWAV("music/flap.wav");
	if(flap == NULL){
		cout<<"flap\n";
		Mix_GetError();
		success = false;
	}
	point = Mix_LoadWAV("music/point.wav");
	if(point == NULL){
		cout<<"point\n";
		Mix_GetError();
		success = false;
	}
	swosh = Mix_LoadWAV("music/swosh.wav");
	if(swosh == NULL){
		cout<<"swosh\n";
		Mix_GetError();
		success = false;
	}
	return success;
}
void close() {
	flappyBird.free();
	pipe1.free();
	pipe2.free();
	background.free();
	ground.free();
	start.free();
	score.free();
	bestScore.free();
	TTF_CloseFont(font);
	font = NULL;
	Mix_FreeChunk(die);
	Mix_FreeChunk(flap);
	Mix_FreeChunk(point);
	Mix_FreeChunk(swosh);
	die = NULL;
	flap = NULL;
	point = NULL;
	swosh = NULL;
	pipe.clear();
	SDL_DestroyRenderer(but);
	SDL_DestroyWindow(cuaso);
	cuaso = NULL;
	but = NULL;
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
bool check(SDL_Rect a,SDL_Rect b){
	if(a.x+a.w<=b.x) return false;
	if(a.x>=b.x+b.w) return false;
	if(a.y+a.h<=b.y) return false;
	if(a.y>=b.y+b.h) return false;
	return true;
}
bool setMouse(SDL_Event &e,SDL_Rect a){
	if(e.type == SDL_MOUSEBUTTONDOWN){
		int x,y;
		bool inside = true;
		SDL_GetMouseState(&x,&y);
		if(x<a.x){
			inside = false;
		}else if(x>a.x+a.w){
			inside = false;
		}else if(y<a.y){
			inside = false;
		}else if(y>a.y+a.h){
			inside = false;
		}
		if(inside){
			Mix_PlayChannel(-1,swosh,0);
			return true;
		}
	}
	return false;
}

int main(int argc, char* argv[]) {
	if (!init()) {
		cout << "init\n";
	}
	else {
		if (!loadMedia()) {
			cout << "loadMedia\n";
		}
		else {
			int bs=0;
			fstream file;
			file.open("bestScore.txt");
			file>>bs;
			file.close();
			while(true){
				bool quit = false;
				SDL_Event e;
				Bird bird;
				int n=0;
				SDL_Rect exit1 = {142,459,79,28};
				while(!quit){
					while(SDL_PollEvent(&e)){
						if(e.type == SDL_QUIT){
							quit = true;
						}
						if(setMouse(e,exit1)){
							close();
							return 0;
						}
						if(e.type==SDL_MOUSEBUTTONDOWN){
							Mix_PlayChannel(-1,swosh,0);
							quit = true;
						}
					}
					SDL_SetRenderDrawColor(but,255,255,255,255);
					SDL_RenderClear(but);
					start.render(0,0,but);
					flappyBird.render(SCREEN_WIDTH/4,SCREEN_HEIGHT/2,but,&imageBird[n/3]);
					SDL_RenderPresent(but);
					SDL_Delay(40);
					n++;
					if(n>6) n=0;
				}
				int t=0;
				int s=0;
				SDL_Color color={255,255,255};
				quit = false;
				int frame = 0;
				while (!quit) {
					while (SDL_PollEvent(&e) != 0) {
						if (e.type == SDL_QUIT) {
							quit = true;
						}
						bird.handleEvent(e,flap);
					}
					bird.move();
					if(t%50==0){
						int y=rand()%(SCREEN_HEIGHT-220-220+1)+220;
						Pipe x = Pipe(y);
						pipe.push_back(x);
					}
					SDL_SetRenderDrawColor(but, 255, 255, 255, 255);
					SDL_RenderClear(but);
					background.render(frame,0, but);
					background.render(SCREEN_WIDTH + frame, 0, but);
					for(int i=0;i<pipe.size();i++){
						pipe[i].render(but,pipe1,pipe2);
						pipe[i].update();
					}
					if(!score.loadTTF(font,to_string(s),color,but)){
						cout<<"score\n";
					}
					ground.render( frame, SCREEN_HEIGHT - 120,but);
					ground.render(SCREEN_WIDTH+frame,SCREEN_HEIGHT-120,but);
					bird.render(but,flappyBird,&imageBird[-frame%3]);
					score.render(SCREEN_WIDTH/2-15,30,but);
					SDL_RenderPresent(but);
					SDL_Delay(40);
					frame -= 1;
					if (frame <= -SCREEN_WIDTH) frame = 0;
					t++;
					if(pipe[0].getRect1().x+Pipe::WIDTH<0){
						pipe.erase(pipe.begin());
					}
					if(bird.getBird().x==pipe[0].getRect1().x){
						Mix_PlayChannel(-1,point,0);
						s++;
					}
					if(check(bird.getBird(),g_ground)||check(bird.getBird(),pipe[0].getRect1())||check(bird.getBird(),pipe[0].getRect2())){
						Mix_PlayChannel(-1,die,0);
						quit = true;
					}
				}
				quit = false;
				SDL_Rect restart = {56,432,79,27};
				SDL_Rect exit2 = {225,433,79,26};
				if(bs<s){
					bs=s;
					file.open("bestScore.txt");
					file<<bs;
					file.close();
				}
				while(!quit){
					while(SDL_PollEvent(&e)){
						if(e.type == SDL_QUIT){
							quit = true;
						}
						if(setMouse(e,restart)){
							pipe.clear();
							quit = true;
						}
						if(setMouse(e,exit2)){
							close();
							return 0;
						}
					}
					if(!check(bird.getBird(),g_ground)){
						SDL_SetRenderDrawColor(but, 255, 255, 255, 255);
						SDL_RenderClear(but);
						background.render(frame,0, but);
						background.render(SCREEN_WIDTH + frame, 0, but);
						for(int i=0;i<pipe.size();i++){
							pipe[i].render(but,pipe1,pipe2);
						}
						ground.render( frame, SCREEN_HEIGHT - 120,but);
						ground.render(SCREEN_WIDTH+frame,SCREEN_HEIGHT-120,but);
						bird.move();
						bird.render(but,flappyBird,&imageBird[-frame%3]);
						SDL_Delay(30);
					}else{
						gameOver.render(0,0,but);
						score.render(170,215,but);
						if(!bestScore.loadTTF(font,to_string(bs),color,but)){
							cout<<"score\n";
						}
						bestScore.render(170,280,but);
					}
					SDL_RenderPresent(but);
				}
			}
		}
	}
	close();
	return 0;
}
