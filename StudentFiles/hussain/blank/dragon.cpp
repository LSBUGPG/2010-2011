#include "example.h"

#include "object.h"
#include "engine.h"

static struct {
     int image;
} type;

class example_object: public object {
     float position[2];
public:
     void update(float time) {
     }

     void draw(void) {
          float size[2] = { 16.0f, 32.0f };
          draw_bitmap(type.image, position, size);
     }

     void reset(void) {
          position[0] = 0.0f;
          position[1] = 0.0f;
     }
};

object & load_example_object(void)
{
     type.image = load_bitmap("dragon.bmp");
     static example_object instance;
     return instance;
}
