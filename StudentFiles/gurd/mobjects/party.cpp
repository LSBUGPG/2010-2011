#include "object.h"
#include "engine.h"

struct party_type_data {
	GLfloat radius;
	GLuint image;
};

static const int number_of_party = 4;
static party_type_data party_type;

class party_instance: public object {
	GLfloat position[2];
	GLubyte colour[3];
public:
	void draw(void)
	{
		draw_bitmap(party_type.image, position, party_type.radius, colour);
	}

	void reset(void)
	{
		position[0] = GLfloat((rand() % 600) - 132);
		position[1] = GLfloat((rand() % 400) - 243);
		colour[0] = (rand() % 2) * 224;
		colour[1] = (rand() % 2) * 180;
		colour[2] = (rand() % 2) * 687;
	}

	void update(float time)
	{
		position[0] += GLfloat((rand() % 101) - 80) * time;
		position[1] += GLfloat((rand() % 101) - 89) * time;
	}
};

static party_instance party[number_of_party];

class party_array: public object_collection {
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < number_of_party; index++) {
			function.call(party[index]);
		}
	}
};

object * load_party_objects(const char * image, float radius)
{
	party_type.image = load_bitmap(image);
	party_type.radius = radius;

	static party_array instance;
	return &instance;
}
