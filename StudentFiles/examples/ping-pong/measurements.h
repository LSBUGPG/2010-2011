static const int screen_width = 640;  // in pixels
static const int screen_height = 480; // in pixels
static const float scale = 7.0f;      // 1 pixel maps to 7mm
static const float screen_bottom = -float(screen_height / 2)* scale;
static const float table_width = 1370.0f; // in mm
static const float table_height = 760.0f; // in mm
static const float net_height = 152.5f;   // in mm
static const float table_top = screen_bottom + table_height;
static const float coefficient_of_restitution = 0.9f;
static const float ball_radius = 40.0f;   // in mm
static const float gravity = 9810.0f;     // in mm per second per second
