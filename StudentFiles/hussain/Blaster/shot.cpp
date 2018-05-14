#include "shot.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>
#include <math.h>

#include "object.h"
#include "collection.h"
#include "engine.h"
#include "measurements.h"
#include "rules.h"

struct shot_type {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * audio;
};

static shot_type type;

static float shot_speed = 1000.0f;

class shot_instance;

class shot_instance: public object {
     GLfloat position[2];
     GLfloat velocity[2];

public:
     shot_instance() {
     }
     shot_instance(const float * from, float heading) {
          position[0] = from[0];
          position[1] = from[1];
          velocity[0] = shot_speed * sinf(radians(heading));
          velocity[1] = shot_speed * cosf(radians(heading));
     }
     void reset(void) {
          expire_shot(*this);
     }
     void update(float time);
     void draw(void) {
     draw_bitmap(type.image, position,  type.radius, 0.0f);
     }
};

const int maximum_shots = 20;

class shot_pool: public object_pool<shot_instance> {
     shot_instance shots[maximum_shots];
public:
     shot_pool(): object_pool<shot_instance>(&shots[0], &shots[maximum_shots]) {
     }
     void fire(const float * position, float heading) {
          play_audio(type.audio);
          add(shot_instance(position, heading));
     }
     void expire(shot_instance & instance) {
          remove(instance);
     }
};

static shot_pool shots;

collection_object & load_shots(const char * image, const char * audio, float radius)
{
     type.image = load_bitmap(image);
     type.radius = radius;
     type.audio = load_audio(audio);

     static collection_object instance(shots);
     return instance;
}

void fire_shot(const float * position, float heading)
{
     shots.fire(position, heading);
}

void shot_instance::update(float time)
{
     position[0] += velocity[0] * time;
     position[1] += velocity[1] * time;

     bool off_screen = position[0] - type.radius < screen_left ||
                       position[0] + type.radius > screen_right ||
                       position[1] + type.radius > screen_top ||
                       position[1] - type.radius < screen_bottom;

     if (off_screen) {
          shots.expire(*this);
     } else {
          collide(*this, position, type.radius);
     }
}

void expire_shot(shot_instance & instance)
{
     shots.expire(instance);
}
