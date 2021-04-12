/*
 *  ball.cpp
 *  DJPong
 *
 *  Created by Daniel Jung on 6/16/08.
 *  Copyright 2008 Dimensional Eye. All rights reserved.
 *
 */

#include "ball.h"

Ball::Ball()
{
	image = NULL;
	posX = 320.0f;
	posY = 240.0f;
	velX = 4.0f;
	velY = -5.3f;
	width = 16.0f;
	height = 16.0f;
	speed = 1.0f;
}

Ball::~Ball()
{
	// free memory
	SDL_FreeSurface(image);
}

SDL_Surface* Ball::getImage()
{
	return image;
}

float Ball::getPosX()
{
	return posX;
}

float Ball::getPosY()
{
	return posY;
}

float Ball::getVelX()
{
	return velX;
}

float Ball::getVelY()
{
	return velY;
}

float Ball::getWidth()
{
	return width;
}

float Ball::getHeight()
{
	return height;
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setImage()
{
	image = loadImage( "data/Ball.png", 0, 0, 0 );
}

void Ball::setPosX( float n )
{
	posX = n;
}

void Ball::setPosY( float n )
{
	posY = n;
}

void Ball::setVelX( float n )
{
	velX = n;
}

void Ball::setVelY( float n )
{
	velY = n;
}

void Ball::setSpeed( float n )
{
	speed = n;
}
