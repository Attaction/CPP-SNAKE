#ifndef START_CPP
#define START_CPP

#include "start.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>


void Start::startMenu(SDL_Renderer* renderer, bool& game_close, bool& start, int WIDTH, int HEIGHT) {
    while (!game_close || start) {
        SDL_Event event;

        SDL_RenderClear(renderer);
        boxRGBA(renderer, 0, 0, WIDTH, HEIGHT, 77, 59, 59, 255);
        
        TTF_Font *startbigfont = TTF_OpenFont("comic.ttf", 70);
        TTF_Font *startsmallfont = TTF_OpenFont("comic.ttf", 15);
        SDL_Color White = {255, 255, 255};

        if (startbigfont == NULL || startsmallfont == NULL) {
            std::cerr << "Nem sikerult megnyitni a fontot! " << TTF_GetError();
            exit(1);
        }
        
 
        SDL_Surface *msg;
        SDL_Texture *msg_t;
        SDL_Rect msgpos = {0, 0, 0, 0};
        msg = TTF_RenderUTF8_Blended(startbigfont, "SNAKE", White);
        msg_t = SDL_CreateTextureFromSurface(renderer, msg);
        msgpos.x = (WIDTH - msg->w) / 2;
        msgpos.y = (HEIGHT - msg->h) / 2;
        msgpos.w = msg->w;
        msgpos.h = msg->h;
        SDL_RenderCopy(renderer, msg_t, NULL, &msgpos);

        SDL_Surface *smallmsg;
        SDL_Texture *smallmsg_t;
        SDL_Rect smallmsgpos = {0, 0, 0, 0};
        smallmsg = TTF_RenderUTF8_Blended(startsmallfont, "Made by Zalavary Daniel", White);
        smallmsg_t = SDL_CreateTextureFromSurface(renderer, smallmsg);
        smallmsgpos.x = (WIDTH - smallmsg->w) / 2;
        smallmsgpos.y = (HEIGHT - msg->h) / 2;
        smallmsgpos.w = smallmsg->w;
        smallmsgpos.h = smallmsg->h;
        SDL_RenderCopy(renderer, smallmsg_t, NULL, &smallmsgpos);
        
        SDL_Surface *startmsg;
        SDL_Texture *startmsg_t;
        SDL_Rect startmsgpos = {0, 0, 0, 0};
        startmsg = TTF_RenderUTF8_Blended(startsmallfont, "PRESS A KEY TO START", White);
        startmsg_t = SDL_CreateTextureFromSurface(renderer, startmsg);
        startmsgpos.x = (WIDTH - smallmsg->w) / 2;
        startmsgpos.y = (HEIGHT - msg->h + 300) / 2;
        startmsgpos.w = startmsg->w;
        startmsgpos.h = startmsg->h;
        SDL_RenderCopy(renderer, startmsg_t, NULL, &startmsgpos);

        SDL_Surface *controls;
        SDL_Texture *controls_t;
        SDL_Rect controlspos = {0, 0, 0, 0};
        controls = TTF_RenderUTF8_Blended(startsmallfont, "MOVE SNAKE WITH ARROW KEYS. PRESS (Q) TO EXIT.", White);
        controls_t = SDL_CreateTextureFromSurface(renderer, controls);
        controlspos.x = (WIDTH - controls->w) / 2;
        controlspos.y = HEIGHT - controls->h;
        controlspos.w = controls->w;
        controlspos.h = controls->h;
        SDL_RenderCopy(renderer, controls_t, NULL, &controlspos);
        
        SDL_RenderPresent(renderer);

        SDL_WaitEvent(&event);
        while(event.type != SDL_KEYDOWN) {
            SDL_WaitEvent(&event);
        }
        if (event.key.keysym.sym == SDLK_q) {
            game_close = true;
            break;
        }
        else {
            start = false;
            break;
        }
        SDL_FreeSurface(msg);
        SDL_DestroyTexture(msg_t);
    }
};

#endif