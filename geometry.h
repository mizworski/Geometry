#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H

#include <utility>
#include <vector>
#include <cstddef>

class Position {
public :
    Position(int x, int y);

    bool operator==(const Position &rhs);
    bool operator!=(const Position &rhs);
    Position &operator+=(const Position &rhs);

    static const Position &origin();
    int x() const;
    int y() const;
    Position &reflection() const;
private:
    int x_;
    int y_;
};

class Vector {
public:
    Vector(int x, int y);

    bool operator==(const Vector &rhs);
    bool operator!=(const Vector &rhs);
    Vector &operator+=(const Vector &rhs);

    int x() const;
    int y() const;
    Vector &reflection() const;
private:
    int x_;
    int y_;
};

class Rectangle {
public:
    Rectangle(int width, int height, Position pos);
    Rectangle(int width, int height);

    bool operator==(const Rectangle &rhs) const;
    bool operator!=(const Rectangle &rhs) const;
    Rectangle &operator+=(const Vector &rhs);

    int width() const;
    int height() const;
    const Position &pos() const;
    Rectangle &reflection() const;
    int area() const;

    std::pair<Rectangle &, Rectangle &> split_horizontally(int place);
    std::pair<Rectangle &, Rectangle &> split_vertically(int place);
private:
    int width_;
    int height_;
    Position position_;
};

class Rectangles {
public:
    Rectangles();
    Rectangles(const std::initializer_list<Rectangle> &rectangles);

    bool operator==(const Rectangles &rhs) const;
    bool operator!=(const Rectangles &rhs) const;
    Rectangles &operator+=(const Vector &rhs);
    const Rectangle &operator[](int index) const; //todo sprawdz czy nie trzeba nie-const ref

    size_t size() const;
    Rectangles& split_horizontally(int place);
    Rectangles& split_vertically(int place);
private:
    std::vector<Rectangle> rectangles_;
};

#endif //GEOMETRY_GEOMETRY_H