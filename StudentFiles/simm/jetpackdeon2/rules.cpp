#include "rules.h"

#include <conio.h>
#include <stdlib.h>

#include "object.h"
#include "collection.h"
#include "player.h"
#include "evil.h"
#include "timer.h"

#include "measurements.h"

enum state { start_game, play, game_over, winner };

static state game_state = start_game;
static int score = 0;
static int remaining_lives = 0;
static float next_spawn = 0.0f;

class deon: public collection_object {
public:
     deon(collection & game_objects): collection_object(game_objects) {
     }
     void reset(void) {
          _cputs("game begins\n");
          remaining_lives = 3;
          score = 0;
          next_spawn = 1.0f;
          game_state = start_game;
          collection_object::reset();
     }
     void update(float time) {
          switch (game_state) {
          case start_game:
               if (time > next_spawn) {
                    spawn_player();
                    next_spawn += 1.0f;
                    game_state = play;
               }
               break;
          case play:
               if (time > next_spawn) {
                    spawn_evil();
                    next_spawn += (rand() % 10) * 0.1f;
               }
               break;
          case game_over:
               break;

          }
          next_spawn -= time;
          collection_object::update(time);
     }
};

object & load_deon(void)
{
     static abstract_object instances[] = {
          load_player("super.bmp", "spawn.wav", "explode.wav", 20.0f),
          load_evils("evil.bmp", "generate.wav", "hit.wav", 15.0f),
		  load_timer_object()
     };
     static const int size = sizeof(instances) / sizeof(instances[0]);
     static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
     static deon instance(game_objects);
     return instance;
}



void collide(player_instance & player, const float * position, float radius)
{
     if (hit_evils(position, radius)) {
          kill_player();
          if (remaining_lives) {
               _cprintf("lives remaining = %d\n", remaining_lives);
               remaining_lives--;
               game_state = start_game;
          } else {
               _cprintf("game over\n");
               game_state = game_over;
          }
     }
}
