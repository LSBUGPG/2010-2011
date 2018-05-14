#include "spike.h"

#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "collection.h"

static struct {
     int image;
	 float size[2];
     float radius;
} type;

class spike_object: public object {
      float start_point[2];
      float position[2];
      float velocity[2];
 
public:
      spike_object(const point & start) {
           start_point[0] = start.coordinate[0];
           start_point[1] = start.coordinate[1];
      }
	   void update(float time) {
		 position[0] += velocity[0] * time;
           position[1] += velocity[1] * time;
     }

     void draw(void) {
          float size[2] = { type.radius, type.radius };
          draw_bitmap(type.image, position, size);
     }
	 float distance_to_bottom(void) {
          return (position[1] - type.radius) - base;
     }

 void reset(void) {
           position[0] = start_point[0];
           position[1] = start_point[1];
           velocity[0] = -300.0f;
           velocity[1] = 0.0f;
      }
};

object & load_spike_objects(void)
{
	
      type.radius = 50.0f;   //minus right value moves it down
							//plus value of right moves up the platform
							//minus right value moves it down

	static spike_object spikes[] = {						
           point( 1050.0f, -150.0f), 
		   point( 1750.0f, -141.0f),
		   point( 2130.0f, -110.0f),
		   point( 3150.0f,  30.0f),
		   point( 3450.0f, 118.0f),
		   point( 3730.0f, -220.0f),
		   point( 3680.0f, -220.0f),
		   point(3630.0f, -220.0f),
		   point(3780.0f, -220.0f),
		   point(3830.0f, -220.0f),
		   point(5302.0f, 135.0f),
           
      };
      const int number_of_spikes =
           sizeof(spikes) / sizeof(spikes[0]);
 
      static object_array<spike_object> spike_array(&spikes[0],
           &spikes[number_of_spikes]);
 
      type.image = load_bitmap("Spike.bmp");
      type.size[0] = 10.0f;
      type.size[1] = 50.0f;


      static collection_object instance(spike_array);
      return instance;



}
