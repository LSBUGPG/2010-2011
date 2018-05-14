#include "player.h"
#include "object.h"
#include "engine.h"
#include "drifter.h"
#include "floor.h"

class floor_canyon: public object {
     int image;
     float position[2];
     float size[2];
     control current_direction;

public:
     floor_canyon(const char * image_name) {
          image = load_bitmap(image_name);
     }

     void reset(void) {
          position[0] = 64.0f;
          position[1] = 64.0f;
          size[0] = 410.0f;
          size[1] = 310.0f;
     }

     void update(float time) {
     }

     void draw(void) {
          draw_bitmap(image, position, size);
     }

};

static floor_canyon * floor = 0;

object & load_floor(void)
{
     static floor_canyon instance("canyon floor.bmp");
     floor = & instance;
     return instance;
}
