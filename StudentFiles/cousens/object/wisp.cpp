#include "object.h"
#include "engine.h"

struct wisp_type_data {
	GLfloat radius;
	GLuint image;
};

static const int number_of_wisps = 15;
static wisp_type_data wisp_type;

class wisp_instance: public object {
	GLfloat position[5];
	GLubyte colour[5];
public:
	void draw(void)
	{
		draw_bitmap(wisp_type.image, position, wisp_type.radius, colour);
	}

	void reset(void)
	{
		position[0] = GLfloat((rand() % 600) - 100);
		position[1] = GLfloat((rand() % 400) - 50);
		colour[0] = 255 * 255 * 255;
		colour[1] = 255 * 255 * 255;
		colour[2] = 255 * 255 * 255;
	}

	void update(float time)
	{
		position[0] += GLfloat((rand() % 101) - 100) * time;
		position[1] += GLfloat((rand() % 101) - 100) * time;
	}
};

static wisp_instance wisp[number_of_wisps];

class wisp_array: public object_collection {
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < number_of_wisps; index++) {
			function.call(wisp[index]);
		}
	}
};

object * load_wisp_objects(const char * image, float radius)
{
	wisp_type.image = load_bitmap(image);
	wisp_type.radius = radius;

	static wisp_array instance;
	return &instance;
}