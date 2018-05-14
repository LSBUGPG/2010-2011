#include "chicken.h"
#include "score.h"
#include "object.h"
#include "engine.h"
#include "collection.h"

static struct {
     int image;
     Mix_Chunk* audio;
} type;

class chicken_object;
static void expire_chicken(chicken_object & instance);

static float player_position[2];

void notify_chickens(const float * position)
{
	player_position[0] = position[0];
	player_position[1] = position[1];
}

class chicken_object: public object {
     float position[2];
public:
     void update(float time) {
          position[0] -= 500.0f * time;

          if (position[0] < -350.0f) {
               expire_chicken(*this);
          }

		  const float radius = 60.0f;
		  if (   position[0] > player_position[0] - radius 
			  && position[0] < player_position[0] + radius
			  && position[1] > player_position[1] - radius
			  && position[1] < player_position[1] + radius) {

		       expire_chicken(*this);
			   play_audio(type.audio);
			   add_score();
		  }

     }

     void draw(void) {
          float size[2] = { 32.0f, 32.0f };
          draw_bitmap(type.image, position, size);
     }

     void reset(void) {
          position[0] = 350.0f;
          position[1] = 100.0f;
     }
};

const int maximum_chickens = 20;

class chicken_pool: public object_pool<chicken_object> {
     chicken_object instance[maximum_chickens];
public:
     chicken_pool(): object_pool(&instance[0], &instance[maximum_chickens]) {
     }
     void spawn(void) {
          chicken_object new_chicken;
          new_chicken.reset();
          add(new_chicken);
     }
};

static chicken_pool chickens;

class chicken_manager: public collection_object {
     float respawn_time;

public:
     chicken_manager(collection & source): collection_object(source), respawn_time(1.50f) {
     }

     void update(float time) {
          if (time > respawn_time) {
               chickens.spawn();
               respawn_time = 1.50f;
          } else {
               respawn_time -= time;
          }
          collection_object::update(time);
     }
};

void expire_chicken(chicken_object & instance)
{
     chickens.remove(instance);
}

object & load_chickens_object(void)
{
     type.image = load_bitmap("chickens.bmp");
	 type.audio = load_audio("chicken sound.wav");
     static chicken_manager instance(chickens);
     return instance;
}
