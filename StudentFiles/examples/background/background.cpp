#include "background.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"

class background : public object {
     int texture;
public:
     background(const char* image) {
          texture = load_bitmap(image);
     }

     void reset() {
     }

     void update(float time) {
     }

     void draw() {
          float position[] = { 0.0f, 0.0f };
          float size[] = { half_width, half_height };
          draw_bitmap(texture, position, size);
     }
};

object& load_background_object(const char* image)
{
     static background instance(image);
     return instance;
}
