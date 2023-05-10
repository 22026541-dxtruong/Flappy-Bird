#include"LTexture.h"
LTexture::LTexture() {
    mat = NULL;
    width = 0;
    height = 0;
}
LTexture::~LTexture() {
    free();
}
bool LTexture::loadIMG(string path,SDL_Renderer* renderer) {
    free();
    SDL_Surface* load = IMG_Load(path.c_str());
    if (load == NULL) {
        cout << "IMG_Load\n";
        IMG_GetError();
    }
    else {
        mat = SDL_CreateTextureFromSurface(renderer, load);
        if (mat == NULL) {
            cout << "loadIMG\n";
            SDL_GetError();
        }
        else {
            width = load->w;
            height = load->h;
        }
        SDL_FreeSurface(load);
    }
    return mat != NULL;
}
bool LTexture::loadTTF(TTF_Font* font,string path, SDL_Color color, SDL_Renderer* renderer) {
    free();
	SDL_Surface* load = TTF_RenderText_Solid(font,path.c_str(),color);
	if(load == NULL){
		cout<<"TTF_load\n";
		TTF_GetError();
	}else{
		mat = SDL_CreateTextureFromSurface(renderer,load);
		if(mat == NULL){
			cout<<"loadTTF\n";
			SDL_GetError();
		}else{
			width = load->w;
			height = load->h;
		}
		SDL_FreeSurface(load);
	}
    return mat != NULL;
}
void LTexture::free() {
    if (mat != NULL) {
        SDL_DestroyTexture(mat);
        mat = NULL;
        width = 0;
        height = 0;
    }
}
void LTexture::render(int x, int y,SDL_Renderer* renderer, SDL_Rect* clip,double angle,SDL_Point* center,SDL_RendererFlip flip) {
    SDL_Rect rect = { x,y,width,height };
    if (clip != NULL) {
        rect.w = clip->w;
        rect.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, mat, clip, &rect,angle,center,flip);
}