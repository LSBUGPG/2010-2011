#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct footy_type_data {
	GLfloat radius;
	GLuint image;
	Mix_Chunk * audio;
	GLubyte * colour;
};

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_footys = 15;
static footy_type_data footy_type;

class footy_instance: public object {                // class of ball_instance, based on public version of "object"
	GLfloat position[2];
	GLfloat velocity[2];            //postion of velocity 

	GLfloat distance_to_bottom(void)
	{
		return (position[1] - footy_type.radius) - base;
	}

public:
	void reset(void) 
	{
		position[0] = GLfloat((rand() % 600) - 300);
		position[1] = GLfloat((rand() % 400) - 200);
		velocity[0] = 1.0f;
		velocity[1] = 5.0f;
	}

	void update(float time)
	{
		position[0] += velocity[0] * GLfloat(time);
		position[1] += velocity[1] * GLfloat(time);
		GLfloat distance = distance_to_bottom();
		if (distance < 0.0f) {                            //it knows inturnally what type it is
			position[1] = base + footy_type.radius - distance;
			velocity[1] *= -1.0f;
		}

		velocity[1] -= GLfloat(9810.0f * time); // acceleration due to gravity in mm
	}

	void draw(void) 
	{
		draw_bitmap(footy_type.image, position, footy_type.radius, footy_type.colour);
	}
};                                    // provides the three fuctions in the object.h, must get names right

static footy_instance footy[number_of_footys];

class footy_array: public object_collection {
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < number_of_footys; index++) {     //goes through each ball
			function.call(footy[index]);								// calls ball function on each ball
		}
	}                                                     
};

object * load_footy_objects(const char * image, float radius)
{
	static GLubyte white[3] = { 255, 255, 255 };

	footy_type.image = load_bitmap(image);
	footy_type.audio = NULL;//load_audio(audio);
	footy_type.radius = radius;
	footy_type.colour = white;

	static footy_array instance;
	return &instance;
}
// Ensure the images have a white gamma color, so it can be seen when it's running