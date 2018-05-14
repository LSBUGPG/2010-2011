#include "text.h"
#include "graphics.h"
#include "object.h"
#include "engine.h"
#include "background.h"

class image: public object {
     int texture;
     bool created;

public:
     image(const char * file_name) {
          set_image(file_name);
     }

     void reset(void) {
     }

     void update(float time) {
     }

     void draw(void) {
          float position[] = { 0.0f, 0.0f };
          float size[] = { 100.0f, 100.0f };
          draw_bitmap(texture, position, size);
     }

     void set_image(const char * image) {
          if (created) {
               delete_bitmap(texture);
          }
          texture = load_bitmap(image);
          created = true;
     }
};

static image * single_instance = 0;

object & load_image_object(void)
{
     static image instance("lizard.bmp");
     single_instance = &instance;
     return instance;
}

void change_image(const char * image)
{
     if (single_instance) {
          single_instance->set_image(image);
     }
}