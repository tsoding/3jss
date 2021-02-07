#ifndef THREEJSS_MATH_HPP_
#define THREEJSS_MATH_HPP_

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

#endif  // THREEJSS_MATH_HPP_
