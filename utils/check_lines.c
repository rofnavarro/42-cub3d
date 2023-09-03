#include "../raycaster.h"

void    checkHorizontalLines()
{
    rays.dept_of_field = 0;
    rays.distH = 10000000;
    float	hx = player.x;
    float	hy = player.y;
    float	hTan = -1/tan(rays.ray_angle);
    //	looking down
    if (rays.ray_angle > PI)
    {
        rays.ray_y = (((int)player.y>>6)<<6) - 0.0001;
        rays.ray_x = (player.y - rays.ray_y) * hTan + player.x;
        rays.yo = -64;
        rays.xo = -rays.yo * hTan;
    }
    //	looking up
    if (rays.ray_angle < PI)
    {
        rays.ray_y = (((int)player.y>>6)<<6) + 64;
        rays.ray_x = (player.y - rays.ray_y) * hTan + player.x;
        rays.yo = 64;
        rays.xo = -rays.yo * hTan;
    }
    //	looking left or right
    if (rays.ray_angle == 0 || rays.ray_angle == PI)
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
            hx = rays.ray_x;
            hy = rays.ray_y;
            rays.distH = distance(player.x, player.y, hx, hy, rays.ray_angle);
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
    float	vx = player.x;
    float	vy = player.y;
    float	vTan = -tan(rays.ray_angle);
    //	looking left
    if (rays.ray_angle > P2 && rays.ray_angle < P3)
    {
        rays.ray_x = (((int)player.x>>6)<<6) - 0.0001;
        rays.ray_y = (player.x - rays.ray_x) * vTan + player.y;
        rays.xo = -64;
        rays.yo = -rays.xo * vTan;
    }
    //	looking right
    if (rays.ray_angle < P2 || rays.ray_angle > P3)
    {
        rays.ray_x = (((int)player.x>>6)<<6) + 64;
        rays.ray_y = (player.x - rays.ray_x) * vTan + player.y;
        rays.xo = 64;
        rays.yo = -rays.xo * vTan;
    }
    //	looking up or down
    if (rays.ray_angle == 0 || rays.ray_angle == PI)
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
            vx = rays.ray_x;
            vy = rays.ray_y;
            rays.distV = distance(player.x, player.y, vx, vy, rays.ray_angle);
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
