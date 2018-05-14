#include "player.h"

#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "platform.h"

static struct {
	int image;
	float radius;

} type;

static bool jump = false;
static bool jumping = false;

static float platform_height = base;

void set_player_platform(float height)
{
	if (height > platform_height) {
		platform_height = height;
	}
}

class player_object: public object {
	float position[2];
	float velocity[2];
	bool jumping;


	float distance_to_bottom(void) {
		return (position[1] - type.radius) - platform_height;
	}


public:
	void update(float time) {
		if (jump && !jumping) {
			velocity[1] = 1700.0f; // speed upward in mm per second
			jump = false;
			jumping = true;
		}

		platform_height = base;
		hit_floor(position, type.radius);

		position[0] += velocity[0] * time;
		position[1] += velocity[1] * time;

		float distance = distance_to_bottom();
		if (distance < 0.0f) {
			position[1] = platform_height + type.radius;
			velocity[1] = 0.0f;
			jumping = false;
			if (platform_height == base) {
				reset_game();
			}
		} 

		velocity[1] -= 9310.0f * time; // acceleration due to gravity
	}         


	void draw(void) {
		float size[2] = { type.radius, type.radius };
		draw_bitmap(type.image, position, size);
	}

	void reset(void) {
		position[0] = -150.0f;
		position[1] = 100.0f;
		velocity[0] = 0.0f;
		velocity[1] = 0.0f;

	}
};

object & load_player_object(void)
{
	type.image = load_bitmap("Character.bmp");
	type.radius = 40.0f;
	static player_object instance;
	return instance;
}

void make_player_jump(void)
{
	jump = true;
}






