/*
 *  Global.h
 *  DJPong
 *
 *  Created by Daniel Jung on 6/13/08.
 *  Copyright 2008 Dimensional Eye. All rights reserved.
 *
 */

#include "SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_mixer/SDL_mixer.h"
#include "SDL_ttf/SDL_ttf.h"

#include <math.h>
#include <string>
using namespace std;

#include "ball.h"
#include "paddle.h"

SDL_Surface *loadImage( string filename );
SDL_Surface *loadImage( string filename, Uint8 r, Uint8 g, Uint8 b );
void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void CheckKeyInput();
void CheckCollision();
void Render();
void Logic();
void UpdateScore();
void Restart();
