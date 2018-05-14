#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct shuriken_type_data {
	GLfloat radius;
	GLuint image;
	GLubyte * colour;
};

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_shurikens = 10;
static shuriken_type_data shuriken_type;

class shuriken_instance: public object {
	GLfloat position[2];
	GLfloat velocity[2];

	GLfloat distance_to_bottom(void)
	{
		return (position[1] - shuriken_type.radius) - base;
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
			position[1] = base + shuriken_type.radius - distance;
			velocity[1] *= -1.0f;
		}

		velocity[1] -= GLfloat(40.0f * time); // acceleration due to gravity in mm
	}

	void draw(void) 
	{
		draw_bitmap(shuriken_type.image, position, shuriken_type.radius, shuriken_type.colour);
	}
};

static shuriken_instance shuriken[number_of_shurikens];

class shuriken_array: public object_collection {
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < number_of_shurikens; index++) {
			function.call(shuriken[index]);
		}
	}
};

object * load_shuriken_objects(const char * image, float radius)
{
	static GLubyte white[3] = { 255, 255, 255 };

	shuriken_type.image = load_bitmap(image);
	shuriken_type.radius = radius;
	shuriken_type.colour = white;

	static shuriken_array instance;
	return &instance;
}