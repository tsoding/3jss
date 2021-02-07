#ifndef THREEJSS_TILE_HPP_
#define THREEJSS_TILE_HPP_

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

#endif  // THREEJSS_TILE_HPP_
