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

class gameover : public state {
     int line[3];
     float size[3][2];
     float timer;
public:
     gameover() {
          TTF_Font* font = load_font("LiberationMono-Regular.ttf", 50);
          if (font) {
               int colour[] = { 255, 255, 255 };
               line[0] = load_text_line(font, "GAME OVER ", size[0],colour);
               release_font(font);
          }
          font = load_font("LiberationMono-Regular.ttf", 30);
          if (font) {
               int colour[] = { 255, 255, 255 };
               line[1] = load_text_line(font, "YOU WIN!", size[1],colour);
               line[2] = load_text_line(font, "your adventure is at an end", size[2],colour);
               release_font(font);
          }
     }

     void enter() {
          reset();
     }

     void reset() {
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

     void draw() {
          float position[3][2] = {
               { 0.0f,  64.0f },
               { 0.0f, -32.0f },
               { 0.0f, -32.0f }
          };

          draw_bitmap(line[0], position[0], size[0]);
          if (game_won) {
               draw_bitmap(line[1], position[1], size[1]);
          } else {
               draw_bitmap(line[2], position[2], size[2]);
          }
     }

     void leave() {
     }
};

state* gameover_state()
{
     static state* singleton = 0;
     if (!singleton) {
          static gameover instance;
          singleton = &instance;
     }
     return singleton;
}
