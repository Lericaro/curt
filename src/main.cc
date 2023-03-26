#include <bits/stdc++.h>
#include <camera.h>
#include <hittable.h>
#include <hittable_list.h>
#include <material.h>
#include <ray.h>
#include <sphere.h>
#include <util.h>
#include <vec3.h>
auto ray_color(const ray &r, const hittable &world, int depth) {
    if (depth <= 0)
        return vec3(0, 0, 0);
    // hit_record rec;
    // if (world.hit(r, 0, inf, rec)) {
    //     auto target = rec.p + rec.normal + random_in_unit_sphere();
    //     return 0.5 * ray_color(ray(rec.p, target - rec.p), world);
    // }
    // return 0.5 * (rec.normal + vec3(1, 1, 1));

    hit_record rec;
    if (world.hit(r, 0.001, inf, rec)) {
        // auto target = rec.p + rec.normal + random_unit_vector();

        ray scattered;
        vec3 attenuation;

        if (rec.pmaterial->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return vec3(0, 0, 0);

        // auto target = rec.p + random_in_hemisphere(rec.normal);
        // return 0.5 * ray_color(ray{rec.p, target - rec.p}, world, depth - 1);
    }

    auto unit_dir = unit_vector(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
    hittable_list world;

    world.add(std::make_shared<sphere>(
        vec3(0, -1000, 0), 1000,
        std::make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9 * random_double(), 0.2,
                        b + 0.9 * random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    world.add(std::make_shared<sphere>(
                        center, 0.2, std::make_shared<lambertian>(albedo)));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(std::make_shared<sphere>(
                        center, 0.2, std::make_shared<metal>(albedo, fuzz)));
                } else {
                    // glass
                    world.add(std::make_shared<sphere>(
                        center, 0.2, std::make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    world.add(std::make_shared<sphere>(vec3(0, 1, 0), 1.0,
                                       std::make_shared<dielectric>(1.5)));

    world.add(std::make_shared<sphere>(
        vec3(-4, 1, 0), 1.0,
        std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

    world.add(std::make_shared<sphere>(
        vec3(4, 1, 0), 1.0, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return world;
}

int main() {
    constexpr double aspect_ratio = 9.0 / 16;
    const int image_width = 640;
    const int image_height = image_width * aspect_ratio;
    const int samples_per_pixel = 50;

    const int maxn_depth = 50;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // vec3 lower_left_corner(-2.0, -1.0, -1.0);
    // vec3 horizontal(4.0, 0.0, 0.0);
    // vec3 vertical(0.0, 2.0, 0.0);
    // vec3 origin(0.0, 0.0, 0.0);

    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,
               dist_to_focus);

    // const auto aspect_ratio = 9.0 / 16j;
    // camera cam(vec3{-2, 2, 1}, vec3{0, 0, -1}, vup, 90, aspect_ratio);

    auto world = random_scene();

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 color{0, 0, 0};
            for (int k = 0; k < samples_per_pixel; k++) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                auto r = cam.get_ray(u, v);
                color += ray_color(r, world, maxn_depth);
            }
            color.write_color(std::cout, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}