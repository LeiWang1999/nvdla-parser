//
// Created by Deng Weijia on 8/22/18.
//

///Classes that offer tools for drawing a process flow

#ifndef NVDLA_DEPICTER_GRAPH_GENERATOR_H
#define NVDLA_DEPICTER_GRAPH_GENERATOR_H

#include <string>
#include <map>
#include <vector>
#include "DLA_desc.h"
#include "EMU_desc.h"



//Base class for graph drawers.

class Graph_base{
protected:
    //Name list of each operations.
    std::vector<std::string> layer_name_list;

    //Name list of each memory address.
    std::vector<std::string> mem_name_list;

    //Edge lists that between either kinds of nodes, mem address or layer
    std::vector<std::pair<std::string,std::string> >  edge_list;

    //The destination mem addresses of each layer.
    std::vector<std::vector<int> > dest_list;

    //The source mem addresses of each layer.
    std::vector<std::vector<int> > source_list;

    //The fused parents of each layer. Some layers' input data is not from the memory,
    // rather, they are from the fused parents.
    std::vector<int> fused_parents;

    //Stores the operation type for each layer.
    std::map<int,std::string> converted_list;

    Addr_list addr_list;

    //The original index is task-wise. In order to not collide with other tasks within
    // the same file, index_offset is needed.
    int index_offset;

    //Generate the dots of a process flow.
    void generate_dot(std::ostream & os, std::string const & title, std::string const & param);

    //Generate the edges of a process flow.
    void generate_edge(std::ostream & os);

public:

    //Write the information that is needed in the head of each python script file.
    static void graph_head(std::ostream & os,const std::string & format);
    //Write the information that is needed in the tail of each python script file.
    static void graph_tail(std::ostream & os, const std::string & filename);
    //Set the format for nodes.
    static void set_node_format(std::ostream & os, const std::string & attr){ os<<"dot.attr('node',"<<attr<<")\n"; }

    //Drive the process of drawing a graph.
    void draw_data_flow(std::ostream & os);
    Graph_base(Addr_list addr, int i = 0):addr_list(addr),index_offset(i){}

};

//Class for DLA process graph drawer.
class DLA_graph :public Graph_base{

public:
    DLA_graph(Dep_graph_desc net, Addr_list addr, Surf_desc surf, int i = 0);
};

//Class for EMU process graph drawer.
class EMU_graph :public Graph_base{


public:
    EMU_graph(EMU_Op_desc op, Addr_list addr, EMU_Op_buf surf, int i = 0);



};



#endif //NVDLA_DEPICTER_GRAPH_GENERATOR_H
