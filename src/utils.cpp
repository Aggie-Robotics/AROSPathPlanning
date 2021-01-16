//
// Created by jerry on 1/11/2021.
//

#include "utils.hpp"
#include <cmath>

namespace aros::utils {
    const double pi = 3.14159265358979323846;

    //TODO: Update from chassis definition and ticks per rev value
    /*
     * tolerance_p is minimum measurable change in distance between 2 points
     * tolerance_o is minimum measurable change in orientation between 2 points
     */
    double tolerance_p = 0.001;
    double tolerance_o = 0.002;

    bool same_position(double x1, double y1, double x2, double y2) {
        return std::abs(sqrt(pow(x2 - x1, 2) +
                    pow(y2 - y1, 2))) <= tolerance_p;
    }

    bool same_orientation(double o1, double o2) {
        return std::abs(o1 - o2) <= tolerance_o;
    }

    double degToRad(double d) {
        return d * pi / 180;
    }

    double radToDeg(double r) {
        return r * 180 / pi;
    }

    bool isMove(Point a, Point b) { //possible error when case: "everything is the same"? which honestly shouldn't even happen
        if (a.x == b.x && a.y == b.y && a.orientation != b.orientation) //orientation part tries to account for above error
            return true;
        return false;
    }

    bool isTurn(Point a, Point b){
        if (a.orientation == b.orientation && (a.x != b.x || a.y != b.y)){
            return true;
        }
        return false;
    }
}