
#ifndef __COLOR_H__
#define __COLOR_H__

#include "vec3.h"

#include <iostream>

inline void write_color(std::ostream &out, color &&pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif