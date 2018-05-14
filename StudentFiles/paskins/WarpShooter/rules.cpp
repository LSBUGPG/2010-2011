#include "rules.h"
#include "background.h"

#include <conio.h>
#include <stdlib.h>

#include "object.h"
#include "collection.h"
#include "warper.h"
#include "enemy.h"
#include "shot.h"
#include "measurements.h"
#include "gameover.h"

enum state { start_game, play, game_over };

static state game_state = start_game;
static int score = 0;
static int remaining_lives = 0;
static float next_spawn = 0.0f;

class warpshooter: public collection_object {
public:
     warpshooter(collection & game_objects): collection_object(game_objects) {
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
                    spawn_enemy();
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

object & load_warpshooter(void)
{
     static abstract_object instances[] = {
		 load_background_object("nebula.bmp"),
          load_player("warpshooter.bmp", "spawn.wav", "explode.wav", 12.0f),
          load_shots("shot.bmp", "laser.wav", 5.0f),
          load_enemies("enemy_ship.bmp", "generate.wav", "hit.wav", 15.0f)
		  
     };
     static const int size = sizeof(instances) / sizeof(instances[0]);
     static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
     static warpshooter instance(game_objects);
     return instance;
}

void collide(shot_instance & shot, const float * position, float radius)
{
     if (hit_enemies(position, radius)) {
          if (game_state == play) {
               score += 5;
               _cprintf("+5 Score! Total: %d\n", score);
          }
          expire_shot(shot);
     }
}

void collide(player_instance & player, const float * position, float radius)
{
     if (hit_enemies(position, radius)) {
          kill_player();
          if (remaining_lives) {
               _cprintf("Ships remaining: %d\n", remaining_lives);
               remaining_lives--;
               game_state = start_game;
          } else {
               _cprintf("Game Over!\n");
               game_state = game_over;
               notify_win(false);
          }
     }
}
