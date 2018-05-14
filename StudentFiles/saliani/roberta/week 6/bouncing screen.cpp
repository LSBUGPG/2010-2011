const int moving_spaceship = 2;

typedef struct spaceship_info     

{
    int xVel;
    int yVel;

}spaceship_info;

public:

	class moving_spaceship

int xVel = 1;
int yVel = 1;

X += xVel;
Y += yVel;

if(X < -240 || X > 240)
xVel *= -1;

if(Y < -320 || Y > 320)
yVel *= -1;

