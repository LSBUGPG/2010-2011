#include "player.h"
#include "object.h"
#include "engine.h"
#include "drifter.h"
#include "floor.h"
#include "flame monster.h"

class player_instance: public object {
     int image;
     float position[2];
     float size[2];
     control current_direction;

public:
     player_instance(const char * image_name) {
          image = load_bitmap(image_name);
     }

     void reset(void) {
          position[0] = 0.0f;
          position[1] = 64.0f;
          size[0] = 64.0f;
          size[1] = 90.0f;
     }

     void update(float time) {
          switch (current_direction) {
          case up:
               position[1] += 80.0f * time;
               break;
          case down:
               position[1] -= 80.0f * time;
               break;
          case left:
               position[0] -= 80.0f * time;
               break;
          case right:
               position[0] += 80.0f * time;
               break;
          default:
               break;
          }
          notify_monsters(position);
     }

     void draw(void) {
          draw_bitmap(image, position, size);
     }

     void apply_control(control action, keystate state) {
          if (state == press) {
               current_direction = action;
          } else {
               current_direction = none;
          }
     }
};

static player_instance * player = 0;

object & load_player(void)
{
     static player_instance instance("My Charicter copy.bmp");
     player = &instance;
     return instance;
}


void control_player(control action, keystate state)
{
     if (player) {
          player->apply_control(action, state);
     }
}
