#include "example.h"

#include "object.h"
#include "engine.h"

static struct {
     int image;
} type;

class example_object : public object {
     float position[2];
public:
     void update(float time) {
     }

     void draw() {
          float size[2] = { 32.0f, 32.0f };
          draw_bitmap(type.image, position, size);
     }

     void reset() {
          position[0] = 0.0f;
          position[1] = 0.0f;
     }
};

object& load_example_object()
{
     type.image = load_bitmap("dot.bmp");
     static example_object instance;
     return instance;
}
