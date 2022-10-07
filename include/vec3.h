#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3
{
public:
    vec3() : data{0.0f, 0.0f, 0.0f} {}
    vec3(double x, double y, double z) : data{x, y, z} {}

    double x() const
    {
        return data[0];
    }
    double y() const
    {
        return data[1];
    }
    double z() const
    {
        return data[2];
    }

    // TODO : huh??
    vec3 operator-() const
    {
        return vec3(-data[0], -data[1], -data[2]);
    }

    double &operator[](int i)
    {
        return data[i];
    }

    vec3 &operator+=(const vec3 &rhs)
    {
        this->data[0] = this->x() + rhs.x();
        this->data[1] = this->y() + rhs.y();
        this->data[2] = this->z() + rhs.z();
        return *this;
    }

    vec3 &operator-=(const vec3 &rhs)
    {
        return *this += (-rhs);
    }

    vec3 &operator*=(const double &rhs)
    {
        this->data[0] = this->x() * rhs;
        this->data[1] = this->y() * rhs;
        this->data[2] = this->z() * rhs;
        return *this;
    }

    vec3 &operator/=(const double &rhs)
    {
        return *this *= 1 / rhs;
    }

    double length() const
    {
        return std ::sqrt(length_squared());
    }

    double length_squared() const
    {
        return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
    }

private:
    double data[3];
};

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

#endif