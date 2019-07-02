//#pragma once

#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
        
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

        Node * parent = nullptr;        //Node pointer to nullptr
        float h_value = std::numeric_limits<float>::max();    
        float g_value = 0.0;                                  
        bool visited = false;                              
        std::vector<Node *> neighbors;  //Vector of Node pointers

        float Distance(Node other) const{
          return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
        }

        void FindNeighbors();

      
      private:
        // Add private Node variables and methods here.
        int index;
        RouteModel * parent_model = nullptr;
        //Find the closest node in each Road contaning the current node
        RouteModel::Node * FindNeighbor(std::vector<int>node_indices);
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml); 
    auto &SNodes(){ return m_Nodes;}    //Getter method
    auto &GetNodeToRoadMap(){return node_to_road;}

    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
    
    



  private:
    // Add private RouteModel variables and methods here.
    void CreateNodeToRoadHashmap();
    std::unordered_map<int, std::vector<const Model::Road*>>node_to_road;
    std::vector<Node> m_Nodes;  //Store all of the nodes from the Open Street Map data
    

};

#endif