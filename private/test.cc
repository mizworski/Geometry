#include <assert.h>
#include <iostream>
#include "../geometry.h"

#include <cassert>

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

    //auto& origin = Position::origin();
    //origin += v1;

    //assert(origin==Position::origin()); //todo jak zrobic zeby byl immutable


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

    auto d2_copy = d2.reflection();
    assert(d2_copy == Rectangle(100, 200, Position(200, 100)));

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
    auto test = d3.split_vertically(split_place);
    assert(d3.split_vertically(split_place) == expected_ver_pair);

    // Arithmetic operations

    auto d_temp = d1 + v1;
    assert(d_temp == Rectangle(200, 100, Position(200, 350)));

    auto d_temp2 = v1 + d2;
    assert(d_temp == Rectangle(200, 100, Position(200, 350)));
}

void simple_test_rectangles() {
    auto p1 = Position(100, 200);
    auto p2 = Position(100, 200);

    /*auto v1 = */Vector(100, 150);

    auto d1 = Rectangle(200, 100, p1);
    auto d2 = Rectangle(200, 100, p2);

    /*
    auto res1 = Rectangles();
    auto res2 = Rectangles({d1, d2});

    assert(res1.size() == 0);
    */
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
//poczatek Position
    {
        simple_test();

    }
    {
        Position x1(100, 200);
        Position x2(100, 200);
        Position x3(100, 300);
        assert(x1 == x2);
        assert(!(x1 == x3));
        assert(x3.x() == 100);
        assert(x3.y() == 300);
        Position reflected = x1.reflection();
        Position reflectedGoodPosition(200, 100);
        assert(x1 == x2);
        assert(reflected == reflectedGoodPosition);
        Vector v1(10, 20);
        x3 += v1;
        Position x3PlusVector(110, 320);
        assert(x3 == x3PlusVector);
        assert(Position(0, 0) == Position::origin());
    }
//koniec Position

//poczatek Vector
    {
        Vector v1(101, 202);
        Vector v2(120, -10);
        Vector v3(120, -10);
        assert(!(v1 == v2));
        assert(v2 == v3);
        assert(v1.x() == 101);
        assert(v1.y() == 202);
        assert(v2.y() == -10);
        assert(v1.reflection() == Vector(202, 101));
        assert(v2.reflection() == Vector(-10, 120));
        assert(v2 == v3);
        v1 += v2;
        assert(v1 == Vector(221, 192));
    }
//koniec Vector

//poczatek Rectangle
    {
        Position pos1(100, 120);
        Position pos2(100, 120);
        Position pos3(120, 122);
        Rectangle rec1(10, 20, pos1);
        Rectangle rec2(10, 20, pos2);
        Rectangle rec3(10, 21, pos1);
        Rectangle rec4(10, 20, pos3);
//Rectangle(-200, 300);
        Rectangle rec5(200, 300);
        Rectangle rec6(200, 300);
        Rectangle rec7(200, 300, Position(0, 0));
        assert(rec6 == rec7);
        assert(rec5 == rec6);
        assert(rec1 == rec2);
        assert(!(rec1 == rec3));
        assert(!(rec1 == rec4));
        assert(rec7.width() == 200);
        assert(rec7.height() == 300);
        assert(rec7.pos() == Position::origin());

        Rectangle rectangle(2, 1, Position(0, 3));
        Rectangle rectangleReflection(1, 2, Position(3, 0));
        assert(rectangle.reflection() == rectangleReflection);

        Vector v1(10, 20);
        rectangle += v1;
        assert(rectangle.width() == 2);
        assert(rectangle.height() == 1);
        assert(rectangle.pos() == Position(10, 23));
        assert(rectangle.area() == 2);

        Rectangle rect(100, 200, Position(10, 20));
        std::pair<Rectangle, Rectangle> para = rect.split_horizontally(20);
        Rectangle first(100, 20, Position(10, 20));
        Rectangle second(100, 180, Position(10, 40));
        assert(para.first == first);
        assert(para.second == second);

        std::pair<Rectangle, Rectangle> para2 = rect.split_vertically(21);
        Rectangle first2(21, 200, Position(10, 20));
        Rectangle second2(79, 200, Position(31, 20));
        assert(para2.first == first2);
        assert(para2.second == second2);

        rec1 = rec3;
        rec3 += v1;

        Position pos1_before(pos1);
        pos1 += v1;

        Rectangle rec3_before(10, 21, pos1_before);
        assert(rec1 == rec3_before);
        assert(rec1 != rec3);

    }
//koniec Rectangle

//poczatek Rectangles
    {
        Rectangle rect1(10, 20);
        Rectangle rect2(20, 30);
        Rectangle rect3(30, 40);
        Rectangle rect4(40, 50);
        Rectangles rectangles1({rect1, rect2, rect3});
        Rectangles rectangles2({rect1, rect2, rect3});
        Rectangles rectangles3({rect1, rect2, rect4});
        Rectangles rectangles4({rect1, rect3, rect2});
        assert(rectangles1 == rectangles2);
        assert(!(rectangles1 == rectangles3));
        assert(!(rectangles1 == rectangles4));
//rectangles1[4];
        assert(rectangles1.size() == 3);

        Vector v1(10, 11);
        Rectangle rect11(10, 20, Position(10, 11));
        Rectangle rect12(20, 30, Position(10, 11));
        Rectangle rect13(30, 40, Position(10, 11));
        Rectangles rectangles11({rect11, rect12, rect13});
        rectangles1 += v1;
        assert(rectangles11 == rectangles1);


        Rectangles rectangles22({rect1, Rectangle(20, 10), Rectangle(20, 20, Position(0, 10)), rect3});
        rectangles2.split_horizontally(1, 10);
        assert(rectangles22 == rectangles2);

        Rectangles rectangles33({rect1, Rectangle(11, 30), Rectangle(9, 30, Position(11, 0)), rect3});
        Rectangles rectangles10({rect1, rect2, rect3});
        rectangles10.split_vertically(1, 11);
        assert(rectangles10 == rectangles33);
    }
//koniec Rectangles

//poczatek Operatorow
    {
        Position p1(10, 20);
        Position p2(15, 30);
        Vector v1(40, 50);
        Vector v2(100, 200);
        Rectangle rectangle1(100, 200);
        Rectangle rectangle2(200, 300);

        Position p3 = p1 + v1;
        Position p4 = v1 + p1;
        assert(p3 == p4);
        assert(p3 == Position(50, 70));

        Vector v3 = v1 + v2;
        assert(v3 == Vector(140, 250));

        Rectangle rectangle3 = rectangle1 + v1;
        assert(rectangle3 == Rectangle(100, 200, Position(40, 50)));
        Rectangle rectangle4 = v1 + rectangle1;
        assert(rectangle3 == rectangle4);

        Rectangles rectangles({rectangle1, rectangle2});
        Rectangles rectangles2({(rectangle1 + v1), rectangle2 + v1});
//        assert(rectangles + v1 == rectangles2);   //tu sie wywala
//        assert((v1 + rectangles) == rectangles2); //tu tez

    }
//koniec Operatorow

//poczatek Merge
    {
        Rectangle rect1(10, 20);
        std::pair<Rectangle, Rectangle> splitted1 = rect1.split_horizontally(9);
        assert(merge_horizontally(splitted1.first, splitted1.second) == rect1);
    }
    {
        Rectangle rect1(10, 20);
        std::pair<Rectangle, Rectangle> splitted1 = rect1.split_vertically(9);
        assert(merge_vertically(splitted1.first, splitted1.second) == rect1);
    }
//koniec Merge

    std::cout << "Wsystko ok!" << std::endl;


    return 42;
}