// main.cpp
//
// ICS 46 Spring 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include <iomanip>
#include "InputReader.hpp"
#include "RoadMap.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "RoadSegment.hpp"
#include "Trip.hpp"
#include "TripMetric.hpp"
#include "TripReader.hpp"

int main()
{
    InputReader input(std::cin);
    RoadMapReader reader;
    RoadMap map = reader.readRoadMap(input);
    TripReader tripRead;
    std::vector<Trip> trips = tripRead.readTrips(input);
    std::cout.precision(1);
    if (map.isStronglyConnected())
    {
        for (int i = 0; i < trips.size(); i++)
        {
            if (trips[i].metric == TripMetric::Distance)
            {
                std::map<int, int> road = map.findShortestPaths(trips[i].startVertex, [](auto &edge){return edge.miles;});
                std::cout << "Shortest distance from " << map.vertexInfo(trips[i].startVertex) << " to " << map.vertexInfo(trips[i].endVertex) << std::endl;
                std::cout << "  Begin at " << map.vertexInfo(trips[i].startVertex) << std::endl;
                int currentVertex = trips[i].endVertex;
                int previousVertex = road[currentVertex];
                double totalDistance = 0.00;
                std::vector<std::pair<int, int>> path;
                path.push_back(std::make_pair(previousVertex, currentVertex));
                while (!path.empty())
                {
                    if (previousVertex != trips[i].startVertex)
                    {
                        currentVertex = previousVertex;
                        previousVertex = road[currentVertex];
                        path.push_back(std::make_pair(previousVertex, currentVertex));   
                    }
                    else
                    {
                        std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << std::fixed << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles)" << std::endl;
                        totalDistance += map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles;
                        path.pop_back();
                    }
                }
                std::cout << "Total distance: " << std::fixed << totalDistance << " miles\n" << std::endl;
            }
            else
            {
                std::map<int, int> road = map.findShortestPaths(trips[i].startVertex, [](auto& edge){return edge.miles / edge.milesPerHour;});
                std::cout << "Shortest driving time from " << map.vertexInfo(trips[i].startVertex) << " to " << map.vertexInfo(trips[i].endVertex) << std::endl;
                std::cout << "  Begin at " << map.vertexInfo(trips[i].startVertex) << std::endl;
                int currentVertex = trips[i].endVertex;
                int previousVertex = road[currentVertex];
                double totalTime = 0.00;
                std::vector<std::pair<int, int>> path;
                path.push_back(std::make_pair(previousVertex, currentVertex));

                while (!path.empty())
                {
                    if (previousVertex != trips[i].startVertex)
                    {
                        currentVertex = previousVertex;
                        previousVertex = road[currentVertex];
                        path.push_back(std::make_pair(previousVertex, currentVertex)); 
                    }
                    else
                    {
                        double time = (map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles / map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour) * 3600;
                        int hours = time / 3600;
                        int minutes = int(time) % 3600 / 60;
                        if (hours == 0 && minutes == 0)
                        {
                            std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << std::fixed << time << " secs)" << std::endl;
                        }
                        else if (hours == 0 && minutes != 0)
                        {
                            if (minutes == 1)
                            {
                                std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << minutes << " min " << std::fixed << time - (minutes * 60) << " secs)" << std::endl;
                            }
                            else
                            {
                                std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << minutes << " mins " << std::fixed << time - (minutes * 60) << " secs)" << std::endl;
                            }
                        }
                        else
                        {
                            if (hours == 1)
                            {
                                if (minutes == 1)
                                {
                                    std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << hours << " hr " << minutes << "min " << std::fixed << (time - (hours * 3600)) - (minutes * 60) << " secs)" << std::endl;
                                }
                                else
                                {
                                    std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << hours << " hr " << minutes << "mins " << std::fixed << (time - (hours * 3600)) - (minutes * 60) << " secs)" << std::endl;
                                }
                            }
                            else
                            {
                                if (minutes == 1)
                                {
                                    std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << hours << " hrs " << minutes << "min " << std::fixed << (time - (hours * 3600)) - (minutes * 60) << " secs)" << std::endl;
                                }
                                else
                                {
                                    std::cout << "  Continue to " << map.vertexInfo(path[path.size() - 1].second) << " (" << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles << " miles @ " << map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour << "mph = " << hours << " hrs " << minutes << "mins " << std::fixed << (time - (hours * 3600)) - (minutes * 60) << " secs)" << std::endl;
                                }
                            }
                        }
                        totalTime += (map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).miles / map.edgeInfo(path[path.size() - 1].first, path[path.size() - 1].second).milesPerHour) * 3600;
                        path.pop_back();
                    }
                }
                int hours = totalTime / 3600;
                int minutes = (int(totalTime) % 3600) / 60;
                if (hours == 0 && minutes == 0)
                {
                    std::cout << "Total time: " << std::fixed << totalTime << " secs\n" << std::endl;
                }
                else if (hours == 0 && minutes != 0)
                {
                    if (minutes == 1)
                    {
                        std::cout << "Total time: " << minutes << " min " << std::fixed << totalTime - (minutes * 60) << " secs\n" << std::endl;
                    }
                    else
                    {
                        std::cout << "Total time: " << minutes << " mins " << std::fixed << totalTime - (minutes * 60) << " secs\n" << std::endl;
                    }
                }
                else
                {
                    if (hours == 1)
                    {
                        if (minutes == 1)
                        {
                            std::cout << "Total time: " << hours << " hr " << minutes << " min " << std::fixed << (totalTime - (hours * 3600)) - (minutes * 60) << " secs\n" << std::endl;
                        }
                        else
                        {
                            std::cout << "Total time: " << hours << " hr " << minutes << " mins " << std::fixed << (totalTime - (hours * 3600)) - (minutes * 60) << " secs\n" << std::endl;
                        }
                    }
                    else
                    {
                        if (minutes == 1)
                        {
                            std::cout << "Total time: " << hours << " hrs " << minutes << " min " << std::fixed << (totalTime - (hours * 3600)) - (minutes * 60) << " secs\n" << std::endl;
                        }
                        else
                        {
                            std::cout << "Total time: " << hours << " hrs " << minutes << " mins " << std::fixed << (totalTime - (hours * 3600)) - (minutes * 60) << " secs\n" << std::endl;
                        }
                    }
                }
            }
        }   
    }
    else
    {
        std::cout << "Disconnected Map" << std::endl;
    }
    return 0;
}

