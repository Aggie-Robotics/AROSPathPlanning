//
// Created by jerry on 1/11/2021.
//
#include <vector>
#include "utils.hpp"
#ifndef AROSPATHPLANNING_PATH_H
#define AROSPATHPLANNING_PATH_H

using namespace aros::utils;

namespace aros::Path{
    class Path{
        std::string which;
        std::vector<Point> route;

        vector<Point> topRoute();
        vector<Point> bottomRoute();
    public:
        Path(std::string which);



    };
}
#endif //AROSPATHPLANNING_PATH_H
