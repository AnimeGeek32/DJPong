/*
 *  ball.h
 *  DJPong
 *
 *  Created by Daniel Jung on 6/16/08.
 *  Copyright 2008 Dimensional Eye. All rights reserved.
 *
 */

#ifndef _BALL_H_
#define _BALL_H_

#include "Global.h"

class Ball
{
public:
	Ball();
	~Ball();
	
	SDL_Surface *getImage();
	float getPosX();
	float getPosY();
	float getVelX();
	float getVelY();
	float getWidth();
	float getHeight();
	float getSpeed();
	
	void setImage();
	void setPosX( float n );
	void setPosY( float n );
	void setVelX( float n );
	void setVelY( float n );
	void setSpeed( float n );
private:
	SDL_Surface *image;
	float posX;
	float posY;
	float velX;
	float velY;
	float width;
	float height;
	float speed;
};

#endif
