#include "script.h"

#include "text.h"
#include "object.h"
#include "graphics.h"
#include "state.h"

static const char * lines[] = {
     "you awaken in a small labrinth ",
     "and are attacked by a mutant",
     "you try to fight back",
     "but sadly its futile",
     "it seems this is the end"
};

const char * pics[] = {
     "lizard.bmp",
     "monster.bmp",
     0,
     0,
     0,
};


static bool next = false;

class script: public object {
     int current_line;

public:
     script(void): current_line(0) {
     }

     void reset(void) {
          current_line = 0;
     }

     void update(float time) {
          if (next) {
               const int number_of_lines = sizeof(lines) / sizeof(lines[0]);
               if (current_line >= number_of_lines) {
                    change_state(gameover_state());
                    current_line = 0;
               }

               change_text(lines[current_line]);
               if (pics[current_line]) {
                    change_image(pics[current_line]);
               }
               current_line++;
               next = false;
          }
     }

     void draw(void) {
     }
};

object & load_script(void)
{
     static script instance;
     return instance;
}

void next_line(void)
{
     next = true;
}

