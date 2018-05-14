#include "engine.h"

#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>

bool pause = true;
bool step = false;
bool reset = true;

struct ball_definition {
	const char * image;
	const char * audio;
	GLfloat radius; // units in mm
};

struct ball_type {
	GLfloat radius;
	GLuint image;
	Mix_Chunk * audio;
};

struct ball_instance {
	GLfloat position[2];
	GLfloat velocity[2];
};

void handle_key(SDL_keysym & key)
{
    switch (key.sym) {
	case SDLK_ESCAPE:
        quit(0);
		break;
	case SDLK_p:
		pause = !pause;
		break;
	case SDLK_f:
		step = true;
		break;
	case SDLK_r:
		reset = true;
		break;
	}
}

void process_events(void)
{
    SDL_Event an_event;

    while (SDL_PollEvent(&an_event)) {
        switch (an_event.type) {
		case SDL_KEYUP:
            handle_key(an_event.key.keysym);
			break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

void draw(const ball_type & type, const ball_instance & instance)
{
	draw_bitmap(type.image, instance.position, type.radius);
}

void set_start(ball_instance & instance)
{
	instance.position[0] = -150 + rand() % 500; //putting the ball on X axis between -150 and 500
	instance.position[1] = -0 + rand() % 200;   //putting the ball on Y axis between 0 and 200
	instance.velocity[0] = -1500.0f;     
	instance.velocity[1] = -0.0f;
}

const int screen_height = 480;
const int screen_width = 640; 
const GLfloat base = GLfloat(-screen_height / 2);
const GLfloat leftside = GLfloat(-screen_width / 2); 
const GLfloat rightside = GLfloat(+screen_width / 2);

GLfloat distance_to_bottom(const ball_type & type, const ball_instance & instance)
{
	return (instance.position[1] - type.radius) - base;
}

GLfloat distance_to_leftside(const ball_type & type, const ball_instance & instance) //defining the left side of screen
{
	return (instance.position[0] - type.radius) - leftside;
}

GLfloat distance_to_rightside(const ball_type & type, const ball_instance & instance) //defining the right side of screen
{
	return (instance.position[0] - type.radius) + rightside;
}

void update(const ball_type & type, ball_instance & instance, float time)
{
	instance.position[0] += instance.velocity[0] * time;
	instance.position[1] += instance.velocity[1] * time;

	GLfloat distance = distance_to_bottom(type, instance);
	if (distance < 0.0f) {
		instance.position[1] = base + type.radius - distance;
		instance.velocity[1] *= -1.0f;
	}

	else if	(distance > 580.0f) {         
		instance.position[0] = base + type.radius - distance;   
		instance.velocity[1] *= 1.0f;
	} 
	
			;
	instance.velocity[1] -= 9310.0f * time; 

	
	GLfloat left_distance = distance_to_leftside(type, instance); 
	if (left_distance < 0.0f) {
		instance.velocity[0] *= -1.0f; //bouncing the ball off the left side of the screen
	}


	GLfloat right_distance = distance_to_rightside(type, instance); 
	if (right_distance > 580.0f) { 
		instance.velocity[0] *= -1.0f; //bouncing the ball off the right side of the screen
	}
}

int main(int argc, char * argv[])
{
	initialise_engine();

	ball_definition definition = { "ball.bmp", "bounce.wav", 40.0f };
	ball_type type;
	ball_instance instance;
	
	type.image = load_bitmap(definition.image);
	type.audio = load_audio(definition.audio);
	type.radius = definition.radius;

	while (true) {
		const float time = 1.0f / 60.0f;

		process_events();
		if (reset) {
			set_start(instance);
			reset = false;
		} else if (!pause || step) {
			update(type, instance, time);
			step = false;
		}
		start_render();
		draw(type, instance);
		end_render();
    }

	return 0;
}
