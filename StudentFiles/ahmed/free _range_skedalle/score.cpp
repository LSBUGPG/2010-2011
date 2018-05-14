#include "engine.h"
#include "object.h"
#include <stdio.h>
#include <algorithm>

static TTF_Font * font = 0;
static int points = 0;

const int invalid_texture = -1;

class score: public object {
     int texture;
     float position[2];
     float size[2];
     int points_displayed;
public:
     void reset(void) {
          position[0] = -128.0f;
          position[1] = 64.0f;
          points_displayed = invalid_texture;
     }

     void update(float time) {
          if (points != points_displayed) {
               if (points_displayed != invalid_texture) {
                    delete_bitmap(texture);
               }
               char buffer[] = "score: xx";
               sprintf_s(buffer, "score: %d", points);
               texture = load_text_line(font, buffer, size);
               points_displayed = points;
          }
     }

     void draw(void) {
          if (points_displayed != invalid_texture) {
               draw_bitmap(texture, position, size);
          }
     }
};
   
void add_score(void)
{
     points = std::min(points + 10, 99);
}

object & load_score_object(TTF_Font * input_font)
{
     font = input_font;
     static score instance;
     return instance;
}