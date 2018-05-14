#include "object.h"
#include "engine.h"

struct metor_type_data {
     GLfloat radius;
     GLuint image;
};

static const int number_of_metors = 20;
static metor_type_data metor_type;

class metor_instance: public object {
     GLfloat position[2];
     GLubyte colour[3];
public:
     void draw(void) {
          draw_bitmap(metor_type.image, position, metor_type.radius, colour);
     }

     void reset(void) {
          position[0] = GLfloat((rand() % 1000) - 300);
          position[1] = GLfloat((rand() % 800) - 300);
          colour[0] = 255 * 255 * 255;
          colour[1] = 255 * 255 * 255;
          colour[2] = 255 * 255 * 255;
     }

     void update(float time) {
          position[0] += GLfloat((rand() % 120) - 60) * time;
          position[1] += GLfloat((rand() % 130) - 60) * time;
     }
};

static metor_instance metor[number_of_metors];

class metor_array: public object_collection {
protected:
     void for_each_object(object_function & function) {
          for (int index = 0; index < number_of_metors; index++) {
               function.call(metor[index]);
          }
     }
};

object * load_metor_objects(const char * image, float radius)
{
     metor_type.image = load_bitmap(image);
     metor_type.radius = radius;

     static metor_array instance;
     return &instance;
}
