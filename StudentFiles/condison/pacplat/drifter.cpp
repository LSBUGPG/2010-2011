#include "drifter.h"

#include <windows.h>
#include <GL/gl.h>

#include "object.h"
#include "engine.h"
#include "measurements.h"

struct drifter_type {
     GLfloat radius;
     GLuint image;
};

static drifter_type type;
const float growth_rate = 5.0f;
const int initial_speed = 20;

class drifter_instance: public object {
     float position[2];
     float velocity[2];
     float radius;
     enum { grow, move } stage;

public:
     drifter_instance(void) {
     }
     void reset(void) {
          position[0] = float((rand() % screen_width) - screen_width / 2);
          position[1] = float((rand() % screen_height) - screen_height / 2);
          velocity[0] = float((rand() % 2) * initial_speed * 2 - initial_speed);
          velocity[1] = float((rand() % 2) * initial_speed * 2 - initial_speed);
          stage = grow;
          radius = 1.0f;
     }
     void update(float time) {
          switch (stage) {
          case grow:
               if (radius < type.radius) {
                    radius += growth_rate * time;
               } else {
                    radius = type.radius;
                    stage = move;
               }
               break;
          case move:
               position[0] += velocity[0] * time;
               position[1] += velocity[1] * time;

               if (position[0] < screen_left + type.radius) {
                    position[0] = screen_left + type.radius;
                    velocity[0] *= -1.0f;
               }

               if (position[0] > screen_right - type.radius) {
                    position[0] = screen_right - type.radius;
                    velocity[0] *= -1.0f;
               }

               if (position[1] > screen_top - type.radius) {
                    position[1] = screen_top - type.radius;
                    velocity[1] *= -1.0f;
               }

               if (position[1] < screen_bottom + type.radius) {
                    position[1] = screen_bottom + type.radius;
                    velocity[1] *= -1.0f;
               }
               break;
          }
     }
     void draw(void) {
          draw_bitmap(type.image, position, radius);
     }
};

object & load_drifter(const char * image)
{
     type.image = load_bitmap(image);
     type.radius = 10.0f;
     static drifter_instance instance;
     return instance;
}
