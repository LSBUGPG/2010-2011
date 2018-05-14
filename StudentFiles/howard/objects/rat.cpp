#include "object.h"
#include "engine.h"

struct rat_type_data {
     GLfloat radius;
     GLuint image;
};

static const int number_of_rats = 1;
static rat_type_data rat_type;

class rat_instance: public object {
     GLfloat position[2];
     GLubyte colour[3];
public:
     void draw(void) {
          draw_bitmap(rat_type.image, position, rat_type.radius, colour);
     }

     void reset(void) {
          position[0] = GLfloat((rand() % 400) - 300);
          position[1] = GLfloat((rand() % 300) - 200);
          colour[0] = 255 * 255 * 255; 
          colour[1] = 255 * 255 * 255;
          colour[2] = 255 * 255 * 255;
     }

     void update(float time) {
          position[0] += GLfloat((rand() % 201) - 150) * time;
          position[1] += GLfloat((rand() % 201) - 150) * time;

     }
};

static rat_instance rat[number_of_rats];

class rat_array: public object_collection {
protected:
     void for_each_object(object_function & function) {
          for (int index = 0; index < number_of_rats; index++) {
               function.call(rat[index]);
          }
     }
};

object * load_rat_objects(const char * image, float radius)
{
     rat_type.image = load_bitmap(image);
     rat_type.radius = radius;

     static rat_array instance;
     return &instance;
}
