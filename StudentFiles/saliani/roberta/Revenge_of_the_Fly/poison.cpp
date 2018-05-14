#include "poison.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <math.h>

#include "object.h"
#include "collection.h"
#include "engine.h"
#include "measurements.h"
#include "rules.h"

struct poison_type {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * audio;
};

static poison_type type;

static float poison_speed = 1000.0f;

class poison_instance;

class poison_instance: public object {
     GLfloat position[2];
     GLfloat velocity[2];

public:
     poison_instance() {
     }
     poison_instance(const float * from, float heading) {
          position[0] = from[0];
          position[1] = from[1];
          velocity[0] = poison_speed * sinf(radians(heading));
          velocity[1] = poison_speed * cosf(radians(heading));
     }
     void reset(void) {
          expire_poison(*this);
     }
     void update(float time);
     void draw(void) {
          draw_bitmap(type.image, position, type.radius, 0.0f);
     }
};

const int maximum_poisons = 20;

class poison_pool: public object_pool<poison_instance> {
     poison_instance poisons[maximum_poisons];
public:
     poison_pool(): object_pool<poison_instance>(&poisons[0], &poisons[maximum_poisons]) {
     }
     void fire(const float * position, float heading) {
          play_audio(type.audio);
          add(poison_instance(position, heading));
     }
     void expire(poison_instance & instance) {
          remove(instance);
     }
};

static poison_pool poisons;

collection_object & load_poisons(const char * image, const char * audio, float radius)
{
     type.image = load_bitmap(image);
     type.radius = radius;
     type.audio = load_audio(audio);

     static collection_object instance(poisons);
     return instance;
}

void fire_poison(const float * position, float heading)
{
     poisons.fire(position, heading);
}

void poison_instance::update(float time)
{
     position[0] += velocity[0] * time;
     position[1] += velocity[1] * time;

     bool off_screen = position[0] - type.radius < screen_left ||
                       position[0] + type.radius > screen_right ||
                       position[1] + type.radius > screen_top ||
                       position[1] - type.radius < screen_bottom;

     if (off_screen) {
          poisons.expire(*this);
     } else {
          collide(*this, position, type.radius);
     }
}

void expire_poison(poison_instance & instance)
{
     poisons.expire(instance);
}
