#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {

    //Scale floats to percentages
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    //Should be pointers? When attaching & to m_model, running make fails
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}

std::vector<RouteModel::Node>RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node){
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    RouteModel::Node parent;

    while(current_node->parent != nullptr){
        path_found.push_back(*current_node);
        parent = *(current_node->parent);
        distance += current_node->Distance(parent);
        current_node = current_node->parent;
    }

    path_found.push_back(*current_node);
    distance *= m_Model.MetricScale();
    return path_found;
}

void RoutePlanner::AStarSearch(){
    end_node->parent = start_node;
    m_Model.path = ConstructFinalPath(end_node);
    return;
}

float RoutePlanner::CalculateHValue(RouteModel::Node *node){
    return node->Distance(*end_node);
}

RouteModel::Node *RoutePlanner::NextNode(){
    //Sort the open_list
    std::sort(open_list.begin(), open_list.end(), [](const auto &_1st, const auto &_2nd){
        return _1st->h_value * _1st->g_value < _2nd->h_value + _2nd->g_value;
    });

    //Return a pointer to lowest_node
    RouteModel::Node *lowest_node = open_list.front();
    //Erase node from list
    open_list.erase(open_list.begin());
    return lowest_node;
}