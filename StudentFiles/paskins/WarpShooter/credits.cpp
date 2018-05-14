#include "state.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"
#include "controls.h"

struct line {
     int image;
     float size[2];
     float position[2];
};

class credits: public state {
     line credit_line[3];
     int number_of_lines;
     float timer;
public:
     credits(void) {
          TTF_Font * font = load_font("LiberationMono-Bold.ttf", 20);
          if (font) {
               credit_line[0].image = load_text_line(font, "CREDITS", credit_line[0].size);
               release_font(font);
          }
          font = load_font("LiberationMono-Regular.ttf", 20);
          if (font) {
               credit_line[1].image = load_text_line(font, "Gary Paskins", credit_line[1].size);
               release_font(font);
          }
		  font = load_font("LiberationMono-Regular.ttf", 20);
          if (font) {
               credit_line[2].image = load_text_line(font, "Paul Sinnett", credit_line[2].size);
               release_font(font);
          }
          number_of_lines = sizeof(credit_line) / sizeof(credit_line[0]);
     }

     void enter(void) {
          reset();
     }

     void reset(void) {
          timer = 20.0f;
          skip = false;

          float vertical = -half_height;
          const float line_height = 32.0f;

          for (int line_number = 0; line_number < number_of_lines; line_number++) {
               credit_line[line_number].position[0] = 0.0f;
               credit_line[line_number].position[1] = vertical;
               vertical -= line_height;
          }
     }

     void update(float time) {
          if (skip) {
               timer = 0.0f;
          }
          if (timer > time) {
               timer -= time;
          } else {
               change_state(title_state());
          }

          const float credits_speed = 16; // pixels per second

          for (int line_number = 0; line_number < number_of_lines; line_number++) {
               credit_line[line_number].position[1] += time * credits_speed;
          }
     }

     void draw(void) {
          for (int line_number = 0; line_number < number_of_lines; line_number++) {
               draw_bitmap(
                    credit_line[line_number].image,
                    credit_line[line_number].position,
                    credit_line[line_number].size);
          }
     }

     void leave(void) {
     }
};

state * credits_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static credits instance;
          singleton = &instance;
     }
     return singleton;
}
