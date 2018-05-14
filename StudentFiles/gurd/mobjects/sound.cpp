#include "object.h"
#include "engine.h"

static Mix_Chunk * loop = NULL;

class sound_instance: public object {
public:
	void draw(void)
	{
	}

	void reset(void)
	{
		play_audio(loop);
	}

	void update(float time)
	{
	}
};

object * load_sound_object(const char * audio)
{
	loop = load_audio(audio);

	static sound_instance instance;
	return &instance;
}
