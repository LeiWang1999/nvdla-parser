//
// Created by Deng Weijia on 8/27/18.
//

#include "Graph_generator.h"
#include "external/loadable_generated.h"
#include <string>
#include <unordered_set>

using std::ostream;
using std::map;
using std::string;
using std::unordered_set;
using std::vector;

void Graph_base::generate_dot(ostream &os, string const &title, string const &param) {
    os << "dot.node('A" << title << "B', label = '" << title << "'"<<param<<")\n";
}

void Graph_base::generate_edge(ostream &os) {
    // std::unordered_set<string> out_list;
    // for (auto & x : edge_list)
    // {
    //     out_list.emplace( "dot.edge('A" + x.first + "B','A" + x.second + "B', '')" +"\n");
    // }
    // for ( auto & x: out_list)
    //     os<<x;
    for (auto & x : edge_list)
        os <<x.second<<std::endl;
}

void Graph_base::graph_head(ostream &os, const string & format) {
    os << "import graphviz as gz\n";
    os << "dot = gz.Digraph();\n";
    os<<"dot.format = '"<<format<<"'\n";
}

void Graph_base::graph_tail(ostream &os,const string & filename) {
    os << "dot.render('"<<filename<<"')\n";
}

void Graph_base::draw_data_flow(ostream &os) {


    //The operation name presented in the process flow is layer_type+global_index
    for (auto &i : converted_list) {

        layer_name_list.emplace_back(i.second + " "+ num_to_string(i.first + index_offset));
    }

    //The mem name presented in the process flow is mem_addr+mem_index
    for (int i =0; i<addr_list.index_dict.size();i++){
        mem_name_list.emplace_back( "MEM_ADDR " + num_to_string(i));
    }

    //Check whether the layer or the mem_addr is used in the process flow. Unused nodes won't be appeared in the result.
    vector<int> is_used_layer(layer_name_list.size(),0);
    vector<int> is_used_mem_name_list(mem_name_list.size(),0);

    for (int i=0;i<converted_list.size();i++){
        //Deal with edges that is the source of current layer.
        for(auto x: source_list[i]) {
            //If the source addr is valid, add the corresponding edge.
            if(x!=-1)
            {   edge_list.emplace_back( std::pair<string,string>( mem_name_list[addr_list.index_dict[x]],layer_name_list[i] ));
                is_used_mem_name_list[addr_list.index_dict[x]] = 1;
                is_used_layer[i] = 1;
            }
            //If the fused parent addr is valid, add the corresponding edge.


        }
        if(fused_parents.size()&&fused_parents[i]!=-1){
            edge_list.emplace_back( std::pair<string,string>( layer_name_list[fused_parents[i]],layer_name_list[i] ));
            is_used_layer[i] = 1;
            is_used_layer[fused_parents[i]] = 1;

        }
        //Deal with edges that is the destination of current layer.
        for(auto x:dest_list[i])

            if(x!= -1) {
                edge_list.emplace_back(layer_name_list[i], mem_name_list[addr_list.index_dict[x]]);
                is_used_mem_name_list[addr_list.index_dict[x]] = 1;
                is_used_layer[i] = 1;
            }

    }
    for (auto & x : edge_list)
         std::cout <<x.first<<" , "<<x.second<<std::endl;
    
    std::cout<<std::endl;
    

    //Write down all valid nodes.
    // for (int i=0;i<is_used_layer.size();i++)
    // {
    //     if(is_used_layer[i])
    //         generate_dot(os, layer_name_list[i] ,"");
    // }
    // for (int i=0;i<is_used_mem_name_list.size();i++)
    // {
    //     if(is_used_mem_name_list[i])
    //         generate_dot(os, mem_name_list[i] ,",shape='box'");
    // }


    // //Write down all edges.
    generate_edge(os);
}

//In the EMU blobs, the type of each layer is stored in the op_desc blob.
EMU_graph::EMU_graph(EMU_Op_desc op, Addr_list addr, EMU_Op_buf surf, int i) :Graph_base(addr,i)
{

    source_list = surf.source_list;
    dest_list = surf.dest_list;
    for (int i=0;i<op.configuration.size();i++)
        converted_list.emplace(std::pair<int,string>(i,op.configuration[i]));
}

//In the DLA blobs, the type of each layer is stored in the dep_graph blob.
DLA_graph::DLA_graph(Dep_graph_desc net, Addr_list addr, Surf_desc surf, int i) :Graph_base(addr,i)
{
    source_list = surf.source_list;
    dest_list = surf.dest_list;
    for(auto & x:net.converted_data){
        converted_list.emplace(std::pair<int,string>(x.index,x.op_type));
    }
    for(int i=0;i<net.converted_data.size();i++){
        fused_parents.emplace_back(net.converted_data[i].fused_parrent.index);
    }

}
