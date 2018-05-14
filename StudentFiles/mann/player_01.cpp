#include "player.h"

#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>
#include <SDL_keyboard.h>
#include <math.h>

#include "engine.h"
#include "measurements.h"
#include "object.h"

struct ship_type {
	GLfloat radius;
	GLuint image;
};
struct ship_instance {
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
		
		break;
	case SDLK_f:
	
		break;
	case SDLK_r:

		break;
	}
}


static ship_type type;

static const float maximum_acceleration = 250.0f; // units per second 
static const float maximum_speed = 200.0f; // units per second
static const float maximum_velocity = 250.0f; //units per second
static const float drag = 25.0f; // units per second

void set_start(ship_instance & instance)
{
	instance.position[0] = 0.0f;
	instance.position[1] = 0.0f;
	instance.velocity[0] = 1000.0f;
	instance.velocity[1] = 0.0f;
}

const GLfloat base = GLfloat(-screen_height / 2);

GLfloat distance_to_bottom(const ship_type & type, const ship_instance & instance)
{
	return (instance.position[1] - type.radius) - base;
}

void update(const ship_type & type, ship_instance & instance, float time)
{
	instance.position[0] += instance.velocity[0] * time;
	instance.position[1] += instance.velocity[1] * time;

	GLfloat distance = distance_to_bottom(type, instance);
	if (distance < 00.0f) {
		instance.position[1] = base + type.radius - distance;
		instance.position[0] = base +type.radius - distance;
		instance.velocity[1] *= -1.0f;
	}

	instance.velocity[1] -= 9810.0f * time; // acceleration due to gravity in mm
}
