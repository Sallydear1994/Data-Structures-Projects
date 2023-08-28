// RoadMap.hpp
//
// ICS 46 Spring 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This header defines a type RoadMap, which is simply a shorthand name for a
// particular instantiation of the Digraph template, where each vertex has a
// string for its information and each edge has a RoadSegment for its information.

#ifndef ROADMAP_HPP
#define ROADMAP_HPP

#include <string>
#include "Digraph.hpp"
#include "RoadSegment.hpp"



using RoadMap = Digraph<std::string, RoadSegment>;



#endif

