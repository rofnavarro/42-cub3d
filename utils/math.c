#include    "../raycaster.h"

int fixAngle(int x)
{
    if (x > 359)
        x -= 360;
    if (x < 0)
        x += 360;
    return (x);
}

float   degToRad(int x)
{
    return (x * M_PI / 180.0);
}
