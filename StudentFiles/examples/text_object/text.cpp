#include "text.h"

#include "object.h"
#include "engine.h"

static TTF_Font* font = 0;

class text : public object {
     int texture;
     float position[2];
     float size[2];
public:
     text(const char* message) {
          texture = load_text_line(font, message, size);
          position[0] = 0.0f;
          position[1] = 0.0f;
     }

     void reset() {
     }

     void update(float time) {
     }

     void draw() {
          draw_bitmap(texture, position, size);
     }
};

object& load_text_object()
{
     font = load_font("LiberationMono-Regular.ttf");

     static text message("Hello World");
     return message;
}
