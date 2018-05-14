#include "object.h"
#include "engine.h"

struct brownian_type_data
    {
    GLfloat radius;
    GLuint image;
    };

static const int number_of_penman = 10;
static brownian_type_data penman_type;

class brownian_instance: public object
    {
        GLfloat position[2];
        GLubyte colour[3];
    public:
        void draw(void)
            {
            draw_bitmap(penman_type.image, position, penman_type.radius, colour);
            }

        void reset(void)
            {
            position[0] = GLfloat((rand() % 600) - 300);
            position[1] = GLfloat((rand() % 400) - 200);
            colour[0] = (rand() % 2) * 255;
            colour[1] = (rand() % 2) * 255;
            colour[2] = (rand() % 2) * 255;
            }

        void update(float time)
            {
            position[0] += GLfloat((rand() % 101) - 50) * time;
            position[1] += GLfloat((rand() % 101) - 50) * time;
            }
    };

static brownian_instance penman[number_of_penman];

class penman_array: public object_collection
    {
    protected:
        void for_each_object(object_function & function)
            {
            for (int index = 0; index < number_of_penman; index++)
                {
                function.call(penman[index]);
                }
            }
    };

object * load_penman_objects(const char * image, float radius)
    {
    penman_type.image = load_bitmap(image);
    penman_type.radius = radius;

    static penman_array instance;
    return &instance;
    }
