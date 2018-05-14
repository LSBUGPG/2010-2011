#include "player.h"

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

class player_instance: public object {
     float position[2];
public:
     player_instance() {
     }
     void reset(void) {
          position[0] = 0.0f;
          position[1] = 0.0f;
     }
     void update(float time) {
     }
     void draw(void) {
          draw_bitmap(type.image, position, type.radius);
     }
     void apply_control(control action, keystate state) {
          switch (state) {
          case press:
               switch (action) {
               case jump:
                    break;
               case left:
                    break;
               case right:
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
                    break;
               case right:
                    break;
               default:
                    break;
               }
               break;
          default:
               break;
          }
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
