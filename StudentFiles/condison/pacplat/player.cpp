#include "player.h"
#include "enemies.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <math.h>

#include "object.h"
#include "engine.h"
#include "measurements.h"

struct player_type {
     GLfloat radius;
     GLuint image;
};

static player_type type;
const float growth_rate = 5.0f;
const int initial_speed = 290;

class player_instance: public object {
     
     float velocity[1];
     float position[1];
     float radius;
     enum { grow, move } stage;


     control current_direction;
public:
     player_instance() {
     }
     void reset(void) {
          position[1] = 0.0f;
          position[1] = -260.0f;
          velocity[1] = -300.0f;
     }
     void update(float time) {

          switch (current_direction) {
          case up:
               position[1] += 180.0f * time;
               break;
          case down:
               position[1] -= 180.0f * time;
               break;
          case left:
               position[0] -= 180.0f * time;
               break;
          case right:
               position[0] += 180.0f * time;
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
          if (collide_enemies(position, type.radius)) {reset();}
	 }

     void apply_control(control action, keystate state) {
          if (state == press) {
               current_direction = action;
          } else {
               current_direction = none;
          }
     }
     void draw(void) {
          draw_bitmap(type.image, position, type.radius);
     }
};

static player_instance instance;

object & load_player(const char * image, float radius)
{
     type.image = load_bitmap(image);
     type.radius = radius;
     return instance;
}

void control_player(control action, keystate state)
{
     instance.apply_control(action, state);
}




