#ifndef THREEJSS_CAMERA_HPP_
#define THREEJSS_CAMERA_HPP_

#include "./3jss_math.hpp"
#include "./3jss_config.hpp"

struct Camera
{
    V2<float> pos;
    V2<float> vel;

    void update(Seconds dt);
    V2<int> window_size();
    V2<float> to_screen(V2<float> point);
    Rect<float> to_screen(Rect<float> point);
    V2<float> to_world(V2<float> point);
    Rect<float> view_rect();
    void set_target(V2<float> target);
};

#endif  // THREEJSS_CAMERA_HPP_
