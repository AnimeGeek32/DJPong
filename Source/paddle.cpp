/*
 *  paddle.cpp
 *  DJPong
 *
 *  Created by Daniel Jung on 6/16/08.
 *  Copyright 2008 Dimensional Eye. All rights reserved.
 *
 */

#include "paddle.h"

Paddle::Paddle()
{
	image = NULL;
	posX = 0.0f;
	posY = 0.0f;
	velocity = 0.0f;
}

Paddle::~Paddle()
{
	SDL_FreeSurface( image );
}

SDL_Surface* Paddle::getImage()
{
	return image;
}

float Paddle::getPosX()
{
	return posX;
}

float Paddle::getPosY()
{
	return posY;
}

float Paddle::getVelocity()
{
	return velocity;
}

void Paddle::setImage()
{
	image = loadImage( "data/Paddle.png", 0, 0, 0 );
}

void Paddle::setPosX( float n )
{
	posX = n;
}

void Paddle::setPosY( float n )
{
	posY = n;
}

void Paddle::setVelocity( float n )
{
	velocity = n;
}

void Paddle::MoveUp()
{
	if( posY > 0 )
	{
		if( (velocity >= -6.0f) && (velocity <= 0.0f) )
		{
			velocity -= 2.0f;
		}
		else if( velocity > 0.0f )
		{
			velocity = 0.0f;
		}
		posY += velocity;
	}
	else
	{
		velocity = 0.0f;
		posY = 0;
	}
}

void Paddle::MoveDown()
{
	if( posY < (480 - 128) )
	{
		if( (velocity >= 0.0f) && (velocity <= 6.0f) )
		{
			velocity += 2.0f;
		}
		else if( velocity < 0.0f )
		{
			velocity = 0.0f;
		}
		posY += velocity;
	}
	else
	{
		posY = 480 - 128;
	}
}
