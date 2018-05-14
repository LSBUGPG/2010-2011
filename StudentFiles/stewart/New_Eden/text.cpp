#include "text.h"
#include "graphics.h"
#include "object.h"
#include "engine.h"
#include "script.h"

static TTF_Font * font = 0;

class text: public object {
     int texture;
     float position[2];
     float size[2];
     bool created;
public:
     text(const char * message): created(false) {
          set_text(message);
     }

     void reset(void) {
     }

     void update(float time) {
     }

     void draw(void) {
          float size[] = { 140.0f, 25.0f };
          float position[] = { -105.f, -145.0f };
          draw_bitmap(texture, position, size);
     }

     void set_text(const char * message) {
          if (created) {
               delete_bitmap(texture);
          }
          if (font) {
               int colour[] = { 0, 0, 0 };
               texture = load_text_line(font, message, size,colour);
               created = true;
          }
     }
};

static text * single_instance = 0;

object & load_text_object(void)
{
     font = load_font("LiberationMono-Italic.ttf", 90);

     static text message("");
     next_line();
     single_instance = &message;
     return message;
};

void change_text(const char * message) // general change text function
{
     if (single_instance) {
          single_instance->set_text(message);
     }
}