#ifndef LTEXTURE_H
#define LTEXTURE_H

#include"CommonFunc.h"
class LTexture {
private:
    SDL_Texture* mat;
    int width;
    int height;
public:
    LTexture();
    ~LTexture();
    bool loadIMG(string path,SDL_Renderer* renderer);
    bool loadTTF(TTF_Font* font,string path, SDL_Color color,SDL_Renderer* renderer);
    void free();
    void render(int x, int y,SDL_Renderer* renderer, SDL_Rect* clip = NULL,double abgle = 0,SDL_Point* center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif