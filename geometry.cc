#include <cassert>
#include "geometry.h"

Position::Position(int x, int y) : x_(x), y_(y) {}

bool Position::operator==(const Position &rhs) {
    return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Position::operator!=(const Position &rhs) {
    return !(*this == rhs);
}

Position &Position::operator+=(const Vector &rhs) {
    x_ += rhs.x();
    y_ += rhs.y();
    return *this;
}

int Position::x() const {
    return x_;
}

int Position::y() const {
    return y_;
}

Position Position::reflection() const {
    return Position(y_, x_);
}

const Position &Position::origin() {
    static Position origin(0, 0);
    return origin;
}

Vector::Vector(int x, int y) : x_(x), y_(y) {}

bool Vector::operator==(const Vector &rhs) {
    return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Vector::operator!=(const Vector &rhs) {
    return !(*this == rhs);
}

Vector &Vector::operator+=(const Vector &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

int Vector::x() const {
    return x_;
}

int Vector::y() const {
    return y_;
}

Vector Vector::reflection() const {
    return Vector(y_, x_);
}

Rectangle::Rectangle(int width, int height, const Position &pos) : width_(width), height_(height), position_(pos) {}

Rectangle::Rectangle(int width, int height) : width_(width), height_(height), position_(Position(0, 0)) {}

bool Rectangle::operator==(const Rectangle &rhs) const {
    return width_ == rhs.width() && height_ == rhs.height() && position_ == rhs.position_;
}

bool Rectangle::operator!=(const Rectangle &rhs) const {
    return !(*this == rhs);
}

Rectangle &Rectangle::operator+=(const Vector &rhs) {
    position_ += rhs;
    return *this;
}

int Rectangle::width() const {
    return width_;
}

int Rectangle::height() const {
    return height_;
}

const Position &Rectangle::pos() const {
    return position_;
}

Rectangle Rectangle::reflection() const {
    Rectangle rectangle(height_, width_, position_.reflection());
    return rectangle;
}

int Rectangle::area() const {
    return height_ * width_;
}

std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int place) {
    assert(place >= 0 && place <= height_);

    Vector v(0, place);
    Rectangle top(width_, height_ - place, position_ + v);
    Rectangle bottom(width_, place, position_);
    return std::pair<Rectangle, Rectangle>(bottom, top);
}

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int place) {
    assert(place >= 0 && place <= width_);

    Vector v(0, place);
    Rectangle top(width_ - place, height_, position_ + v);
    Rectangle bottom(place, height_, position_);
    return std::pair<Rectangle, Rectangle>(bottom, top);
}

Rectangles::Rectangles() : rectangles_(std::vector<Rectangle>()) {}

Rectangles::Rectangles(const std::initializer_list<Rectangle> &rectangles) :
        rectangles_(std::vector<Rectangle>(rectangles)) {}

bool Rectangles::operator==(const Rectangles &rhs) const {
    return false;
}

bool Rectangles::operator!=(const Rectangles &rhs) const {
    return false;
}

Rectangles &Rectangles::operator+=(const Vector &rhs) {
    return <#initializer#>;
}

const Rectangle &Rectangles::operator[](int index) const {
    return <#initializer#>;
}

size_t Rectangles::size() const {
    return rectangles_.size();
}

Rectangles &Rectangles::split_horizontally(int place) {
    return <#initializer#>;
}

Rectangles &Rectangles::split_vertically(int place) {
    return <#initializer#>;
}
