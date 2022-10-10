#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color, int sample_per_pixel)
{
    pixel_color /= sample_per_pixel;
    double r = sqrt(pixel_color.x());
    double g = sqrt(pixel_color.y());
    double b = sqrt(pixel_color.z());

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * clamp(r, 0.0f, 0.999f)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0f, 0.999f)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0f, 0.999f)) << '\n';
}

#endif