#include "engine.h"
#include "background.h"
#include "measurements.h"

#include "object.h"


class background: public object {
     int texture;
     float position;
     float velocity;
     float radius;
     enum {move} stage;
public:
     background(const char * image) {
          texture = load_bitmap(image);
     }

     void reset(void) {
     }

     void update(float time) {

     }

     void draw(void) {
          float position[] = { 0.0f, 0.0f };
          float size[] = { half_width, half_height };
          draw_bitmap(texture, position, size);
     }
};

object & load_background_object(const char * image)
{
     static background instance(image);
     return instance;
}
