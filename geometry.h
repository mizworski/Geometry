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

    /**
     * Reflects vector over x = y axis.
     * @return reflected vector
     */
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

    /**
     * Gets origin of coordinate system.
     * @return origin of coordinate system
     */
    static const Position &origin();

    /**
     * Reflects point over x = y axis.
     * @return reflected point
     */
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

    /**
     * Reflects rectangle over x = y axis.
     * @return reflected rectangle
     */
    Rectangle reflection() const;

    /**
     * Calculates area of rectangle.
     * @return area of rectangle
     */
    int area() const;

    /**
     * Splits rectangle into two with heights of place and rectangle's height decreased by place.
     * Throws error if height is incorrect.
     * @param place height of first rectangle
     * @return pair of splitted rectangles
     */
    std::pair<Rectangle, Rectangle> split_horizontally(int place);

    /**
     * Splits rectangle into two with widths of place and rectangle's width decreased by place.
     * Throws error if width is incorrect.
     * @param place width of first rectangle
     * @return pair of splitted rectangles
     */
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
    Rectangles &operator=(const Rectangles &other);
    Rectangles &operator=(Rectangles &&other);
    Rectangles &operator+=(const Vector &rhs);
    Rectangle &operator[](size_t index);

    size_t size() const;

    /**
     * Splits one of the rectangles with a horizontal cut.
     * Throws error if place is incorrect.
     * @param idx index of splitted rectangle
     * @param place position of cut
     * @return new collection of rectangles, ordered as before, with the one splitted
     */
    Rectangles &split_horizontally(size_t idx, int place);
    
    /**
     * Splits one of the rectangles with a vertical cut.
     * Throws error if place is incorrect.
     * @param idx index of splitted rectangle
     * @param place position of cut
     * @return new collection of rectangles, ordered as before, with the one splitted
     */
    Rectangles &split_vertically(size_t idx, int place);

private:
    std::vector<Rectangle> rectangles_;

    /**
     * Splits one of the rectangles.
     * Throws error if place is incorrect.
     * @param idx index of splitted rectangle
     * @param place position of cut
     * @param horizontal shows whether the cut is horizontal or vertical
     * @return new collection of rectangles, ordered as before, with the one splitted
     */
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

/**
 * Merges two recangles that share the same horizontal edge.
 * Throws error if upper edge of the first rectangle is not bottom
 * edge of the second rectangle.
 * @param rect1 first rectangle to merge
 * @param rect2 second rectangle to merge
 * @return merged rectangle
 */
Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

/**
 * Merges two recangles that share the same vertical edge.
 * Throws error if right edge of the first rectangle is not left
 * edge of the second rectangle.
 * @param rect1 first rectangle to merge
 * @param rect2 second rectangle to merge
 * @return merged rectangle
 */
Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

#endif //GEOMETRY_GEOMETRY_H
