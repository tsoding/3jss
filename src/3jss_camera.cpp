#include "./3jss_game.hpp"
#include "./3jss_camera.hpp"

void Camera::set_target(V2<float> target)
{
    vel = target - pos;
}

void Camera::update(Seconds dt)
{
    pos += vel * dt;
}

V2<float> Camera::to_screen(V2<float> point)
{
    return point - pos + game->window_size().cast_to<float>() * 0.5f;
}

Rect<float> Camera::to_screen(Rect<float> rect)
{
    return {to_screen(rect.pos), rect.size};
}

V2<float> Camera::to_world(V2<float> point)
{
    return point - game->window_size().cast_to<float>() * 0.5f + pos;
}

Rect<float> Camera::view_rect()
{
    const auto size = game->window_size().cast_to<float>();
    return Rect(pos - size * 0.5f, size);
}
