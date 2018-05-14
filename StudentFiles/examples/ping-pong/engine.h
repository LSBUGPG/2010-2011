void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char* filename);
void draw_bitmap(int texture, const float* position, float radius);
void draw_bitmap(int texture, const float* position, const float* size);
void start_render();
void end_render();

