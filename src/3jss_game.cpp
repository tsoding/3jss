#include "./3jss_game.hpp"
#include "./3jss_sdl.hpp"

void Game::render_background()
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

void Game::render()
{
    sec(SDL_SetRenderDrawColor(renderer, UNPACK_HEX_COLOR(BACKGROUND_COLOR)));
    sec(SDL_RenderClear(renderer));

    render_background();
    player.render();

    SDL_RenderPresent(renderer);
}

void Game::update(Seconds dt)
{
    camera.set_target(player.raw_center());
    camera.update(dt);

    player.update(dt);
}

void Game::handle_event(SDL_Event *event)
{
    switch (event->type) {
    case SDL_QUIT: {
        quit = true;
    } break;

    case SDL_KEYDOWN: {
        switch (event->key.keysym.sym) {
        case SDLK_w:
            player.step_to(Tile_Direction::Up);
            break;

        case SDLK_s:
            player.step_to(Tile_Direction::Down);
            break;

        case SDLK_d:
            player.step_to(Tile_Direction::Right);
            break;

        case SDLK_a:
            player.step_to(Tile_Direction::Left);
            break;
        }
    } break;
    }
}

V2<int> Game::window_size()
{
    return {SCREEN_WIDTH, SCREEN_HEIGHT};
}
