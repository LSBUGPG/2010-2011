#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"
#include <math.h>

class title : public state {
     int splash;
     int prompt;
     float prompt_size[2];
     float timer;
public:
     title() {
          splash = load_bitmap("title.png");
          TTF_Font* font = load_font("LiberationMono-Regular.ttf", 40);
          if (font) {
               int colour[] = { 255, 255, 255 };
               prompt = load_text_line(font, "Press space to start!", prompt_size, colour);
               release_font(font);
          }
     }

     void enter() {
          reset();
     }

     void reset() {
          timer = 0.0f;
          start = false;
     }

     void update(float time) {
          timer = fmod(timer + time, 1.0f);
          if (start) {
               start = false;
               change_state(instructions_state());
          }
     }

     void draw() {
          float splash_position[] = { 0.0f, 64.0f };
          float splash_size[2] = { 228.0f, 36.0f };
          draw_bitmap(splash, splash_position, splash_size);
          if (timer > 0.5f) {
               float prompt_position[] = { 0.0f, -64.0f };
               draw_bitmap(prompt, prompt_position, prompt_size);
          }
     }

     void leave() {
     }
};

state* title_state()
{
     static state* singleton = 0;
     if (!singleton) {
          static title instance;
          singleton = &instance;
     }
     return singleton;
}
