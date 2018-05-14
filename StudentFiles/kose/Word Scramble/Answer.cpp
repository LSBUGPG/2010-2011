#include "Answer.h"

#include "object.h"
#include "engine.h"
#include "text.h"

#include <string.h>
#include <stdlib.h>

static TTF_Font * font = 0;

const int maximum_letters = 20;

class Answer: public object {
     int texture;
     float position[2];
     float size[2];
     char buffer[maximum_letters + 1];
     bool created;
public:
     Answer(void): created(false) {
     }

     void reset(void) {
          buffer[0] = 0;
          position[0] = 100.0f;
          position[1] = 0.0f;
          if (created) {
              (texture);
               created = false;
          }
     }

     void update(float time) {
     }

     void draw(void) {
          if (created) {
               draw_bitmap(texture, position, size);
          }
     }

     void show_key(int key) {
          if (created) {
               delete_bitmap(texture);
          }
          if (strlen(buffer) < maximum_letters) {
               char new_letter[] = { key, 0 };
               strcat_s(buffer, sizeof(buffer), new_letter);
          }
          texture = load_text_line(font, buffer, size);
          created = true;
          test_guess(buffer);
     }
};

static void swap(char & in, char & out)
{
     char temporary = in;
     in = out;
     out = temporary;
}

static Answer message;

object & load_Answer_object(TTF_Font * input_font)
{
     font = input_font;

     return message;
}

void notify_Answer(int key)
{
     message.show_key(key);
}

void reset_answer(void)
{
     message.reset();
}
