#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H

#include <vector>
#include <cstddef>

class Vector {
public:
    Vector(int x, int y);

    bool operator==(const Vector &rhs) const;
    bool operator!=(const Vector &rhs) const;
    Vector &operator+=(const Vector &rhs);

    int x() const;
    int y() const;

    Vector reflection() const;

private:
    int x_;
    int y_;
};

class Position {
public :
    Position(int x, int y);

    bool operator==(const Position &rhs) const;
    bool operator!=(const Position &rhs) const;
    Position &operator+=(const Vector &rhs);

    int x() const;
    int y() const;

    static const Position &origin();
    Position reflection() const;

private:
    int x_;
    int y_;
};

class Rectangle {
public:
    Rectangle(int width, int height, const Position &pos);
    Rectangle(int width, int height);

    bool operator==(const Rectangle &rhs) const;
    bool operator!=(const Rectangle &rhs) const;
    Rectangle &operator+=(const Vector &rhs);

    int width() const;
    int height() const;
    const Position &pos() const;

    Rectangle reflection() const;
    int area() const;

    std::pair<Rectangle, Rectangle> split_horizontally(int place);
    std::pair<Rectangle, Rectangle> split_vertically(int place);

private:
    int width_;
    int height_;
    Position position_;
};

class Rectangles {
public:
    Rectangles();
    Rectangles(const std::initializer_list<Rectangle> &rectangles);
    Rectangles(const Rectangles &other);
    Rectangles(Rectangles &&other);

    bool operator==(const Rectangles &rhs) const;
    bool operator!=(const Rectangles &rhs) const;
    Rectangles &operator+=(const Vector &rhs);
    Rectangle &operator[](size_t index);

    size_t size() const;

    Rectangles &split_horizontally(size_t idx, int place);
    Rectangles &split_vertically(size_t idx, int place);

private:
    std::vector<Rectangle> rectangles_;

    Rectangles &split(size_t idx, int place, bool horizontal);
};

Position operator+(const Position &lhs, const Vector &rhs);
Position operator+(const Vector &lhs, const Position &rhs);

Vector operator+(const Vector &lhs, const Vector &rhs);

Rectangle operator+(const Rectangle &lhs, const Vector &rhs);
Rectangle operator+(const Vector &lhs, const Rectangle &rhs);

Rectangles operator+(const Rectangles &lhs, const Vector &rhs);
Rectangles operator+(Rectangles &&lhs, const Vector &rhs);
Rectangles operator+(const Vector &lhs, const Rectangles &rhs);
Rectangles operator+(const Vector &lhs, Rectangles &&rhs);

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);
Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

#endif //GEOMETRY_GEOMETRY_H
