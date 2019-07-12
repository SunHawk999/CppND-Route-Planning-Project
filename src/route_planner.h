#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"

class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}

    //Search algorithm that finds the shortest path
    void AStarSearch();

  private:
    // Add private variables or methods declarations here.
    
    //Constructs final path of a vector of nodes from a given node
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    //Sort the list of open nodes in the AStarSearch, and return the node with the lowest value
    RouteModel::Node *NextNode();
    //Take each neighbor of the current node in the AStarSearch and set their variables
    void AddNeighbors(RouteModel::Node *current_node);
    //Calculate the h-value of a given node
    float CalculateHValue(RouteModel::Node const *node);
    
    //Refers to the model that AStarSearch performes on
    RouteModel &m_Model;

    //start and end node will point to the nodes in the model which are closest to the starting and ending points
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;

    //Will hold the total distance for the route that A* search finds from start to end
    float distance;
    std::vector<RouteModel::Node * > open_list;
};

#endif
