#include <vector>
#include <string>
#include <stdint.h>
#include "utils.hpp"
#ifndef AROSPATHPLANNING_PATH_H
#define AROSPATHPLANNING_PATH_H

namespace aros::Route{
    const utils::Point invalidPoint {INT32_MAX, INT32_MAX, INT32_MAX};

    class Path{
        std::vector<utils::Point> route;
        int index;
        std::string routeChoice;
        void leftRoute();
        void rightRoute();
        void emptyRoute();


    public:
        Path(std::string routeChoice);
        std::string getRouteChoice();
        int getNumPoints();
        utils::Point getCurrentPoint();
        utils::Point getNextPoint();
        std::string getNextAction();
        bool done();

    };
}
#endif //AROSPATHPLANNING_PATH_H
