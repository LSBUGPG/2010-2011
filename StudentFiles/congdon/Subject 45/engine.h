struct _TTF_Font;
typedef _TTF_Font TTF_Font;

void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char * filename);
void delete_bitmap(int handle);
void start_render(void);
void end_render(void);
void draw_bitmap(int texture, const float * position, const float * size);
TTF_Font * load_font(const char * file_name);
int load_text_line(TTF_Font * font, const char * line, float * size);

struct point {
      float coordinate[2];
      point(float x, float y) {
           coordinate[0] = x;
           coordinate[1] = y;
      }
};
