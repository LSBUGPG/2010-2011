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

class introduction: public state {
     line intro_line[6];
     int number_of_lines;
     float timer;
public:
     introduction(void) {
          TTF_Font * font = load_font("LiberationMono-Bold.ttf", 20);
          if (font) {
               intro_line[0].image = load_text_line(font, "Story", intro_line[0].size);
               release_font(font);
          }
          font = load_font("LiberationMono-Regular.ttf", 20);
          if (font) {
               intro_line[1].image = load_text_line(font, "In the year 2316, ", intro_line[1].size);
               release_font(font);
          }
		  font = load_font("LiberationMono-Regular.ttf", 20);
		  if (font) {
               intro_line[2].image = load_text_line(font, "the human space station CTX16", intro_line[2].size);
               release_font(font);
          }
		  font = load_font("LiberationMono-Regular.ttf", 20);
		  if (font) {
               intro_line[3].image = load_text_line(font, "came under fire from enemy ships.", intro_line[3].size);
               release_font(font);
          }
		  font = load_font("LiberationMono-Regular.ttf", 20);
		  if (font) {
               intro_line[4].image = load_text_line(font, "You are the pilot of the remaining", intro_line[4].size);
               release_font(font);
          }
		  font = load_font("LiberationMono-Regular.ttf", 20);
		  if (font) {
               intro_line[5].image = load_text_line(font, "4 ships. Good luck commander.", intro_line[5].size);
               release_font(font);
          }
          number_of_lines = sizeof(intro_line) / sizeof(intro_line[5]);
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
               intro_line[line_number].position[0] = 0.0f;
               intro_line[line_number].position[1] = vertical;
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
               change_state(game_state());
          }

          for (int line_number = 0; line_number < number_of_lines; line_number++) {
               intro_line[line_number].position[1] += time * 50;
          }
     }

     void draw(void) {
          for (int line_number = 0; line_number < number_of_lines; line_number++) {
               draw_bitmap(
                    intro_line[line_number].image,
                    intro_line[line_number].position,
                    intro_line[line_number].size);
          }
     }

     void leave(void) {
     }
};

state * introduction_state(void)
{
     static state * singleton = 0;
     if (!singleton) {
          static introduction instance;
          singleton = &instance;
     }
     return singleton;
}