#include "gameover.h"
#include "state.h"
#include "measurements.h"
#include "text.h"
#include "background.h"
#include "script.h"
#include "graphics.h"
#include "music.h"
#include "collection.h"
#include "object.h"
#include "engine.h"
#include "controls.h"

static object & load_New_Eden()
{
     static object * eden = 0;

     if (!eden) {
          static abstract_object instances[] = {
               load_background_object("background.jpg"),
               load_text_object(),
               load_image_object(),
               load_music_object("One_Last-Sir_Shir-10333_hifi.mp3"),
               load_script()
          };

          static const int size = sizeof(instances) / sizeof(instances[0]);
          static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
          static collection_object New_Eden(game_objects);
          eden = &New_Eden;
     }

     return *eden;
}

class game : public state {
     object * game_objects;
public:
     game() {
          game_objects = &load_New_Eden();
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
