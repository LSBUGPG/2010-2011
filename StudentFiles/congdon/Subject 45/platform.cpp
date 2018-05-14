#include "platform.h"

#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "collection.h"
#include "player.h"

static struct {
	int image;
	float size[2];
	float radius;
} type;

inline float square(float number)
{
	return number* number;
}

inline float square_distance_between(const float* point_a,
	const float* point_b)
{
	return square(point_a[0] - point_b[0]) +
		square(point_a[1] - point_b[1]);
}

class platform_object: public object {
	float start_point[2];
	float position[2];
	float velocity[2];

public:
	platform_object(const point & start) {
		start_point[0] = start.coordinate[0];
		start_point[1] = start.coordinate[1];
	}

	void update(float time) {
		position[0] += velocity[0] * time;
		position[1] += velocity[1] * time;

		if (hit_floor(position, type.radius)) {
			position[1] = -600.0f;
		}
	}

	void draw(void) {
		draw_bitmap(type.image, position, type.size);
	}

	float distance_to_bottomm(void) {
		return (position[1] - type.radius) - base;
	}

	void reset(void) {
		position[0] = start_point[0];
		position[1] = start_point[1];
		velocity[0] = -300.0f;
		velocity[1] = 0.0f;
	}

	bool collide(const float* collision_position,
		float collision_radius) {

			if (collision_position[0] > position[0] - type.size[0] &&
				collision_position[0] < position[0] + type.size[0] &&
				collision_position[1] > position[1] + type.size[1]) {

					set_player_platform(position[1] + type.size[1]);
			}

			return false;
	}
};

static object_array<platform_object>* spike_instances = 0;

object & load_platform_objects(void)
{

	static platform_object platforms[] = {
		point( 10.0f,   0.0f),
		point( 350.0f,  0.0f),  //left value directs side movement
		point( 700.0f,   0.0f), //plus value of right moves up the platform
		point( 1000.0f, 120.0f), //minus right value moves it down
		point( 1350.0f, -190.0f),
		point( 1700.0f, -170.0f),
		point( 2080.0f, -140.0f),
		point( 2470.0f, -90.0f),
		point( 2800.0f, -40.0f),
		point( 3150.0f,  0.0f),
		point( 3520.0f, 90.0f),
		point( 3900.0f, -90.0f),
		point( 3700.0f, -240.0f),
		point( 4220.0f, -40.0f),
		point( 4570.0f, 0.0f),
		point( 4870.0f, 60.0f),
		point( 5200.0f, 100.0f),
		point( 5400.0f, -100.0f),
		point( 5700.0f, 40.0f),
		point( 6100.0f, -100.0f),
		point( 6440.0f, 40.0f),
		point( 6840.0f, -110.0f),
		point( 7240.0f, -170.0f),
		point( 7540.0f, -20.0f),
		point( 7920.0f, 20.0f),
		point( 8320.0f, 80.0f),
		point( 8690.0f, 120.0f),
		point( 9080.0f, 160.0f),
		point( 9500.0f, -180.0f),
	};

	const int number_of_platforms =
		sizeof(platforms) / sizeof(platforms[0]);

	static object_array<platform_object> platform_array(&platforms[0],
		&platforms[number_of_platforms]);

	type.image = load_bitmap("Platform.bmp");
	type.size[0] = 150.0f;
	type.size[1] = 20.0f;

	spike_instances = &platform_array;

	static collection_object instance(platform_array);
	return instance;

}

static void copy_position(float* to, const float* from)
{
	to[0] = from[0];
	to[1] = from[1];
}

class collision_test : public test_function {
	float position[2];
	float radius;
public:
	collision_test(const float* collision_position, float
		collision_radius):
	radius(collision_radius) {

		copy_position(&position[0], collision_position);
	}
	bool test(object& instance) const {
		platform_object& platform =*((platform_object*)&instance);
		return platform.collide(position, radius);
	}
};

bool hit_floor(float* position, float radius)
{
	bool hit = false;
	if (spike_instances) {
		hit = spike_instances->find_object(
			collision_test(position, radius));
	}
	return hit;
}
