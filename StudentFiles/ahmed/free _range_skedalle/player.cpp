#include "player.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <math.h>

#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "chicken.h"

struct player_type {
     GLuint image;
	 float size[2];
     Mix_Chunk* audio;
};

static player_type type;

static const float maximum_acceleration = 500.0f; // units per second per second
static const float maximum_speed = 200.0f; // units per second
static const float turn_speed = 180.0f; // degrees of turn per second
static const float drag = 50.0f; // units per second

class player_instance: public object {
     float position[2];
     float velocity[2];
     float acceleration;
     bool move_left;
     bool move_right;
     bool do_jump;
     bool jumping;
public:
     player_instance() {
     }
     void reset(void) {
          position[0] = 290.0f;
          position[1] = -150.0f;
          velocity[0] = 0.0f;
          velocity[1] = 0.0f;
          move_left = false;
          move_right = false;
          do_jump = false;
          jumping = false;
     }
     void update(float time) {
          if (move_left) {
               position[0] -= 60.0f * time;
          } else if (move_right) {
               position[0] += 60.0f * time;
          } else if (do_jump) {
			  play_audio(type.audio);
               velocity[1] = 500.0f;
               do_jump = false;
               jumping = true;
          }

          position[0] += velocity[0] * time;
          position[1] += velocity[1] * time;

          if (jumping) {
               velocity[1] -= 640.0f * time;
          }

          if (position[1] < -150.0f) {
               position[1] = -150.f;
               jumping = false;
          }

		  notify_chickens(position);
     }
     void draw(void) {
          draw_bitmap(type.image, position, type.size);
     }
     void apply_control(control action, keystate state) {
          switch (state) {
          case press:
               switch (action) {
               case jump:
                    do_jump = true;
                    break;
               case left:
                    move_left = true;
                    break;
               case right:
                    move_right= true;
                    break;
               default:
                    break;
               }
               break;
          case release:
               switch (action) {
               case jump:
                    break;
               case left:
                    move_left = false;
                    break;
               case right:
                    move_right= false;
                    break;
               default:
                    break;
               }
               break;
          default:
               break;
          }
     }
     void spawn(void) {
          reset();
     }
     void kill(void) {
     }
};

static player_instance instance;

object & load_player(const char * image, const float * size)
{
     type.image = load_bitmap(image);
	 type.audio = load_audio("Boing.wav");
	 type.size[0] = size[0];
	 type.size[1] = size[1];
     return instance;
}

void control_player(control action, keystate state)
{
     instance.apply_control(action, state);
}

void spawn_player(void)
{
     instance.spawn();
}

void kill_player(void)
{
     instance.kill();
}
