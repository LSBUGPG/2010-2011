#include "music.h"
#include "measurements.h"

#include "object.h"
#include "engine.h"

typedef struct _Mix_Music Mix_Music;

class music_object : public object {
     Mix_Music* music;
     bool updated;
     bool paused;
public:
     music_object(const char* filename) {
          music = load_music(filename);
          updated = false;
          paused = true;
     }

     void reset() {
          play_music(music);
          updated = false;
          paused = false;
     }

     void update(float time) {
          updated = true;
     }

     void draw() {
          if (updated && paused) {
               resume_music();
               paused = false;
          } else if (!updated && !paused) {
               pause_music();
               paused = true;
          }

          updated = false;
     }
};

object& load_music_object(const char* filename)
{
     static music_object instance(filename);
     return instance;
}
