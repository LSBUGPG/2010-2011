#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct nike_trainers_type_data {
	GLfloat radius;
	GLuint image;
	GLubyte * colour;
};

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_nike_trainers = 10;
static nike_trainers_type_data nike_trainers_type;

class nike_trainers_instance: public object {
	GLfloat position[2];
	GLfloat velocity[2];

	GLfloat distance_to_bottom(void)
	{
		return (position[1] - nike_trainers_type.radius) - base;
	}

public:
	void reset(void) 
	{
		position[0] = GLfloat((rand() % 600) - 300);
		position[1] = GLfloat((rand() % 400) - 200);
		velocity[0] = 0.0f;
		velocity[1] = 0.0f;
	}

	void update(float time)
	{
		position[0] += velocity[0] * GLfloat(time);
		position[1] += velocity[1] * GLfloat(time);
		GLfloat distance = distance_to_bottom();
		if (distance < 0.0f) {
			position[1] = base + nike_trainers_type.radius - distance;
			velocity[1] *= -1.0f;
		}

		velocity[1] -= GLfloat(9810.0f * time); // acceleration due to gravity in mm
	}

	void draw(void) 
	{
		draw_bitmap(nike_trainers_type.image, position, nike_trainers_type.radius, nike_trainers_type.colour);
	}
};

static nike_trainers_instance nike_trainers[number_of_nike_trainers];

class nike_trainers_array: public object_collection {
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < number_of_nike_trainers; index++) {
			function.call(nike_trainers[index]);
		}
	}
};

object * load_nike_trainers_objects(const char * image, float radius)
{
	static GLubyte white[3] = { 255, 255, 255 };

	nike_trainers_type.image = load_bitmap(image);;
	nike_trainers_type.radius = radius;
	nike_trainers_type.colour = white;

	static nike_trainers_array instance;
	return &instance;
}
