#include "../raycaster.h"

void    checkHorizontalLines()
{
    rays.dept_of_field = 0;
    rays.distH = 10000000;
    float	tangent = 1/tan(degToRad(rays.ray_angle));
    //	looking up
    if (sin(degToRad(rays.ray_angle) > 0.001))
    {
        rays.ray_y = (((int)player.y>>6)<<6) - 0.0001;
        rays.ray_x = (player.y - rays.ray_y) * tangent + player.x;
        rays.yo = -64;
        rays.xo = -rays.yo * tangent;
    }
    //	looking down
    else if (sin(degToRad(rays.ray_angle)) < -0.001)
    {
        rays.ray_y = (((int)player.y>>6)<<6) + 64;
        rays.ray_x = (player.y - rays.ray_y) * tangent + player.x;
        rays.yo = 64;
        rays.xo = -rays.yo * tangent;
    }
    //	looking left or right
    else
    {
        rays.ray_x = player.x;
        rays.ray_y = player.y;
        rays.dept_of_field = 8;
    }
    while (rays.dept_of_field < 8)
    {
        rays.map_x = (int)(rays.ray_x)>>6;
        rays.map_y = (int)(rays.ray_y)>>6;
        rays.map_pos = rays.map_y * map.x + rays.map_x;
        if (rays.map_pos > 0 && rays.map_pos < map.x * map.y && map.map_str[rays.map_pos] == '1')
        {
            rays.distH = cos(degToRad(rays.ray_angle)) * (rays.ray_x - player.x) - sin(degToRad(rays.ray_angle)) * (rays.ray_y - player.y);
            rays.dept_of_field = 8;
        }
        else
        {
            rays.ray_x += rays.xo;
            rays.ray_y += rays.yo;
            rays.dept_of_field += 1;
        }
    }
}

void    checkVerticalLines()
{
    rays.dept_of_field = 0;
    rays.distV = 10000000;

    float   tangent = tan(degToRad(rays.ray_angle));
    //	looking left
    if (cos(degToRad(rays.ray_angle)) > 0.001)
    {
        rays.ray_x = (((int)player.x>>6)<<6) + 64;
        rays.ray_y = (player.x - rays.ray_x) * tangent + player.y;
        rays.xo = 64;
        rays.yo = -rays.xo * tangent;
    }
    //	looking right
    else if (cos(degToRad(rays.ray_angle)) < -0.001)
    {
        rays.ray_x = (((int)player.x>>6)<<6) -0.0001;
        rays.ray_y = (player.x - rays.ray_x) * tangent + player.y;
        rays.xo = -64;
        rays.yo = -rays.xo * tangent;
    }
    //	looking up or down
    else
    {
        rays.ray_x = player.x;
        rays.ray_y = player.y;
        rays.dept_of_field = 8;
    }
    while (rays.dept_of_field < 8)
    {
        rays.map_x = (int)(rays.ray_x)>>6;
        rays.map_y = (int)(rays.ray_y)>>6;
        rays.map_pos = rays.map_y * map.x + rays.map_x;
        if (rays.map_pos > 0 && rays.map_pos < map.x * map.y && map.map_str[rays.map_pos] == '1')
        {
            rays.distV = (cos(degToRad(rays.ray_angle)) * (rays.ray_x - player.x)) - (sin(degToRad(rays.ray_angle)) * (rays.ray_y - player.y));
            rays.dept_of_field = 8;
        }
        else
        {
            rays.ray_x += rays.xo;
            rays.ray_y += rays.yo;
            rays.dept_of_field += 1;
        }
    }
    rays.vx = rays.ray_x;
    rays.vy = rays.ray_y;
}

void    checkDistance()
{
    if (rays.distV < rays.distH)
    {
        rays.ray_x = rays.vx;
        rays.ray_y = rays.vy;
        rays.dist = rays.distV;
        glColor3f(0.9, 0, 0);
    }
    if (rays.distH < rays.distV)
    {
        rays.ray_x = rays.hx;
        rays.ray_y = rays.hy;
        rays.dist = rays.distH;
        glColor3f(0.7, 0, 0);
    }
}
