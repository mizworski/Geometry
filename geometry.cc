#include <cassert>
#include <utility>

#include "geometry.h"

Vector::Vector(int x, int y) : x_(x), y_(y) {}

bool Vector::operator==(const Vector &rhs) const {
    return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Vector::operator!=(const Vector &rhs) const {
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

Position::Position(int x, int y) : x_(x), y_(y) {}

bool Position::operator==(const Position &rhs) const {
    return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Position::operator!=(const Position &rhs) const {
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
    static const Position origin(0, 0);

    return origin;
}

Rectangle::Rectangle(int width, int height, const Position &pos)
        : width_(width), height_(height), position_(pos) {}

Rectangle::Rectangle(int width, int height)
        : width_(width), height_(height), position_(Position(0, 0)) {}

bool Rectangle::operator==(const Rectangle &rhs) const {
    return width_ == rhs.width() &&
           height_ == rhs.height() &&
           position_ == rhs.position_;
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

    Rectangle reflected = this->reflection();

    auto split_reflected = reflected.split_horizontally(place);

    return std::pair<Rectangle, Rectangle>(split_reflected.first.reflection(), split_reflected.second.reflection());
}

Rectangles::Rectangles() : rectangles_(std::vector<Rectangle>()) {}

Rectangles::Rectangles(const std::initializer_list<Rectangle> &rectangles) :
        rectangles_(std::vector<Rectangle>(rectangles)) {}

Rectangles::Rectangles(const Rectangles &other) :
        rectangles_(other.rectangles_) {}

Rectangles::Rectangles(Rectangles &&other) :
        rectangles_(std::move(other.rectangles_)) {}

bool Rectangles::operator==(const Rectangles &rhs) const {
    if (this->size() != rhs.size())
        return false;

    for (size_t i = 0; i < this->size(); i++) {
        if (this->rectangles_[i] != rhs.rectangles_[i])
            return false;
    }

    return true;
}

bool Rectangles::operator!=(const Rectangles &rhs) const {
    return !(*this == rhs);
}

Rectangles &Rectangles::operator+=(const Vector &rhs) {
    for (auto &rect : this->rectangles_) {
        rect += rhs;
    }

    return *this;
}

Rectangle &Rectangles::operator[](size_t index) {
    assert(index < this->size());

    return this->rectangles_[index];
}

size_t Rectangles::size() const {
    return rectangles_.size();
}

/* Splits one of the rectangles.
 * Whether the cut is horizontal or vertical,
 * is defined by 'horizontal' variable.
 */
Rectangles &Rectangles::split(size_t idx, int place, bool horizontal) {
    assert(idx < this->size());

    auto halves =
            horizontal ?
            this->rectangles_[idx].split_horizontally(place) :
            this->rectangles_[idx].split_vertically(place);

    this->rectangles_[idx] = halves.first;
    this->rectangles_.push_back(halves.second);

    // inserting the second half just after the first one
    for (size_t i = idx + 1; i < this->size() - 1; i++) {
        std::swap(this->rectangles_[i], this->rectangles_[this->size() - 1]);
    }

    return *this;
}

Rectangles &Rectangles::split_horizontally(size_t idx, int place) {
    return this->split(idx, place, true);
}

Rectangles &Rectangles::split_vertically(size_t idx, int place) {
    return this->split(idx, place, false);
}


Position operator+(const Position &lhs, const Vector &rhs) {
    Position result(lhs);
    result += rhs;

    return result;
}

Position operator+(const Vector &lhs, const Position &rhs) {
    Position result(rhs);
    result += lhs;

    return result;
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
    Vector result(lhs);
    result += rhs;

    return result;
}

Rectangle operator+(const Rectangle &lhs, const Vector &rhs) {
    Rectangle result(lhs);
    result += rhs;

    return result;
}

Rectangle operator+(const Vector &lhs, const Rectangle &rhs) {
    Rectangle result(rhs);
    result += lhs;

    return result;
}

Rectangles operator+(const Rectangles &lhs, const Vector &rhs) {
    Rectangles new_rect = Rectangles(lhs);

    for (size_t i = 0; i < lhs.size(); i++) {
        new_rect[i] += rhs;
    }

    return new_rect;
}

Rectangles operator+(Rectangles &&lhs, const Vector &rhs) {
    Rectangles new_rect = Rectangles(lhs);

    for (size_t i = 0; i < lhs.size(); i++) {
        new_rect[i] += rhs;
    }

    return new_rect;
}

Rectangles operator+(const Vector &lhs, const Rectangles &rhs) {
    Rectangles new_rect = Rectangles(rhs);

    for (size_t i = 0; i < rhs.size(); i++) {
        new_rect[i] += lhs;
    }

    return new_rect;
}

Rectangles operator+(const Vector &lhs, Rectangles &&rhs) {
    Rectangles new_rect = Rectangles(rhs);

    for (size_t i = 0; i < rhs.size(); i++) {
        new_rect[i] += lhs;
    }

    return new_rect;
}

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
    assert(rect1.width() == rect2.width());
    assert(rect1.pos() + Vector(0, rect1.height()) == rect2.pos());

    return Rectangle(rect1.width(), rect1.height() + rect2.height(), rect1.pos());
}

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
    auto rect = merge_horizontally(rect1.reflection(), rect2.reflection());

    return rect.reflection();
}