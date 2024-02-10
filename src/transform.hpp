#pragma once

class Transform
{

public:
    Transform() = default;
    Transform(double x, double y, int z = 0);

    bool operator<(const Transform &other) const;

    int ix() const;
    int iy()const;

    double x = 0.0, y = 0.0;
    int z = 0.0;
private:
    
    
};