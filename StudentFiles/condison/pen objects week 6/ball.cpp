#include "object.h"
#include "engine.h"

#include <SDL_mixer.h>

struct ball_type_data
    {
    GLfloat radius;
    GLuint image;
    Mix_Chunk * audio;
    GLubyte * colour;
    };

static const int screen_height = 480;
static const GLfloat base = GLfloat(-screen_height / 2);
static const int number_of_balls = 10;
static ball_type_data ball_type;

class ball_instance: public object
    {
        GLfloat position[2];
        GLfloat velocity[2];

        GLfloat distance_to_bottom(void)
            {
            return (position[1] - ball_type.radius) - base;
            }

    public:
        void reset(void)
            {
            position[0] = GLfloat((rand() % 600) - 300);
            position[1] = GLfloat((rand() % 400) - 200);
            velocity[0] = 0.0f;
            velocity[1] = 0.0f;
            }

        void update(float time)
            {
            position[0] += velocity[0] * GLfloat(time);
            position[1] += velocity[1] * GLfloat(time);
            GLfloat distance = distance_to_bottom();
            if (distance < 0.0f)
                {
                position[1] = base + ball_type.radius - distance;
                velocity[1] *= -1.0f;
                }

            velocity[1] -= GLfloat(9810.0f * time); // acceleration due to gravity in mm
            }

        void draw(void)
            {
            draw_bitmap(ball_type.image, position, ball_type.radius, ball_type.colour);
            }
    };

static ball_instance ball[number_of_balls];

class ball_array: public object_collection
    {
    protected:
        void for_each_object(object_function & function)
            {
            for (int index = 0; index < number_of_balls; index++)
                {
                function.call(ball[index]);
                }
            }
    };

object * load_ball_objects(const char * image, const char * audio, float radius)
    {
    static GLubyte white[3] = { 255, 255, 255 };

    ball_type.image = load_bitmap(image);
    ball_type.audio = load_audio(audio);
    ball_type.radius = radius;
    ball_type.colour = white;

    static ball_array instance;
    return &instance;
    }
