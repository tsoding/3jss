#ifndef THREEJSS_TILE_HPP_
#define THREEJSS_TILE_HPP_

using Raw_Coord = V2<float>;
using Tile_Coord = V2<int>;

enum class Tile_Direction {
    Left,
    Right,
    Up,
    Down
};

Tile_Coord tile_dir(Tile_Direction dir)
{
    switch (dir) {
    case Tile_Direction::Left: return V2(-1, 0);
    case Tile_Direction::Right: return V2(1, 0);
    case Tile_Direction::Up: return V2(0, -1);
    case Tile_Direction::Down: return V2(0, 1);
    default: {
        assert(false && "tile_dir: unreachable");
    }
    }
}

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

#endif  // THREEJSS_TILE_HPP_
