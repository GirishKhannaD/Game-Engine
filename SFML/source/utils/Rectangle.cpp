#include "../../include/utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    //Implement this function, that returns true if the point <x,y> is inside this rectangle.
    return (x >= topLeft.x && x <= bottomRight.x) &&
           (y >= topLeft.y && y <= bottomRight.y);

    return false; 
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    //Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
    return !(bottomRight.x < rect.topLeft.x ||  // Left side check
             topLeft.x > rect.bottomRight.x ||  // Right side check
             bottomRight.y < rect.topLeft.y ||  // Top side check
             topLeft.y > rect.bottomRight.y);   // Bottom side check

    return false;
}

