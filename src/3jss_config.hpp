#ifndef THREEJSS_CONFIG_HPP_
#define THREEJSS_CONFIG_HPP_

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
const Hex_Color BACKGROUND_COLOR_1 = 0x133133FF;
const Hex_Color BACKGROUND_COLOR_2 = 0x1F2832FF;

const Hex_Color PLAYER_COLOR = 0xF5E148FF;
const float PLAYER_SLIDING_SPEED = 8.0;
const size_t PLAYER_STEP_BUFFER_SIZE = 3;

const float TILE_SIZE = 69.0;

const size_t CHUNK_SIZE = 4;

Hex_Color colors[] = {
    0xF5E148FF,
    0xE5B457FF,
    0x2E2B2AFF,
    0x133133FF,
    0x1F2832FF
};
constexpr size_t colors_size = sizeof(colors) / sizeof(colors[0]);

#endif  // THREEJSS_CONFIG_HPP_
