#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cmath>
#include "../src/optimizer.cpp"

TEST_CASE("vector/basic", "") {
    Vector<3> a(1,2,3);
    Vector<3> b(1,2,3);
    Vector<3> c(2,4,6);
    Vector<3> c2(3,6,9);
    Vec3f d;
    d = a+b;
    REQUIRE(d == c);

    d = a*3;
    REQUIRE(d == c2);

    d = c2/3;
    REQUIRE(d == a);

    d = c-b;
    REQUIRE(d == a);
}

TEST_CASE("create", "") {
    NelderMeadOptimizer<2> o;
}

TEST_CASE("syntax", "") {
    NelderMeadOptimizer<2> o;

    Vec2f a(0.5, 0.5);
    Vec2f new_values = o.step(a, 1);
}

TEST_CASE("functionality", "") {
    NelderMeadOptimizer<2> o;
    Vec2f a(0,0);
    Vec2f b(1,0);
    Vec2f c(0,1);
    Vec2f d(1,1);
    Vec2f e(1.5,1.5);
    Vec2f f(0,2);
    Vec2f g(0.75,0.5);
    Vec2f h(1,0.5);
    Vec2f i(0.5,1);

    o.step(b,0.1);
    o.step(a,0);
    Vec2f result;
    result = o.step(c,0.5);
    REQUIRE(result == d);
    result = o.step(result,1);
    REQUIRE(result == e);
    result = o.step(result,0);
    REQUIRE(result == f);
    result = o.step(result,0);
    REQUIRE(result == g);
    result = o.step(result,0);
    REQUIRE(result == i);
}

float f(Vec2f v) {
    float x = v[0];
    float y = v[1];
    return ((-x*x*x*x+4.5*x*x+2)/pow(2.71828,2*y*y));
}

TEST_CASE("camel", "") {
    NelderMeadOptimizer<2> o;
    Vec2f a(2,1);
    Vec2f b(-1,0.534);
    Vec2f c(-1.0324,-1);
    o.step(a, f(a));
    o.step(b, f(b));
    Vec2f v = o.step(c, f(c));
    for (int i=0; i<100; i++) {
        v = o.step(v, f(v));
    }
    float tolerance = 0.01;
    REQUIRE(abs(v[0]) > 1.5-tolerance);
    REQUIRE(abs(v[0]) < 1.5+tolerance);
    REQUIRE(abs(v[1]) > -tolerance);
    REQUIRE(abs(v[1]) < +tolerance);
}