#include <sdl.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <iostream>

//Check for collisions
bool checkCollision(float Lx, float Ly, float Lw, float Lh, float Rx, float Ry, float Rw, float Rh) 
{
	if (Ly+Lh < Ry) return false;
	else if (Ly > Ry+Rh) return false;
	else if (Lx+Lw < Rx) return false;
	else if (Lx > Rx+Rw) return false;
	
	return true; //If none of the above return false then there is a collision
}

//Cube struct holds information
struct Cube
{
	float x;
	float y;
	float width;
	float height;
	bool unbroken;
};

//So it begins
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING); //Load SDL

	SDL_WM_SetCaption("Jailbreak",NULL); //Window Header

	SDL_SetVideoMode(640,480,32,SDL_OPENGL); //Window size

	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	bool runGame = true; //Handles the main loop

	SDL_Event event; //Handles events

	//Variables for the bat
	float batX = 300;
	float batY = 370;
	float batWidth = 80;
	float batHeight = 20;
	bool left = false,right = false;  

	//Variables for the ball
	float ballX = 50; //Set ball X position
	float ballY = 350; //Set ball Y position
	float ballWH = 30; //Set W and H of ball

	//Variables for velocity
	float velocityX = 2; // X Velocity
	float velocityY = -2; // Y Velocity

	//Brick elements
	const static int CUBES = 54; //Amount of cubes

	Cube cubes[CUBES]; //Cube array

	for (int n = 0, x = 4, y = 10; n < CUBES; n++, x+=66) 
	{
		if (x > 560)
		{
			x = 4;
			y += 25;
		}
		cubes[n].x = x; //Set cube X position
		cubes[n].y = y; //Set cube Y position
		cubes[n].width = 60; //Width
		cubes[n].height = 20; //Height
		cubes[n].unbroken = true; //Cube begins not broken
	}

	//Main game loop
	while (runGame)
	{
		while (SDL_PollEvent(&event))
		{
			//If the window is closed then exit the game
			if (event.type == SDL_QUIT)
			{
				runGame = false;
			}

			//If the escape button is pushed then exit the game
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
			{
				runGame = false;
			}

			if (event.type == SDL_KEYDOWN) //Press key
			{
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					left = true;
				}
				
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					right = true;
				}
	       
			}

			else if (event.type == SDL_KEYUP) //Released key
			{
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					left = false;
				}
	      
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					right = false;
				}
			}
		}

		if (left == true)
		{
			batX -= 3; //Move left if true
		}

		if (right == true)
		{
			batX += 3; //Move right if true
		}

		if (batX < 0)
		{
			batX = 0;
		}

		if (batX+batWidth > 600)
		{
			batX = 600-batWidth;
		}

		ballX += velocityX; //Begin moving upwards

		for (int n = 0; n < CUBES; n++) //Collide with cubes
		{
			if (cubes[n].unbroken == true) //If it's unbroken
			{
				if (checkCollision(ballX,ballY,ballWH,ballWH,cubes[n].x,cubes[n].y,cubes[n].width, cubes[n].height) == true ) //Is there a collision
				{
					velocityX = -velocityX; //Change X velocity
					cubes[n].unbroken = false; //Cube is broken
					break; //Stop checking for a collision
				}
			}
		}

		ballY += velocityY; //Move ball on Y axis

		for (int n = 0; n < CUBES; n++) //Pass through the cubes
		{
			if (cubes[n].unbroken == true) //If the cube is unbroken
			{
				if (checkCollision(ballX,ballY,ballWH,ballWH,cubes[n].x,cubes[n].y,cubes[n].width,cubes[n].height) == true ) //Is there a collision
				{
					velocityY = -velocityY; //Change Y velocity
					cubes[n].unbroken = false; //Cube is broken
					break; //Stop checking for a collision
				}
			}
		}

		if (ballX < 0) //If the ball hits the left
		{
			velocityX = -velocityX; //Flip the X velocity
		}

		else if (ballX+ballWH>600)
		{
			velocityX = -velocityX;
		}
		
		if (ballY < 0)
		{
			velocityY = -velocityY;
		}

		else if (ballY+ballWH > 400) //If the ball hits the bottom
		{ 
			//Reset variables

			batX = 300; 
			batY = 370; 
			batWidth = 80;
			batHeight = 20;
	  
			left = false,right = false; 
	  
			
			ballX = 50;
			ballY = 350;
			ballWH = 30; 
	  
			velocityX = 2;
			velocityY = -2;

			for (int n = 0; n < CUBES; n++) //Set all cubes back to unbroken
			{
				cubes[n].unbroken = true;
			}
		}

		if (checkCollision(ballX,ballY,ballWH,ballWH,batX,batY,batWidth,batHeight) == true) //check for collision between bat and ball
		{
			velocityY = -velocityY; //if true change the Y velocity
		}
		
		//Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); //Begin rendering

		glOrtho(0,600,400,0,-1,1);

		glColor4ub(237,28,36,0); //Colour of the bat

		glBegin(GL_QUADS); //Render the bat
		glVertex2f(batX,batY);
		glVertex2f(batX+batWidth,batY);
		glVertex2f(batX+batWidth,batY+batHeight);
		glVertex2f(batX,batY+batHeight);
		glEnd();

		glColor4ub(181,230,29,255); //Colour of the ball

		glBegin(GL_QUADS); //Render the ball
		glVertex2f(ballX,ballY);
		glVertex2f(ballX+ballWH,ballY);
		glVertex2f(ballX+ballWH,ballY+ballWH);
		glVertex2f(ballX,ballY+ballWH);
		glEnd();

		glBegin(GL_QUADS); //Render the cubes

		for (int n = 0; n < CUBES; n++) //Spread throughout cubes
		{
			if (cubes[n].unbroken == true) //Check if it's unbroken
			{
				if (n%2 == 0) glColor4ub(0,162,232,255); //Colour even cubes
				else glColor4ub(163,73,164,255); //All others differently
	      
				glVertex2f(cubes[n].x,cubes[n].y);
				glVertex2f(cubes[n].x+cubes[n].width,cubes[n].y);
				glVertex2f(cubes[n].x+cubes[n].width,cubes[n].y+cubes[n].height);
				glVertex2f(cubes[n].x,cubes[n].y+cubes[n].height);

			}
		}
		
		glEnd();

		glPopMatrix();

		SDL_GL_SwapBuffers();
} 

SDL_Quit();

return 0;
}