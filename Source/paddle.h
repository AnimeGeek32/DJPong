/*
 *  paddle.h
 *  DJPong
 *
 *  Created by Daniel Jung on 6/16/08.
 *  Copyright 2008 Dimensional Eye. All rights reserved.
 *
 */

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Global.h"

class Paddle
{
public:
	Paddle();
	~Paddle();
	
	SDL_Surface *getImage();
	float getPosX();
	float getPosY();
	float getVelocity();
	
	void setImage();
	void setPosX( float n );
	void setPosY( float n );
	void setVelocity( float n );
	void MoveUp();
	void MoveDown();
private:
	SDL_Surface *image;
	float posX, posY;
	float velocity;
};

#endif
