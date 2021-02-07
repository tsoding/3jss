#include <SDL.h>
#include "./aids.hpp"

using namespace aids;

using Seconds = float;
using Milliseconds = Uint32;
using Hex_Color = Uint32;

#define UNPACK_HEX_COLOR(color)                 \
    (color >> (8 * 3)) & 0xFF,                  \
        (color >> (8 * 2)) & 0xFF,              \
        (color >> (8 * 1)) & 0xFF,              \
        (color >> (8 * 0)) & 0xFF

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;

const Seconds UPDATE_DELTA_TIME_SECS = 1.0 / static_cast<float>(SCREEN_FPS);
const Milliseconds UPDATE_DELTA_TIME_MS = static_cast<Milliseconds>(UPDATE_DELTA_TIME_SECS * 1000);

const Hex_Color BACKGROUND_COLOR = 0x181818FF;
const Hex_Color RED = 0xFF0000FF;
const Hex_Color PLAYER_COLOR = 0xF5E148FF;
const Hex_Color BACKGROUND_COLOR_1 = 0x133133FF;
const Hex_Color BACKGROUND_COLOR_2 = 0x1F2832FF;

Hex_Color colors[] = {
    0xF5E148FF,
    0xE5B457FF,
    0x2E2B2AFF,
    0x133133FF,
    0x1F2832FF
};
constexpr size_t colors_size = sizeof(colors) / sizeof(colors[0]);

const float TILE_SIZE = 69.0;

template <typename T>
struct V2
{
    T x, y;

    V2() = default;

    V2(T x, T y):
        x(x), y(y)
    {}

    template <typename U>
    V2<U> cast_to()
    {
        return {static_cast<U>(x), static_cast<U>(y)};
    }

    template <typename U>
    V2<U> map(U (*f)(T))
    {
        return {f(x), f(y)};
    }
};

template <typename T>
V2<T> operator+(V2<T> a, V2<T> b)
{
    return {a.x + b.x, a.y + b.y};
}

template <typename T>
V2<T> &operator+=(V2<T> &a, V2<T> b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

template <typename T>
V2<T> operator-(V2<T> a, V2<T> b)
{
    return {a.x - b.x, a.y - b.y};
}

template <typename T>
V2<T> operator*(V2<T> a, T s)
{
    return {a.x * s, a.y * s};
}

template <typename T>
V2<T> operator*(T s, V2<T> a)
{
    return {a.x * s, a.y * s};
}

template <typename T>
V2<T> operator/(V2<T> a, T s)
{
    return {a.x / s, a.y / s};
}

float length(V2<float> a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

double length(V2<double> a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

template <typename T, typename U>
V2<U> normalize(V2<T> a)
{
    auto b = a.template cast_to<U>();
    auto l = length(b);
    return V2(b.x / l, b.y / l);
}

template <typename T>
struct Rect
{
    V2<T> pos;
    V2<T> size;

    Rect(V2<T> pos, V2<T> size):
        pos(pos), size(size)
    {}

    template <typename U>
    Rect<U> map(U (*f)(T))
    {
        return {pos.map(f), size.map(f)};
    }

    template <typename U>
    Rect<U> cast_to()
    {
        return {pos.template cast_to<U>(), size.template cast_to<U>()};
    }
};

int sec(int code)
{
    if (code < 0) {
        panic("SDL ERROR: ", SDL_GetError());
    }

    return code;
}

template <typename T>
T *sec(T *ptr)
{
    if (ptr == nullptr) {
        panic("SDL ERROR: ", SDL_GetError());
    }

    return ptr;
}

struct Game;
struct Camera;

Game *game = nullptr;

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

using Tile_Coord = V2<int>;
using Raw_Coord = V2<float>;

Tile_Coord raw_to_tile(Raw_Coord pos)
{
    return (pos / TILE_SIZE).map(floorf).cast_to<int>();
}

Raw_Coord tile_to_raw(Tile_Coord pos)
{
    return pos.cast_to<float>() * TILE_SIZE;
}

Rect<float> rect_of_tile(Tile_Coord tile)
{
    const auto pos = tile_to_raw(tile);
    const auto size = V2(TILE_SIZE, TILE_SIZE);
    return {pos, size};
}

V2<float> center_of_tile(Tile_Coord tile)
{
    const auto pos = tile_to_raw(tile);
    return pos + V2(TILE_SIZE, TILE_SIZE) * 0.5f;
}

SDL_Rect rect_for_sdl(Rect<int> rect)
{
    return {rect.pos.x, rect.pos.y, rect.size.x, rect.size.y};
}

void fill_rect(SDL_Renderer *renderer, Rect<float> rect, Hex_Color color)
{
    const SDL_Rect sdl_rect = rect_for_sdl(rect.map(floorf).cast_to<int>());
    sec(SDL_SetRenderDrawColor(renderer, UNPACK_HEX_COLOR(color)));
    sec(SDL_RenderFillRect(renderer, &sdl_rect));
}

struct Player
{
    Tile_Coord tile;

    void render();
};

struct Game
{
    bool quit;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera camera;
    Player player;

    void render_background()
    {
        const auto rect = camera.view_rect();
        const auto a = raw_to_tile(rect.pos);
        const auto b = raw_to_tile(rect.pos + rect.size);

        for (int x = a.x; x <= b.x; ++x) {
            for (int y = a.y; y <= b.y; ++y) {
                const Hex_Color color = (abs(x) + abs(y)) % 2 == 0 ? BACKGROUND_COLOR_1 : BACKGROUND_COLOR_2;
                fill_rect(
                        renderer,
                        camera.to_screen(rect_of_tile(V2(x, y))),
                        color);
            }
        }
    }

    void render()
    {
        sec(SDL_SetRenderDrawColor(renderer, UNPACK_HEX_COLOR(BACKGROUND_COLOR)));
        sec(SDL_RenderClear(renderer));

        render_background();
        player.render();

        SDL_RenderPresent(renderer);
    }

    void update(Seconds dt)
    {
        camera.set_target(center_of_tile(player.tile));
        camera.update(dt);
    }

    void handle_event(SDL_Event *event)
    {
        switch (event->type) {
        case SDL_QUIT: {
            quit = true;
        } break;

        case SDL_KEYDOWN: {
            switch (event->key.keysym.sym) {
            case SDLK_w:
                player.tile += V2(0, -1);
                break;

            case SDLK_s:
                player.tile += V2(0, 1);
                break;

            case SDLK_d:
                player.tile += V2(1, 0);
                break;

            case SDLK_a:
                player.tile += V2(-1, 0);
                break;
            }
        } break;
        }
    }

    V2<int> window_size()
    {
        return {SCREEN_WIDTH, SCREEN_HEIGHT};
    }
};

void Player::render()
{
    fill_rect(
        game->renderer,
        game->camera.to_screen(rect_of_tile(tile)),
        PLAYER_COLOR);
}

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

int main(void)
{
    game = new Game{};

    sec(SDL_Init(SDL_INIT_VIDEO));

    game->window =
        sec(SDL_CreateWindow(
                "3jss",
                0, 0,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_RESIZABLE));

    game->renderer =
        sec(SDL_CreateRenderer(
                game->window, -1,
                SDL_RENDERER_ACCELERATED));

    sec(SDL_RenderSetLogicalSize(game->renderer,
                SCREEN_WIDTH,
                SCREEN_HEIGHT));

    while (!game->quit) {
        SDL_Event event = {};
        while (SDL_PollEvent(&event)) {
            game->handle_event(&event);
        }

        game->update(UPDATE_DELTA_TIME_SECS);
        game->render();

        SDL_Delay(UPDATE_DELTA_TIME_MS);
    }

    SDL_Quit();

    return 0;
}
