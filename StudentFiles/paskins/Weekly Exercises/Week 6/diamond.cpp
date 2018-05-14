#include "object.h"
#include "engine.h"

struct brownian_type_data {
     GLfloat radius;
     GLuint image;
};

static const int number_of_diamonds = 5;
static brownian_type_data diamond_type;

class brownian_instance: public object {
     GLfloat position[2];
     GLubyte colour[3];
public:
     void draw(void) {
          draw_bitmap(diamond_type.image, position, diamond_type.radius, colour);
     }

     void reset(void) {
          position[0] = GLfloat((rand() % 600) - 300);
          position[1] = GLfloat((rand() % 400) - 200);
          colour[0] = 255;
          colour[1] = 255;
          colour[2] = 255;
     }

     void update(float time) {
          position[0] += 5 * time;
     }
};

static brownian_instance diamond[number_of_diamonds];

class diamond_array: public object_collection {
protected:
     void for_each_object(object_function & function) {
          for (int index = 0; index < number_of_diamonds; index++) {
               function.call(diamond[index]);
          }
     }
};

object * load_diamond_objects(const char * image, float radius)
{
     diamond_type.image = load_bitmap(image);
     diamond_type.radius = radius;

     static diamond_array instance;
     return &instance;
}
