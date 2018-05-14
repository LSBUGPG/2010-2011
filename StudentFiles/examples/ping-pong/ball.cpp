#include "ball.h"

#include <windows.h>
#include <GL/gl.h>
#include <math.h>

#include "object.h"
#include "engine.h"
#include "player.h"
#include "rules.h"
#include "table.h"
#include "measurements.h"

struct ball_type_data {
     GLfloat radius;
     GLuint image;
     GLubyte* colour;
};

static ball_type_data ball_type;

class ball_instance : public object {
     float position[2];
     float velocity[2];
     bool in_play;
     bool held;

public:
     void reset() {
          in_play = false;
          held = true;
          position[0] = 0.0f;
          position[1] = 0.0f;
          velocity[0] = 0.0f;
          velocity[1] = 0.0f;
     }

     void update(float time) {
          float previous[] = { position[0], position[1] };

          if (in_play && !held) {
               position[0] += velocity[0]* time;
               position[1] += velocity[1]* time;

               collide(previous, position);

               velocity[1] -= gravity* time;
          }
     }

     void draw() {
          if (in_play) {
               draw_bitmap(ball_type.image, position, ball_type.radius);
          }
     }

     void bounce() {
          position[1] = table_top + (table_top - position[1]) + ball_type.radius;
          velocity[1]*= -1.0f* coefficient_of_restitution;
     }

     void toss() {
          velocity[1] = 3200.0f;
          held = false;
     }

     void hold(float* set_position) {
          in_play = true;
          held = true;
          position[0] = set_position[0];
          position[1] = set_position[1];
          velocity[0] = 0.0f;
          velocity[1] = 0.0f;
     }

     void hit(float power) {
          velocity[0] = power* 2000.0f;
          velocity[1] = fabs(velocity[0]* 0.5f);
     }

     void hit(table_side side, float power) {
          switch (side) {
          case left:
               if (position[0] < -ball_type.radius) {
                    hit(power);
               }
               break;
          case right:
               if (position[0] > ball_type.radius) {
                    hit(-power);
               }
               break;
          default:
               // ignore
               break;
          }
     }
};

static ball_instance instance;

object* load_ball_object(const char* image, const char* audio)
{
     static GLubyte white[3] = { 255, 255, 255 };

     ball_type.image = load_bitmap(image);
     ball_type.radius = ball_radius;
     ball_type.colour = white;

     return &instance;
}

void bounce_ball()
{
     instance.bounce();
}

void toss_ball()
{
     instance.toss();
}

void hold_ball(float* position)
{
     instance.hold(position);
}

void hit_ball(table_side side, float power)
{
     instance.hit(side, power);
}

void remove_ball_from_play()
{
     instance.reset();
}
