#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct football_type_data {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * audio;
     GLubyte * colour;
};

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_footballs = 7;
static football_type_data football_type;

class football_instance: public object {
     GLfloat position[2];
     GLfloat velocity[2];

     GLfloat distance_to_bottom(void) {
          return (position[1] - football_type.radius) - base;
     }

public:
     void reset(void) {
          position[0] = GLfloat((rand() % 300) - 300);
          position[1] = GLfloat((rand() % 205) - 200);
          velocity[0] = 80.0f;
          velocity[1] = 40.0f;
     }

     void update(float time) {
          position[0] += velocity[0] * GLfloat(time);
          position[1] += velocity[1] * GLfloat(time);
          GLfloat distance = distance_to_bottom();
          if (distance < 0.0f) {
               position[1] = base + football_type.radius - distance;
               velocity[1] *= -1.0f;
          }

          velocity[1] -= GLfloat(9810.0f * time); // acceleration due to gravity in mm
     }

     void draw(void) {
          draw_bitmap(football_type.image, position, football_type.radius, football_type.colour);
     }
};

static football_instance football[number_of_footballs];

class football_array: public object_collection {
protected:
     void for_each_object(object_function & function) {
          for (int index = 0; index < number_of_footballs; index++) {
               function.call(football[index]);
          }
     }
};

object * load_football_objects(const char * image, const char * audio, float radius)
{
     static GLubyte white[3] = { 255, 255, 255 };

     football_type.image = load_bitmap(image);
     football_type.audio = load_audio(audio);
     football_type.radius = radius;
     football_type.colour = white;

     static football_array instance;
     return &instance;
}
