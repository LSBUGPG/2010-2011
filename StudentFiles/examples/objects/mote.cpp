#include "object.h"
#include "engine.h"

struct brownian_type_data {
     GLfloat radius;
     GLuint image;
};

static const int number_of_motes = 20;
static brownian_type_data mote_type;

class brownian_instance : public object {
     GLfloat position[2];
     GLubyte colour[3];
public:
     void draw() {
          draw_bitmap(mote_type.image, position, mote_type.radius, colour);
     }

     void reset() {
          position[0] = GLfloat((rand() % 600) - 300);
          position[1] = GLfloat((rand() % 400) - 200);
          colour[0] = (rand() % 2)* 255;
          colour[1] = (rand() % 2)* 255;
          colour[2] = (rand() % 2)* 255;
     }

     void update(float time) {
          position[0] += GLfloat((rand() % 101) - 50)* time;
          position[1] += GLfloat((rand() % 101) - 50)* time;
     }
};

static brownian_instance mote[number_of_motes];

class mote_array : public object_collection {
protected:
     void for_each_object(object_function& function) {
          for (int index = 0; index < number_of_motes; index++) {
               function.call(mote[index]);
          }
     }
};

object* load_mote_objects(const char* image, float radius)
{
     mote_type.image = load_bitmap(image);
     mote_type.radius = radius;

     static mote_array instance;
     return &instance;
}
