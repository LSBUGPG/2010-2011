#include "player.h"
#include "object.h"
#include "engine.h"
#include "drifter.h"
#include "floor.h"
#include "flame monster.h"

static float player_position[2] = { 0.0f, 0.0f };

class flame_monster: public object {
     int image;
     float position[2];
     float size[2];

public:
     flame_monster(const char * image_name) {
          image = load_bitmap(image_name);
     }

     void reset(void) {
          position[0] = 25.0f;
          position[1] = 25.0f;
          size[0] = 80.0f;
          size[1] = 60.0f;
     }

     void update(float time) {
          const float speed = 20.0f;
          if (position[0] > player_position[0]) {
               position[0] -= speed * time;
          } else if (position[0] < player_position[0]) {
               position[0] += speed * time;
          }


     }

     void draw(void) {
          draw_bitmap(image, position, size);
     }
};

object & load_flame_monster(void)
{
     static flame_monster instance("fire monster.bmp");
     return instance;
}

void notify_monsters(float * position)
{
     player_position[0] = position[0];
     player_position[1] = position[1];
}