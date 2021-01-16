#include <string>
#include "Path.hpp"

using namespace aros::utils;
namespace aros::Route {
    Path::Path(std::string routeChoice) : routeChoice(routeChoice) {
        if (routeChoice == "left")
            leftRoute();
        else if (routeChoice == "right")
            rightRoute();
        else
            emptyRoute();

        index = 0;
    }

    std::string Path::getRouteChoice() {
        return routeChoice;
    }

    int Path::getNumPoints() {
        return route.size();
    }

    Point Path::getCurrentPoint() {
        if (!done()) {
            return route[index];
        }
        return invalidPoint;
    }

    Point Path::getNextPoint() {
        if (!done()) {
            return route[++index];
        }
        return invalidPoint;
    }

    std::string Path::getNextAction() {
        if (!done()) {
            Point a = route[index];
            Point b = route[index + 1];
            if(a.x == b.x && a.y == b.y){ return "turn"; }
            else { return "move"; }
        }
        return "stop";
    }

    bool Path::done() {
        int t = route.size() - 1;
        if (index >= t) {
            return true;
        }
        return false;
    }




}