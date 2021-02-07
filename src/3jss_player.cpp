#include "./3jss_player.hpp"

Raw_Coord Player::raw_center()
{
    switch (state) {
    case State::Idle:
        return center_of_tile(tile);

    case State::Sliding:
        return lerp(tile_to_raw(tile),
                    tile_to_raw(sliding.target),
                    sliding.a) + V2(TILE_SIZE, TILE_SIZE) * 0.5f;

    default:
        assert(false && "Player::raw()");
    }
}

void Player::render()
{
    switch (state) {
    case State::Idle:
        fill_rect(
            game->renderer,
            game->camera.to_screen(rect_of_tile(tile)),
            PLAYER_COLOR);
        break;

    case State::Sliding:
        fill_rect(
            game->renderer,
            game->camera.to_screen(
                Rect(lerp(tile_to_raw(tile),
                          tile_to_raw(sliding.target),
                          sliding.a),
                     V2(TILE_SIZE, TILE_SIZE))),
            PLAYER_COLOR);
        break;

    default:
        assert(false && "Player::render: unreachable");
    }
}

void Player::update(Seconds dt)
{
    if (state == State::Sliding) {
        sliding.a += dt * PLAYER_SLIDING_SPEED;
        if (sliding.a >= 1.0) {
            tile = sliding.target;

            if (step_buffer.empty()) {
                state = State::Idle;
            } else {
                sliding.a = 0.0;
                sliding.target = tile + tile_dir(step_buffer.dq());
            }
        }
    }
}

void Player::step_to(Tile_Direction dir)
{
    switch (state) {
    case State::Idle: {
        state = State::Sliding;
        sliding.target = tile + tile_dir(dir);
        sliding.a = 0;
    } break;

    case State::Sliding: {
        step_buffer.nq(dir);
    } break;
    }
}
