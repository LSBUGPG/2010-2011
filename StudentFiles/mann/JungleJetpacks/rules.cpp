#include "rules.h"

#include <conio.h>
#include <stdlib.h>

#include "object.h"
#include "collection.h"
#include "player.h"
#include "shot.h"
#include "measurements.h"

enum state { start_game, play, game_over };

static state game_state = start_game;
static int score = 0;
static int remaining_lives = 0;
static float next_spawn = 0.0f;

class dot_blaster: public collection_object {
public:
     dot_blaster(collection & game_objects): collection_object(game_objects) {
     }
     void reset(void) {
          _cputs("game begins\n");
          remaining_lives = 3;
          score = 0;
          next_spawn = 1.0f;
          game_state = start_game;
          collection_object::reset();
     }
};

object & load_dot_blaster(void)
{
     static abstract_object instances[] = {
          load_player("panda.bmp", 10.0f),
          load_shots("shot.bmp", "laser.wav", 2.0f),
     };
     static const int size = sizeof(instances) / sizeof(instances[0]);
     static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
     static dot_blaster instance(game_objects);
     return instance;
}

void collide(shot_instance & shot, const float * position, float radius)
{
     if ((position, radius)) {
          if (game_state == play) {
               score += 10;
               _cprintf("score is now %d\n", score);
          }
          expire_shot(shot);
     }
}
