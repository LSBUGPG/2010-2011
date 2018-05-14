#include "object.h"

class reset_object_function: public object_function {
public:
	void call(object & instance) 
	{ 
		instance.reset(); 
	}
};

class update_object_function: public object_function {
	float time;
public:
	update_object_function(float elapsed_time): time(elapsed_time) 
	{
	}

	void call(object & instance) 
	{ 
		instance.update(time); 
	}
};

class draw_object_function: public object_function {
public:
	void call(object & instance) 
	{ 
		instance.draw(); 
	}
};

void object_collection::reset(void)
{
	reset_object_function reset_object;
	for_each_object(reset_object);                                 
}

void object_collection::update(float time)
{
	update_object_function update_object(time);
	for_each_object(update_object);
}

void object_collection::draw(void)
{
	draw_object_function draw_object;
	for_each_object(draw_object);
}
