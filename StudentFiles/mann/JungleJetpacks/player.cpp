#include "player.h"
#include "enemies.h"
#include "shot.h"
#include "engine.h"
#include "measurements.h"
#include "object.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <sdl_keysym.h>

struct player_type {
     GLfloat radius;
     GLuint image;
};

static player_type type;

class player_instance: public object {
     float position[2];
     float velocity[2];
     float heading;
     bool trigger;
     enum {grow , move } stage ;

     control current_direction;

public:
     player_instance() {
     }
     void reset(void) {
          position[0] = -250.0f;
          position[1] = 0.0f;
          heading = 0.0f;
          trigger = false;
     }
     void update(float time) {

          switch (current_direction) {
          case thrust:
               position[1] +=150.0f * time;
               break;
          case left:
               position[0] -=150.0f * time;
               break;
          case right:
               position[0] +=150.0f * time;
               break;
          case down:
               position[1] -=150.0f * time;
               break;
          case fire:
               trigger = true;
               shoot(position, heading);
               break;
          default:
               break;
          }

          if (position[0] < screen_left + type.radius) {
               position[0] = screen_left + type.radius;
          }

          if (position[0] > screen_right - type.radius) {
               position[0] = screen_right - type.radius;
          }

          if (position[1] > screen_top - type.radius) {
               position[1] = screen_top - type.radius;

          }

          if (position[1] < screen_bottom + type.radius) {
               position[1] = screen_bottom + type.radius;
          }

          if (trigger) {
               trigger = false;
               shoot(position, heading);
          }
          if (enemies_collide(position, type.radius)) {
               reset();
          }
     }

     void apply_control(control action, keystate state) {
          if (state == press) {
               current_direction = action;
          } else {
               current_direction = none;
          }
     }
     void draw(void) {
          draw_bitmap(type.image, position, type.radius, 0.0f);
     }

     void spawn(void) {
          reset();
     }
     void kill(void) {
     }
};

static player_instance instance;

object & load_player(const char * image, float position)
{
     type.image = load_bitmap(image);
     type.radius = position;
     return instance;
}

void control_ship(control action, keystate state)
{
     instance.apply_control(action, state);
}