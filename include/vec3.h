#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

#include "common.h"

class vec3
{
public:
    vec3() : m_data{0.0f, 0.0f, 0.0f} {}
    vec3(double x, double y, double z) : m_data{x, y, z} {}

    double x() const
    {
        return m_data[0];
    }
    double y() const
    {
        return m_data[1];
    }
    double z() const
    {
        return m_data[2];
    }

    // TODO : huh??
    vec3 operator-() const
    {
        return vec3(-m_data[0], -m_data[1], -m_data[2]);
    }

    double &operator[](int i)
    {
        return m_data[i];
    }

    vec3 &operator+=(const vec3 &rhs)
    {
        this->m_data[0] = this->x() + rhs.x();
        this->m_data[1] = this->y() + rhs.y();
        this->m_data[2] = this->z() + rhs.z();
        return *this;
    }

    vec3 &operator-=(const vec3 &rhs)
    {
        return *this += (-rhs);
    }

    vec3 &operator*=(const double &rhs)
    {
        this->m_data[0] = this->x() * rhs;
        this->m_data[1] = this->y() * rhs;
        this->m_data[2] = this->z() * rhs;
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
        return m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2];
    }

    vec3 &normalize()
    {
        return (*this) /= (*this).length();
    }

    inline static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

private:
    double m_data[3];
};

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3 &op1, const vec3 &op2)
{
    return vec3(op1.x() + op2.x(), op1.y() + op2.y(), op1.z() + op2.z());
}

inline vec3 operator-(const vec3 &op1, const vec3 &op2)
{
    return vec3(op1.x() - op2.x(), op1.y() - op2.y(), op1.z() - op2.z());
}

inline vec3 operator*(const vec3 &op1, const vec3 &op2)
{
    return vec3(op1.x() * op2.x(), op1.y() * op2.y(), op1.z() * op2.z());
}

inline vec3 operator*(double scale, const vec3 &op2)
{
    return vec3(scale * op2.x(), scale * op2.y(), scale * op2.z());
}

inline vec3 operator*(const vec3 &op1, double scale)
{
    return scale * op1;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vec3 &v1, const vec3 &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline vec3 unit_vector(const vec3 &v)
{
    return v / v.length();
}

inline vec3 random_inside_unit_sphere()
{
    // TODO : Ew
    while (true)
    {
        vec3 random_point = vec3::random(-1, 1);
        // outside unit circle
        if (random_point.length_squared() > 1)
            continue;
        return random_point;
    }
}

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3;  // RGB color

#endif