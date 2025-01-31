#include "route_model.h"
#include <iostream>

//Loop over the vector of Model::Node
RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    //Create RouteModel nodes
    int counter = 0;
    for(Model::Node node: this->Nodes()){
        m_Nodes.push_back(Node(counter, this, node));
        counter++;
    }
    CreateNodeToRoadHashmap();
}

//Loop over Roads and put them into an unordered map of vectors
void RouteModel::CreateNodeToRoadHashmap(){
    for(const Model::Road &road : Roads()){
        if(road.type != Model::Road::Type::Footway){
            for(int node_idx : Ways()[road.way].nodes){
                if(node_to_road.find(node_idx) == node_to_road.end()){
                    node_to_road[node_idx] = std::vector<const Model::Road *>();
                }
                node_to_road[node_idx].push_back(&road);
            }
        }
    }
}

//loop through the node_indices vector to find the closest unvisted node
RouteModel::Node *RouteModel::Node::FindNeighbor(std::vector<int> node_indices){
    Node *closest_node = nullptr;
    Node node;
    for(int node_index : node_indices){
        node = parent_model->SNodes()[node_index];
        if((this->distance(node) != 0) && (!node.visited)){
            if((closest_node == nullptr) || ((this->distance(node)) < (this->distance(*closest_node)))){
                closest_node = &parent_model->SNodes()[node_index];
            }
        }
    }
    return closest_node;
}

//Create a pointer for each road reference in the given vector
void RouteModel::Node::FindNeighbors(){
    for(auto & road : parent_model->node_to_road[this->index]){
        RouteModel::Node *new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
        
        if(new_neighbor != nullptr){
            this->neighbors.push_back(new_neighbor);
        }
    }
}

//Find the closest node from two floats
RouteModel::Node &RouteModel::FindClosestNode(float x, float y){
    Node inNode;
    inNode.x = x;
    inNode.y = y;

    float min_dist = std::numeric_limits<float>::max();
    float dist;
    int closest_idx;
    
    for(const Model::Road &road : Roads()){
        if(road.type != Model::Road::Type::Footway){
            for(int node_idx : Ways()[road.way].nodes){
                dist = inNode.distance(SNodes()[node_idx]);
                if(dist < min_dist){
                    closest_idx = node_idx;
                    min_dist = dist;
                }
            }
        }
    }
    return SNodes()[closest_idx];
}