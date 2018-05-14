#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct cat_type_data {
	GLfloat radius;
	GLuint image;
	GLubyte * colour;
};

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_cats = 10;
static cat_type_data cat_type;

class cat_instance: public object {
	GLfloat position[2];
	GLfloat velocity[2];

	GLfloat distance_to_bottom(void)
	{
		return (position[1] - cat_type.radius) - base;
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
			position[1] = base + cat_type.radius - distance;
			velocity[1] *= -1.0f;
		}

		velocity[1] -= GLfloat(9810.0f * time); // acceleration due to gravity in mm
	}

	void draw(void) 
	{
		draw_bitmap(cat_type.image, position, cat_type.radius, cat_type.colour);
	}
};

static cat_instance cat[number_of_cats];

class cat_array: public object_collection {
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < number_of_cats; index++) {
			function.call(cat[index]);
		}
	}
};

object * load_cat_objects(const char * image, float radius)
{
	static GLubyte white[3] = { 255, 255, 255 };

	cat_type.image = load_bitmap(image);
	cat_type.radius = radius;
	cat_type.colour = white;

	static cat_array instance;
	return &instance;
}
