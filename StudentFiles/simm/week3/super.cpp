#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct super_type_data {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * audio;
     GLubyte * colour;
};

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_supers = 2;
static super_type_data super_type;

class super_instance: public object {
     GLfloat position[2];
     GLfloat velocity[2];

     GLfloat distance_to_bottom(void) {
          return (position[1] - super_type.radius) - base;
     }

public:
     void reset(void) {
          position[0] = GLfloat((rand() % 500) - 300);
          position[1] = GLfloat((rand() % 400) - 100);
          velocity[0] = 90.0f;
          velocity[1] = 12.0f;
     }

     void update(float time) {
          position[0] += velocity[0] * GLfloat(time);
          position[1] += velocity[1] * GLfloat(time);
          GLfloat distance = distance_to_bottom();
          if (distance < 0.0f) {
               position[1] = base + super_type.radius - distance;
               velocity[1] *= -1.0f;
          }

          velocity[1] -= GLfloat(9810.0f * time); // acceleration due to gravity in mm
     }

     void draw(void) {
          draw_bitmap(super_type.image, position, super_type.radius, super_type.colour);
     }
};

static super_instance super[number_of_supers];

class super_array: public object_collection {
protected:
     void for_each_object(object_function & function) {
          for (int index = 0; index < number_of_supers; index++) {
               function.call(super[index]);
          }
     }
};

object * load_super_objects(const char * image, const char * audio, float radius)
{
     static GLubyte white[3] = { 255, 255, 255 };

     super_type.image = load_bitmap(image);
     super_type.audio = load_audio(audio);
     super_type.radius = radius;
     super_type.colour = white;

     static super_array instance;
     return &instance;
}
