#include "object.h"
#include "engine.h"
#include "player.h"
#include "measurements.h"
#include "enemies.h"
#include "collection.h"
#include "background.h"


#include <windows.h>
#include <SDL.h>
#include <conio.h>

bool pause = false;
bool step = false;
bool reset = true;

void handle_key(SDL_keysym & key, keystate state)
{
     control action = none;
     switch (key.sym) {
     case SDLK_UP:
          action = up;
          break;
     case SDLK_DOWN:
          action = down;
          break;
     case SDLK_LEFT:
          action = left;
          break;
     case SDLK_RIGHT:
          action = right;
          break;
     default:
          break;
     }

     if (action != none) {
          control_player(action, state);
     } else if (state == release) {
          switch (key.sym) {
          case SDLK_ESCAPE:
               quit(0);
               break;
          case SDLK_p:
               pause = !pause;
               break;
          case SDLK_f:
               step = true;
               break;
          case SDLK_r:
               reset = true;
               break;
          default:
               break;
          }
     }
}

void process_events(void)
{
     SDL_Event an_event;

     while (SDL_PollEvent(&an_event)) {
          switch (an_event.type) {
          case SDL_KEYUP:
               handle_key(an_event.key.keysym, release);
               break;
          case SDL_KEYDOWN:
               handle_key(an_event.key.keysym, press);
               break;
          case SDL_QUIT:
               quit(0);
               break;
          }
     }
}

int main(int argc, char * argv[])
{
	 _cputs("Aim:\n" 
		    "Aviod the moving white balls\n" 
			"Make your way from the starting position\n"
		    "to the finish (the centre of the wall on the right)\n");
     _cputs("Controles:\n" 
		    "Use the up, down, left and right keys to move the blue ball\n");
	 _cputs("Press P to pause the game\n");
     _cputs("Press R to reset game or genarate a new challenge\n");
	 
		   
     initialise_engine(screen_width, screen_height, scale);

     
     static abstract_object instances[] = {
          load_player("player.bmp", 10.0f),
          load_enemies("enemies.bmp"),

     };

     static const int size = 
          sizeof(instances) / sizeof(instances[0]);

     static object_array<abstract_object> game_objects(
          &instances[0], &instances[size]);

     static collection_object pacplat(game_objects);

     while (true) {
          const float time = 1.0f / 60.0f;

          process_events();
          if (reset) {
               reset = false;
               pacplat.reset();
          } else if (!pause || step) {
               step = false;
               pacplat.update(time);
          }
          start_render();
          pacplat.draw();
          end_render();
     }

     return 0;
}
