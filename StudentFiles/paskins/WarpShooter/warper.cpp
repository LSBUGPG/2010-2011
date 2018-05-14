#include "warper.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <math.h>

#include "object.h"
#include "engine.h"
#include "shot.h"
#include "measurements.h"
#include "controls.h"

struct player_type {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * spawn;
     Mix_Chunk * explode;
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
     float heading;
     float angular_velocity;
     enum { dead, invulnerable, play } stage;
     float age;
     bool trigger;
	 bool ship_bottom; //whether player ship is at the bottom of the screen or not
     float current_speed() {
          return sqrtf(velocity[0] * velocity[0] + velocity[1] * velocity[1]);
     }
public:
     player_instance() {
     }
     void reset(void) {
          position[0] = 0.0f;
          position[1] = -210.0f;
          velocity[0]= 0.0f;
          velocity[1]= 0.0f;
          acceleration = 0.0f;
          angular_velocity = 0.0f;
          heading = 0.0f;
          stage = dead;
          age = 0.0f;
          trigger = false;
     }
     void update(float time) {
          switch (stage) {
          case dead:
               break;
          case invulnerable:
               if (age > 2.0f) {
                    stage = play;
               }
          case play:
               age += time;
               position[0] += velocity[0] * time;
               position[1] += velocity[1] * time;
               heading += angular_velocity * time;
               velocity[0] += acceleration * time;
               velocity[1] += acceleration * time;

               float speed = current_speed();
               float drag_factor = drag * time;
               if (speed > maximum_speed) {
                    velocity[0] *= maximum_speed / speed;
                    velocity[1] *= maximum_speed / speed;
               } else if (drag_factor > speed) {
                    velocity[0] = 0.0f;
                    velocity[1] = 0.0f;
               } else {
                    velocity[0] *= (speed - drag_factor) / speed;
                    velocity[1] *= (speed - drag_factor) / speed;
               }

               if (position[0] < screen_left + type.radius) {
                    position[0] = screen_left + type.radius;
                    velocity[0] = 0.0f;
               }

               if (position[0] > screen_right - type.radius) {
                    position[0] = screen_right - type.radius;
                    velocity[0] = 0.0f;
               }

               if (position[1] > screen_top - type.radius) {
                    position[1] = screen_top - type.radius;
                    velocity[1] = 0.0f;
               }

               if (position[1] < screen_bottom + type.radius) {
                    position[1] = screen_bottom + type.radius;
                    velocity[1] = 0.0f;
               }

               if (trigger) {
                    trigger = false;
                    fire_shot(position, heading);
               }

               break;
          }
          if (stage == play) {
               collide(*this, position, type.radius);
          }
     }
     void draw(void) {
          bool show = (stage == play);
          if (stage == invulnerable) {
               show = (int(age * 10) % 2) == 0;
          }
          if (show) {
               draw_bitmap(type.image, position, type.radius, heading);
          }
     }
     void apply_control(control action, keystate state) {
          switch (state) {
          case press:
               switch (action) {
				case warp:
                    warp_ship();			//press up arrow to warp to top/bottom
                    break;
               case left:
                    position[0] -= 40;
                    break;
               case right:
                    position[0] += 40;
                    break;
               case fire:
                    trigger = true;
                    break;
               default:
                    break;
               }
               break;
          case release:
               switch (action) {
               case warp:
                    acceleration = 0.0f;
                    break;
               case left:
                    angular_velocity = 0.0f;
                    break;
               case right:
                    angular_velocity = 0.0f;
                    break;
               case fire:
                    trigger = false;
                    break;
               default:
                    break;
               }
               break;
          default:
               break;
          }
     }

	 void warp_ship(){		//for when the up key is pressed
		 if (ship_bottom == false){		//warps the ship to the bottom of the screen if at the top
			position[1] = -210.0f;		//faces the ship upward
			heading = 0.0f;
			ship_bottom = true;
		 }
		 else {
			position[1] = 210.0f;		//warps the ship to the top of the screen
			heading = 180.0f;			//faces the ship downward
			ship_bottom = false;
		 }
	 }
     void spawn(void) {
          reset();
          play_audio(type.spawn);
          stage = invulnerable;
          age = 0.0f;
     }
     void kill(void) {
          play_audio(type.explode);
          stage = dead;
     }
};

static player_instance instance;

object & load_player(const char * image, const char * spawn_audio,
                     const char * explode_audio, float radius)
{
     type.image = load_bitmap(image);
     type.spawn = load_audio(spawn_audio);
     type.explode = load_audio(explode_audio);
     type.radius = radius;
     return instance;
}

void control_ship(control action, keystate state)
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
