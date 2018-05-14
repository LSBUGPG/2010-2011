#include "object.h"

#include <windows.h>
#include <GL/gl.h>

#include "engine.h"
#include "player.h"
#include "rules.h"
#include "ball.h"
#include "measurements.h"

struct {
     GLuint image;
     GLfloat size[2];
     GLfloat position[2];
} table_type;

class table_instance : public object {
public:
     void reset() {}

     void update(float time) {}

     void draw() {
          draw_bitmap(table_type.image, table_type.position, table_type.size);
     }
};

object* load_table_object(const char* image, const char* audio)
{
     static GLubyte white[3] = { 255, 255, 255 };

     table_type.image = load_bitmap(image);
     table_type.size[0] = GLfloat(table_width);
     table_type.size[1] = GLfloat(net_height);
     table_type.position[0] = 0.0f;
     table_type.position[1] = table_top;

     static table_instance instance;
     return &instance;
}

void collide(float* previous, float* next)
{
     float height = next[1] - table_top;
     if (previous[0] > 0.0f && next[0] < 0.0f && height < net_height) {
          notify_out_of_play();
     } else if (previous[0] < 0.0f && next[0] > 0.0f && height < net_height) {
          notify_out_of_play();
     } else if (height < 0.0f) {
          if (next[0] > -table_type.size[0] && next[0] < table_type.size[0]) {
               table_side side = none;
               if (next[0] > 0.0f) {
                    side = right;
               } else {
                    side = left;
               }
               notify_bounce(side);
               bounce_ball();
          } else {
               notify_out_of_play();
          }
     }
}
