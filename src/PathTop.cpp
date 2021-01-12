//
// Created by jerry on 1/12/2021.
//
#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>

#include "Path.hpp"

using namespace aros::Path;

Path::Path(std::string fileName) {
    std::ifstream file;

    file.open(fileName);

//    //checking for error
//    if (file.fail()){
//        std::cerr << "Error Opening File" << std::endl;
//        exit(1);
//    }

    std::string myText;
    while (getline(file, myText)){
        //it is a string
        //slice into 3 strings, 1 string per value
        //cast each string as a double
        //create a Point from each string (each of which are doubles)
        //push_back() into vector `route`
    }
}