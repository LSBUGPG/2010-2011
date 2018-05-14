#include "gameover.h"
#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

static bool game_won = false;

void notify_win(bool win)
{
     game_won = win;
}

class gameover: public state {
     int line[3];
     float size[3][2];
     float timer;
public:
     gameover(void) {
          TTF_Font * font = load_font("LiberationMono-Italic.ttf", 32);
          if (font) {
               line[0] = load_text_line(font, "GAME OVER", size[0]);
               release_font(font);
          }
          font = load_font("LiberationMono-Italic.ttf", 20);
          if (font) {
               line[1] = load_text_line(font, "YOU WON!", size[1]);
               line[2] = load_text_line(font, "YOU LOST!", size[2]);
               release_font(font);
          }
     }

     void enter(void) {
          reset();
     }

     void reset(void) {
          timer = 5.0f;
          skip = false;
     }

     void update(float time) {
          if (skip) {
               timer = 0.0f;
          }
          if (timer > time) {
               timer -= time;
          } else {
               change_state(credits_state());
          }
     }

     void draw(void) {
          float position[3][2] = {
               { 0.0f,  64.0f },
               { 0.0f, -32.0f },
               { 0.0f, -32.0f }
          };

          draw_bitmap(line[0], position[0], size[0], radius[0.0f]);
          if (game_won) {
               draw_bitmap(line[1], position[1], size[1], radius[0.0f]);
          } else {
               draw_bitmap(line[2], position[2], size[2], radius[0.0f]);
          }
     }

     void leave(void) {
     }
};

state * gameover_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static gameover instance;
          singleton = &instance;
     }
     return singleton;
}
