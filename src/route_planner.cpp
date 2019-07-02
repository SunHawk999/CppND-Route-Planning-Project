#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {

    //Scale floats to percentages
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    //Should be pointers? When attaching & to m_model, running make fails
    start_node = m_Model.FindClosestNode(start_x, start_y);
    end_node = m_Model.FindClosestNode(end_x, end_y);
}
