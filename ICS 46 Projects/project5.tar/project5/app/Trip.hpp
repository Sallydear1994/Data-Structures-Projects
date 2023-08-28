// Trip.hpp
//
// ICS 46 Spring 2021
// Project #5: Rock and Roll Stops the Traffic
//
// Describes a type that carries information about one trip to be evaluated
// by the program.  A trip is described by a start vertex number, an end
// vertex number, and a TripMetric (i.e., distance or driving time).

#ifndef TRIP_HPP
#define TRIP_HPP

#include "TripMetric.hpp"



struct Trip
{
    int startVertex;
    int endVertex;
    TripMetric metric;
};



#endif

