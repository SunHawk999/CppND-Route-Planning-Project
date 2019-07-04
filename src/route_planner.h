#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}

    void AStarSearch();

  private:
    // Add private variables or methods declarations here.
    
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    RouteModel::Node *NextNode();
    
    RouteModel &m_Model;
    //start and end node will point to the nodes in the model which are closest to the starting and ending points
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;
    //Will hold the total distance for the route that A* search finds from start to end
    float distance;
    float CalculateHValue(RouteModel::Node *node);
    std::vector<RouteModel::Node*> open_list;
    

   

};
