#include "transform.hpp"

#include <math.h> 

Transform::Transform(double x, double y, int z) : x(x), y(y), z(z)
{
}

bool Transform::operator<(const Transform &other) const
{
    if (this->z == other.z)
    {
        return this->y < other.y;
    }
    else
    {
        return this->z < other.z;
    }
}



int Transform::ix() const
{
    return (int)round(x);
}

int Transform::iy() const
{
    return (int)round(y);
}

