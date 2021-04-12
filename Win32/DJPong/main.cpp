/*
 *  main.cpp
 *  DJPong
 *
 *  Created by Daniel Jung on 6/13/08.
 *  Copyright 2008 Dimensional Eye. All rights reserved.
 *
 */

#include "Global.h"

bool bDone = false;

SDL_Surface *screen;
SDL_Event event;
int startTime;

SDL_Surface *gameBackground;
Ball myBall;
Paddle player1;
Paddle player2;
int player1Score;
int player2Score;
SDL_Surface *playerOneScore;
SDL_Surface *playerTwoScore;

// Sound Effect(s)
Mix_Chunk *paddlesound;

TTF_Font *font;
SDL_Color player1Color = { 255, 0, 0 };
SDL_Color player2Color = { 0, 0, 255 };

SDL_Surface *loadImage( string filename )
{
	// This is a temporary storage for loaded image
	SDL_Surface *loadedImage = NULL;
	
	// This is the optimized image that will be returned
	SDL_Surface *optimizedImage = NULL;
	
	// Load the image
	loadedImage = IMG_Load( filename.c_str() );
	
	// If there is nothing wrong so far
	if( loadedImage != NULL )
	{
		// Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		// Free the old image
		SDL_FreeSurface( loadedImage );
	}
	
	// Return the optimized image
	return optimizedImage;
}

// Load image with color key
SDL_Surface *loadImage( string filename, Uint8 r, Uint8 g, Uint8 b )
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;
	
	loadedImage = IMG_Load( filename.c_str() );
	
	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
		
		// If the image was optimized just fine
		if( optimizedImage != NULL )
		{
			// Map the color key
			Uint32 colorKey = SDL_MapRGB( optimizedImage->format, r, g, b );
			// Set all pixels of color R, G, B to be transparent
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorKey );
		}
	}
	
	return optimizedImage;
}

// This function applies the image to the screen
void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	// Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	
	// Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	
	// Blit the surface
	SDL_BlitSurface( source, NULL, destination, &offset );
}

void CheckKeyInput()
{
	// Get the keystates
	Uint8 *keystates = SDL_GetKeyState( NULL );
	
	// If up key is pressed
	if( keystates[SDLK_UP] )
	{
		// Go up
		player1.MoveUp();
	}
	if( keystates[SDLK_DOWN] )
	{
		// Go down
		player1.MoveDown();
	}
}

void CheckCollision()
{
	if( myBall.getPosX() < 0 )
	{
		// if the ball hits the left side of the play area
		player2Score++;
		UpdateScore();
		Restart();
		//printf( "Player Two score: %i\n", player2Score );
	}
	else if( myBall.getPosX() > (640 - myBall.getWidth()) )
	{
		// if the ball hits the right side of the play area
		player1Score++;
		Restart();
		UpdateScore();
		//printf( "Player One score: %i\n", player1Score );
	}
	else if( myBall.getPosY() < 0 )
	{
		// if the ball hits the top side of the play area
		Mix_PlayChannel( -1, paddlesound, 0 );
		myBall.setPosY( 0 );
		myBall.setVelY( -myBall.getVelY() );
	}
	else if( myBall.getPosY() > (480 - myBall.getHeight()) )
	{
		// if the ball hits the bottom side of the play area
		Mix_PlayChannel( -1, paddlesound, 0 );
		myBall.setPosY( 480 - myBall.getHeight() );
		myBall.setVelY( -myBall.getVelY() );
	}
	else if( (myBall.getPosX() >= (player1.getPosX() - 16)) && (myBall.getPosX() <= (player1.getPosX() + 16)) && (myBall.getPosY() >= (player1.getPosY() - 16)) && (myBall.getPosY() <= (player1.getPosY() + 128)) )
	{
		// if the ball hits the player 1's paddle
		Mix_PlayChannel( -1, paddlesound, 0 );
		myBall.setVelX( -myBall.getVelX() + 2 );
		myBall.setPosX( myBall.getPosX() + myBall.getVelX() + 2.0f );
		//myBall.setPosX( myBall.getPosX() + 2 );
		//myBall.setPosY( myBall.getPosY() + myBall.getVelY() );
		myBall.setSpeed( myBall.getSpeed() + 4.0f );
		//myBall.setVelY( player1.getVelocity() * myBall.getSpeed() );
		myBall.setVelY( myBall.getSpeed() * 2 );
	}
	else if( (myBall.getPosX() >= (player2.getPosX() - 16)) && (myBall.getPosX() <= (player2.getPosX() + 16)) && (myBall.getPosY() >= (player2.getPosY() - 16)) && (myBall.getPosY() <= (player2.getPosY() + 128)) )
	{
		// if the ball hits the player 2's paddle
		Mix_PlayChannel( -1, paddlesound, 0 );
		myBall.setVelX( -myBall.getVelX() - 2 );
		//myBall.setPosX( myBall.getPosX() + myBall.getVelX() );
		myBall.setPosX( myBall.getPosX() - 2 - 2 );
		//myBall.setPosY( myBall.getPosY() + myBall.getVelY() );
		myBall.setSpeed( myBall.getSpeed() + 4.0f );
		//myBall.setVelY( player2.getVelocity() * myBall.getSpeed() );
		myBall.setVelY( myBall.getSpeed() * 2 );
	}
	else
	{
		myBall.setPosX( myBall.getPosX() + myBall.getVelX() );
		myBall.setPosY( myBall.getPosY() + myBall.getVelY() );
	}
}

void Render()
{
	applySurface(0, 0, gameBackground, screen);
	applySurface((int)player1.getPosX(), (int)player1.getPosY(), player1.getImage(), screen);
	applySurface((int)player2.getPosX(), (int)player2.getPosY(), player2.getImage(), screen);
	applySurface((int)myBall.getPosX(), (int)myBall.getPosY(), myBall.getImage(), screen);
	applySurface(160, 0, playerOneScore, screen);
	applySurface(480, 0, playerTwoScore, screen);
}

void Logic()
{
	if( (player2.getPosY() + 64) < (myBall.getPosY() + 8) )
	{
		player2.MoveDown();
	}
	else if( (player2.getPosY() + 64) > (myBall.getPosY() + 8) )
	{
		player2.MoveUp();
	}
}

void UpdateScore()
{
	char score1[100];
	char score2[100];
	sprintf( score1, "%d", player1Score );
	sprintf( score2, "%d", player2Score );
	
	playerOneScore = TTF_RenderText_Solid( font, score1, player1Color );
	playerTwoScore = TTF_RenderText_Solid( font, score2, player2Color );
}

void Restart()
{
	myBall.setPosX( 320.0f );
	myBall.setPosY( 240.0f );
	player1.setPosY( 176.0f );
	player2.setPosY( 176.0f );
	//myBall.setVelX( 4.0f );
	float tempVelX = -4.0f + (rand() % 8);
	printf("tempVelX = %f\n", tempVelX);
	myBall.setVelX(tempVelX);
	//myBall.setVelY( -5.3f );
	float tempVelY = -6.0f + (rand() % 12);
	printf("tempVelY = %f\n", tempVelY);
	myBall.setVelY(tempVelY);
	myBall.setSpeed( 1.0f );
}

int main(int argc, char *argv[])
{	
	/* Initialize the SDL library */
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	/* Set 640x480 video mode */
	screen=SDL_SetVideoMode(640,480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set 640x480x32 video mode: \n",
				SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	// Initialize SDL_ttf
	if( TTF_Init() < 0 )
	{
		fprintf(stderr, "Couldn't initialize SDL_ttf: %s\n",
				SDL_GetError());
		SDL_Quit();
		exit(3);
	}
	
	// Initialize SDL_mixer
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0 )
	{
		fprintf(stderr, "Couldn't initialize SDL_mixer: %s\n",
				SDL_GetError());
		SDL_Quit();
		exit(4);
	}
	
	SDL_WM_SetCaption( "Daniel Jung's Pong", NULL );
	
	//startTime = SDL_GetTicks();
	gameBackground = loadImage( "data/PongBack.png" );
	
	// Open the font
	font = TTF_OpenFont( "data/Tahoma.ttf", 28 );
	
	if( font == NULL )
	{
		fprintf(stderr, "Couldn't load the font: %s\n",
				SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	
	// Load the paddle sound
	paddlesound = Mix_LoadWAV( "data/paddle.wav" );
	
	myBall.setImage();
	player1.setImage();
	player1.setPosX( 8.0f );
	player1.setPosY( 176.0f );
	player2.setImage();
	player2.setPosX( 616.0f );
	player2.setPosY( 176.0f );
	player1Score = 0;
	player2Score = 0;
	
	char score1[100];
	char score2[100];
	sprintf( score1, "%d", player1Score );
	sprintf( score2, "%d", player2Score );
	
	playerOneScore = TTF_RenderText_Solid( font, score1, player1Color );
	playerTwoScore = TTF_RenderText_Solid( font, score2, player2Color );
	
	while ( !bDone )
	{
		// Start the timer for fps
		startTime = SDL_GetTicks();
		/* Check for events */
		while ( SDL_PollEvent(&event) )
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE)
						bDone = true;
					break;
				case SDL_QUIT:
					bDone = true;
					break;
				default:
					break;
			}
		}
		
		CheckKeyInput();
		CheckCollision();
		Logic();
		Render();
		
		// Update the screen
		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}
		
		// Frame rate
		if( (SDL_GetTicks() - startTime) < 1000 / 60 )
		{
			// Sleep the remaining frame time
			SDL_Delay( (1000 / 60) - (SDL_GetTicks() - startTime) );
		}
	}
	
	SDL_FreeSurface(gameBackground);
	SDL_FreeSurface(playerOneScore);
	SDL_FreeSurface(playerTwoScore);
	
	Mix_FreeChunk(paddlesound);
	
	TTF_CloseFont(font);
	
	Mix_CloseAudio();
	
	TTF_Quit();
	
	/* Clean up the SDL library */
	SDL_Quit();
	return(0);
}
