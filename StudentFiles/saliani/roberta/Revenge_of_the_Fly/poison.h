class poison_instance;

class collection_object & load_poisons(const char * image, const char * audio,
                                               float radius);
void fire_poison(const float * position, float heading);
void expire_poison(poison_instance & poison);
