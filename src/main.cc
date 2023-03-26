#include <bits/stdc++.h>
#include <hittable.h>
#include <hittable_list.h>
#include <sphere.h>
#include <util.h>
#include <vec3.h>

#include <camera.h>
auto ray_color(const ray &r, const hittable &world) {
    hit_record rec;
    if (world.hit(r, 0, inf, rec))
        return 0.5 * (rec.normal + vec3(1, 1, 1));

    auto unit_dir = unit_vector(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    const int image_width = 200;
    const int image_height = 100;
    const int samples_per_pixel = 100;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    camera cam;

    hittable_list world;
    world.add(std::make_shared<sphere>(vec3{0, 0, -1}, 0.5));
    world.add(std::make_shared<sphere>(vec3{0, -100.5, -1}, 100));

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 color{0, 0, 0};
            for (int k = 0; k < samples_per_pixel; k++) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                auto r = cam.get_ray(u, v);
                color += ray_color(r, world);
            }
            color.write_color(std::cout, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}