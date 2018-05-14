#include "rules.h"

#include <conio.h>
#include <stdlib.h>

#include "object.h"
#include "collection.h"
#include "player.h"
#include "shot.h"
#include "measurements.h"
#include "drifter.h"

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
                    next_spawn += (rand() % 10) * 0.1f;
               }
               break;
          case game_over:
               break;
          }
          next_spawn -= time;
          collection_object::update(time);
     }
}