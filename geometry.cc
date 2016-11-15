#include "geometry.h"

Position::Position(int x, int y) {

}

bool Position::operator==(const Position &rhs) {
    return false;
}

bool Position::operator!=(const Position &rhs) {
    return false;
}

Position &Position::operator+=(const Position &rhs) {
    return <#initializer#>;
}

int Position::x() const {
    return 0;
}

int Position::y() const {
    return 0;
}

Position &Position::reflection() const {
    return <#initializer#>;
}

const Position &Position::origin() {
    return <#initializer#>;
}

Vector::Vector(int x, int y) {

}

bool Vector::operator!=(const Vector &rhs) {
    return false;
}

bool Vector::operator==(const Vector &rhs) {
    return false;
}

Vector &Vector::operator+=(const Vector &rhs) {
    return <#initializer#>;
}

int Vector::x() const {
    return 0;
}

int Vector::y() const {
    return 0;
}

Vector &Vector::reflection() const {
    return <#initializer#>;
}


Rectangle::Rectangle(int width, int height, Position pos) : width_(width), height_(height), position_(pos) {}

Rectangle::Rectangle(int width, int height) : width_(width), height_(height), position_(Position(0, 0)) {}
//todo moze Position(Position::Origin())?

bool Rectangle::operator==(const Rectangle &rhs) const {
    return false;
}

bool Rectangle::operator!=(const Rectangle &rhs) const {
    return false;
}

Rectangle &Rectangle::operator+=(const Vector &rhs) {
    return <#initializer#>;
}

int Rectangle::width() const {
    return 0;
}

int Rectangle::height() const {
    return 0;
}

const Position &Rectangle::pos() const {
    return <#initializer#>;
}

Rectangle &Rectangle::reflection() const {
    return <#initializer#>;
}

int Rectangle::area() const {
    return 0;
}

std::pair<Rectangle &, Rectangle &> Rectangle::split_horizontally(int place) {
    return std::pair<Rectangle &, Rectangle &>();
}

std::pair<Rectangle &, Rectangle &> Rectangle::split_vertically(int place) {
    return std::pair<Rectangle &, Rectangle &>();
}

Rectangles::Rectangles() {

}

Rectangles::Rectangles(const std::initializer_list<Rectangle> &rectangles) {

}

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
    return 0;
}

Rectangles &Rectangles::split_horizontally(int place) {
    return <#initializer#>;
}

Rectangles &Rectangles::split_vertically(int place) {
    return <#initializer#>;
}
