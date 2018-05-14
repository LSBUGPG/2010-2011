#include "player.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <math.h>

#include "shot.h"
#include "engine.h"
#include "measurements.h"
#include "object.h"

struct player_type {
	GLfloat radius;
	GLuint image;
};

static player_type type;

class player_instance: public object {
	float position[2];
	float velocity[2];
	float acceleration;
	float heading;
	float age;
	bool trigger;
	float current_speed() {
		return sqrtf(velocity[0] * velocity[0] + velocity[1] * velocity[1]);
	}
public:
	player_instance() {
	}
	void reset(void) {
		position[0] = 0.0f;
		position[1] = 0.0f;
		velocity[0] = 0.0f;
		velocity[1] = 0.0f;
		acceleration = 0.0f;
		heading = 0.0f;
		age = 0.0f;
		trigger = false;
	}
	void update(float time) {
		age += time;
		position[0] += velocity[0] * time;
		position[1] += velocity[1] * time;
		position[2] += velocity[2] * time;

		float speed = current_speed();
		if (speed > 0.0f) {
			velocity[0] *= acceleration / speed;
			velocity[1] *= acceleration / speed;
		}
		if (position[0] < screen_left + type.radius) {
			position[0] = screen_left + type.radius;
			velocity[0] = 0.0f;
		}

		if (position[0] > screen_right - type.radius) {
			position[0] = screen_right - type.radius;
			velocity[0] = 0.0f;
		}

		if (position[1] > screen_top - type.radius) {
			position[1] = screen_top - type.radius;
			velocity[1] = 0.0f;

		}

		if (position[1] < screen_bottom + type.radius) {
			position[1] = screen_bottom + type.radius;
			velocity[1] = 0.0f;
		}

		if (trigger) {
			trigger = false;
            fire_shot(position, heading);
        }
	}
	void draw(void) {
		draw_bitmap(type.image, position, type.radius, 0.0f);
	}
	void apply_control(control action, keystate state) {
		switch (state) {
		case press:
			switch (action) {
			case thrust:
				acceleration = velocity[1] = 200.0f;
				break;
			case left:
				acceleration = -200.0f;
				break;
			case right:
				acceleration = 250.0f;
				break;
			case down:
				
				break;
			case fire:
				trigger = true;
				break;
			default:
				break;
			}
			break;
		case release:
			switch (action) {
			case thrust:
				acceleration = 0.0f;
				break;
			case left:
				acceleration = 0.0f;
				break;
			case right:
				acceleration = 0.0f;
				break;
			case down:
				acceleration = 0.0f;
				break;
			case fire:
				trigger = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	void spawn(void) {
		reset();
		age = 0.0f;
	}
	void kill(void) {
	}
};

static player_instance instance;

object & load_player(const char * image, float radius)
{
	type.image = load_bitmap(image);
	type.radius = radius;
	return instance;
}

void control_ship(control action, keystate state)
{
	instance.apply_control(action, state);
}

void spawn_player(void)
{
	instance.spawn();
}

void kill_player(void)
{
	instance.kill();
}
