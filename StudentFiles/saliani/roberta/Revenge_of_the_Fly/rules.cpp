#include "rules.h"

#include <conio.h>
#include <stdlib.h>

#include "object.h"
#include "collection.h"
#include "player.h"
#include "frog.h"
#include "poison.h"
#include "measurements.h"
#include "score.h"

enum state { start_game, play, game_over };

static state game_state = start_game;
static int lives = 0;
static float next_spawn = 0.0f;

class revenge_fly: public collection_object {
public:
     revenge_fly(collection & game_objects): collection_object(game_objects) {
     }
     void reset(void) {
		 _cputs("Destroy the Evil-Poisonous-Space Hordes of GiganticFrogs\n");
		 _cputs("with your acid spit from the worst Jakartian dumps,\n");
		 _cputs("companion SuperFly!\n");
		 lives = 3;
		 set_score(0);
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
                    spawn_frog();
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

object & load_revenge_fly(void)
{
     static abstract_object instances[] = {
          load_player("fly2.bmp", "spawn.wav", "eaten.wav", 20.0f), 
          load_poisons("shot.bmp", "spit.wav", 10.0f),  //Original was 1.0f, changed to show the image
          load_frogs("killer_frog.bmp", "bip.wav", "bip.wav", 20.0f), 
		  load_score()
     };
     static const int size = sizeof(instances) / sizeof(instances[0]);
     static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
     static revenge_fly instance(game_objects);
     return instance;
}

void collide(poison_instance & poison, const float * position, float radius)
{
     if (hit_frogs(position, radius)) {
          if (game_state == play) {
               add_score(1);  
          }
          expire_poison(poison);
     }
}

void collide(player_instance & player, const float * position, float radius)
{
     if (hit_frogs(position, radius)) {
          kill_player();
          if (lives) {
               _cprintf("Number of flies/lives = %d\n", lives); //changed _cprintf
               lives--;
               game_state = start_game;
          } else {
			   _cprintf("\n"); //Added a space for better visualization
               _cprintf("You have been eaten.\n"); //changed _cprintf
			   _cprintf("You can be brave and show the frogs what you've got with 'r'\n"); //User-friendly message
			   _cprintf("or you can quit by pressing the 'esc' key.\n"); //User-friendly message
			   game_state = game_over;
          }
     }
}
