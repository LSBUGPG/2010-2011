#include "gameover.h"
#include "state.h"
#include "measurements.h"
#include "text.h"
#include "Answer.h"
#include "score.h"

#include "object.h"
#include "engine.h"
#include "controls.h"
#include "collection.h"

static object * scramble_instance = 0;

object & load_scramble()
{
     if (!scramble_instance) {
          TTF_Font * font = load_font("LiberationMono-Regular.ttf", 24);

          static abstract_object instances[] = {
		          load_text_object(font),
		          load_Answer_object(font),
                    load_score_object(font)
	     };

          static const int size = sizeof(instances) / sizeof(instances[0]);
          static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
          static collection_object scramble(game_objects);

          scramble_instance = &scramble;
     }

     return *scramble_instance;
}


class game : public state {
     object * game_objects;
public:
     game() {
          game_objects = &load_scramble();
     }

     void enter() {
          reset();
     }

     void reset() {
          game_objects->reset();
     }

     void update(float time) {
          game_objects->update(time);
     }

     void draw() {
          game_objects->draw();
     }

     void leave() {
     }
};

state* game_state()
{
     static state* singleton = 0;
     if (!singleton) {
          static game instance;
          singleton = &instance;
     }
     return singleton;
}
