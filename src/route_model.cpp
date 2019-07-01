#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {

    //Create RouteModel nodes
    int counter = 0;
    for(Model::Node node: this-> Nodes()){
        m_nodes.push_back(Node(counter, this, node));
        counter++;
    }

}