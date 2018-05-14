class shot_instance;

class collection_object& load_shots(const char* image, const char* audio,
                                               float radius);
void fire_shot(const float* position, float heading);
void expire_shot(shot_instance& shot);
