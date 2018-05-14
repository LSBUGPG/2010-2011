#include "score.h"

#include "object.h"
#include "engine.h"
#include <stdio.h>

static int current_score = 0;
TTF_Font * font = 0;

class score_object: public object {
	float position[2];
	float size[2];
	int texture;
	bool created;

public:
	void reset(void) {
		position[0] = 300.0f;
		position[1] = 230.0f;
		if (created) {
			delete_bitmap(texture);
		}
		char buffer[] = "0000";
		sprintf_s(buffer, "%d", current_score);
		texture = load_text_line(font, buffer, size);
		created = true;
	}

	void update(float time) {
	}

	void draw(void) {
		if (created) {
			draw_bitmap(texture, position, size);
		}
	}
};

score_object * screen_score = 0;

object & load_score(void)
{
	font = load_font("LiberationMono-Regular.ttf", 20);
	static score_object instance;
	screen_score = &instance;
	return instance;
}

void set_score(int score)
{
	current_score = score;
	if (screen_score) {
		screen_score->reset();
	}
}

void add_score(int score)
{
	current_score += score;
	if (screen_score) {
		screen_score->reset();
	}
}
