#ifndef GAME_HPP_
#define GAME_HPP_

#include "./3jss_camera.hpp"
#include "./3jss_player.hpp"
#include "./3jss_config.hpp"

struct Game
{
    bool quit;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera camera;
    Player player;

    void render_background();
    void render();
    void update(Seconds dt);
    void handle_event(SDL_Event *event);
    V2<int> window_size();
};

Game *game = nullptr;

#endif  // GAME_HPP_
