#include "object.h"
#include "engine.h"

#include <stdio.h>

TTF_Font * font = 0;

class timer: public object {
     float position[2];
     float size[2];
	 int texture;
	 bool created;
	 float count;

public:
     timer(void): created(false) {
     }
     void reset(void) {
		 count = 30.0f;
		 position[0] = 305.0f;
		 position[1] = 225.0f;
     }
     void update(float time) {
		 count -= time;
		 if (created) {
			 delete_bitmap(texture);
		 }
		 char time_string[] = "00";
		 sprintf_s(time_string, "%d", (int)count);
		 texture = load_text_line(font, time_string, size);
		 created = true;
     }
     void draw(void) {
		 if (created) {
			draw_bitmap(texture, position, size);
		 }
     }
};

object & load_timer_object(void)
{
	font = load_font("LiberationMono-Regular.ttf", 18);
	static timer instance;
	return instance;
}

