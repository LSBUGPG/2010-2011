#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>
#include <conio.h>

GLubyte white[3] = { 255, 255, 255 };

struct sound_key_definition {
	const char * image;
	const char * prompt;
	const char * audio;
	SDLKey keycode;
	GLfloat position[2];
};

struct sound_key_instance {
	GLuint image;
	GLuint prompt;
	Mix_Chunk * audio;
	bool held;
};

const sound_key_definition definition[] = {	
	{
		"face.bmp",
		"letter_f.bmp",
		"hello.wav",
		SDLK_f,
		{ -100.0f, 16.0f } 
	}, {
		"french.bmp",
		"letter_h.bmp", 
		"salut.wav",
		SDLK_h,
		{ 100.0f, 16.0f } 
	}
};

const int key_count = sizeof(definition) / sizeof(sound_key_definition);

sound_key_instance instance[key_count];


void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym * key, bool held)
{
    if (key->sym == SDLK_ESCAPE) {
        quit(0);
	} else {
		for (int i = 0; i < key_count; i++) {
			if (key->sym == definition[i].keycode) {
				if (!instance[i].held && held && instance[i].audio) {
					const int auto_channel = -1;
					const int no_loop = 0;
					const int play_to_end = -1;

					Mix_PlayChannelTimed(
						auto_channel, 
						instance[i].audio, 
						no_loop, 
						play_to_end);
				}
				instance[i].held = held;
			}
		}
	}
}

void process_events(void)
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
        case SDL_KEYDOWN:
            handle_key(&evnt.key.keysym, true);
            break;
		case SDL_KEYUP:
            handle_key(&evnt.key.keysym, false);
			break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

void start_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void send_vertex(const GLfloat * texture_coordinates, const GLfloat * position)
{
	glTexCoord2fv(texture_coordinates); 
	glVertex2fv(position);
}

void draw_bitmap(GLuint texture, const GLfloat * position, GLfloat size)
{
	const GLfloat quad[4][2] = {
		{ position[0] - size, position[1] + size },
		{ position[0] + size, position[1] + size },
		{ position[0] + size, position[1] - size },
		{ position[0] - size, position[1] - size }
	};

	const GLfloat texture_coordinates[4][2] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f }
	};

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glColor3ubv(white);

	send_vertex(texture_coordinates[0], quad[0]);
	send_vertex(texture_coordinates[1], quad[1]);
	send_vertex(texture_coordinates[2], quad[2]);

	send_vertex(texture_coordinates[2], quad[2]);
	send_vertex(texture_coordinates[3], quad[3]);
	send_vertex(texture_coordinates[0], quad[0]);

    glEnd();
}

void draw(const sound_key_definition & source, const sound_key_instance & data)
{
	const GLfloat normal_size = 50.0f;
	const GLfloat zoom_size = 60.0f;
	const GLfloat prompt_size = 16.0f;

	GLfloat size;
	if (data.held) {
		size = zoom_size;
	} else {
		size = normal_size;
	}

	draw_bitmap(data.image, source.position, size);

	GLfloat prompt_position[2] = { 
		source.position[0] - zoom_size, 
		source.position[1] - (zoom_size + prompt_size) 
	};

	size = prompt_size;

	draw_bitmap(data.prompt, prompt_position, size);
}

void end_render(void)
{
    SDL_GL_SwapBuffers();
}

void setup_opengl(GLdouble width, GLdouble height)
{
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	const GLdouble left = -width / 2.0;
	const GLdouble right = width / 2.0;
	const GLdouble top = height / 2.0;
	const GLdouble bottom = -height / 2.0;
	const GLdouble front = 0.0;
	const GLdouble back = 100.0;

	glOrtho(left, right, bottom, top, front, back);

	glEnable(GL_TEXTURE_2D);
}

void load_bitmap(const char * bitmap_filename)
{
	SDL_Surface * surface = SDL_LoadBMP(bitmap_filename);
	if (surface) {
		const GLint mipmap_level = 0;
		const GLint no_border = 0;
		
		glTexImage2D(
			GL_TEXTURE_2D,
			mipmap_level,
			GL_RGB8,
			surface->w,
			surface->h,
			no_border,
			GL_BGR_EXT,
			GL_UNSIGNED_BYTE,
			surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(surface);
	} else {
		_cprintf("Failed to load bitmap file: %s\n", bitmap_filename);
	}
}

void load(const sound_key_definition & source, sound_key_instance & data)
{
	glGenTextures(1, &data.image);
	glGenTextures(1, &data.prompt);

	glBindTexture(GL_TEXTURE_2D, data.image);
	load_bitmap(source.image);

	glBindTexture(GL_TEXTURE_2D, data.prompt);load_bitmap(source.prompt);

	data.audio = Mix_LoadWAV(source.audio);
	if (!data.audio) {
		_cprintf("Failed to load audio file: %s\n", source.audio);
	}
}

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		_cprintf("Video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	const int frequency = 44100;
	const int stereo = 2;
	const int buffer_size = 1024;

	if (Mix_OpenAudio(frequency, AUDIO_S16, stereo, buffer_size)) {
		_cputs("Unable to open audio!\n");
		quit(1);
	}

	const SDL_VideoInfo * info = SDL_GetVideoInfo();
    if (!info) {
		_cprintf("Video query failed: %s\n", SDL_GetError());
        quit(1);
    }

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	int width = 640;
    int height = 480;
    int bpp = info->vfmt->BitsPerPixel;
	Uint32 flags = SDL_OPENGL;

	if (SDL_SetVideoMode(width, height, bpp, flags) == 0) {
		_cprintf("Video mode set failed: %s\n", SDL_GetError());
        quit(1);
    }

	setup_opengl(GLdouble(width), GLdouble(height));

	int i = 0;
	for (i = 0; i < key_count; i++) {
		load(definition[i], instance[i]);
	}

	while (true) {
		process_events();
		start_render();
		for (i = 0; i < key_count; i++) {
			draw(definition[i], instance[i]);
		}
		end_render();
    }

	return 0;
}
