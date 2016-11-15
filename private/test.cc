#include <assert.h>
#include "../geometry.h"

Vector get_some_vector() {
    Vector ret = Vector(2, 3);
    return ret;
}

void simple_test_position() {
    auto p1 = Position(100, 200);
    auto p2 = Position(100, 200);
    auto v1 = Vector(100, 150);

    assert(p1 == p2);

    assert(p1.x() == 100);
    assert(p1.y() == 200);
    assert(p1.reflection() == Position(200, 100));

    p1 += v1;
    assert(p1 == Position(200, 350));

    auto origin = Position::origin();
    origin += v1;

    //assert(origin==Position::origin());


    // Arithmetic operations
    auto p3 = p1 + v1;
    assert(p3 == Position(300, 500));
    p3 = v1 + p2;
    assert(p3 == Position(200, 350));

    // auto p4 = p1 + get_some_vector();

}

void simple_test_vector() {
    auto v1 = Vector(100, 150);
    auto v2 = Vector(100, 150);

    assert(v1 == v2);

    assert(v1.x() == 100);
    assert(v1.y() == 150);

    assert(v1.reflection() == Vector(150, 100));
    v1 += v2;
    assert(v1 == Vector(200, 300));

    // Arithmetic operations
    assert(v1 + v2 == Vector(300, 450));

}

void simple_test_rectangle() {
    auto p1 = Position(100, 200);
    auto p2 = Position(100, 200);

    auto v1 = Vector(100, 150);

    auto d1 = Rectangle(200, 100, p1);
    auto d2 = Rectangle(200, 100, p2);
    auto d3 = Rectangle(200, 100);

    assert(d1 == d2);
    assert(!(d1 == d3));

    assert(d1.width() == 200);
    assert(d1.height() == 100);
    assert(d1.pos() == Position(p1));
    assert(d3.pos() == Position::origin());

    assert(d2.reflection() == Rectangle(100, 200, Position(200, 100)));

    d2 += v1;
    assert(d2 == Rectangle(200, 100, Position(200, 350)));

    assert(d2.area() == 20000);

    int split_place = 30;
    std::pair<Rectangle, Rectangle> expected_hor_pair(
            Rectangle(200, split_place),
            Rectangle(200, 100 - split_place, Position(0, split_place))
    );
    assert(d3.split_horizontally(split_place) == expected_hor_pair);

    std::pair<Rectangle, Rectangle> expected_ver_pair(
            Rectangle(split_place, 100),
            Rectangle(200 - split_place, 100, Position(split_place, 0))
    );
    assert(d3.split_vertically(split_place) == expected_ver_pair);

    // Arithmetic operations

    //auto d_temp = d1 + v1;
    //assert(d_temp == Rectangle(200, 100, Position(200, 350)));

    //auto d_temp2 = v1 + d2;
    //assert(d_temp == Rectangle(200, 100, Position(200, 350)));
}

void simple_test_rectangles() {
    auto p1 = Position(100, 200);
    auto p2 = Position(100, 200);

    /*auto v1 = */Vector(100, 150);

    auto d1 = Rectangle(200, 100, p1);
    auto d2 = Rectangle(200, 100, p2);

    auto res1 = Rectangles();
    auto res2 = Rectangles({d1, d2});

    assert(res1.size() == 0);
}

void simple_test() {
    printf("Simple test: Start\n");
    simple_test_position();
    simple_test_vector();
    simple_test_rectangle();
    simple_test_rectangles();

    printf("Simple test: Passed\n");
}

int main() {

    simple_test();
}
