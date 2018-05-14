#include "background.h"
#include "measurements.h"

#include "object.h"
#include "engine.h" 

class background_object : public object {
     int texture;
public:
     background_object (const char* background, int texture, float size) {
          texture = load_bitmap("background.bmp");
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


 

