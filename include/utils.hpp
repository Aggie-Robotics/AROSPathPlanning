//
// Created by jerry on 1/11/2021.
//

#ifndef AROSPATHPLANNING_UTILS_HPP
#define AROSPATHPLANNING_UTILS_HPP

namespace aros::utils {

    struct Point {
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y && orientation == other.orientation;
        }

        double x;
        double y;
        double orientation; //radians, absolute
    };



    bool same_position(double x1, double y1, double x2, double y2); //some way of comparing (x1,y1) with (x2,y2)
    bool same_orientation(double o1, double o2); //some way of comparing (x1,y1) with (x2,y2)

    double degToRad(double d);
    double radToDeg(double r);

    bool isMove(Point a, Point b);
    bool isTurn(Point a, Point b);
}
#endif //AROSPATHPLANNING_UTILS_HPP
