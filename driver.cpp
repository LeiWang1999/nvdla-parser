//
// Created by Deng Weijia on 8/27/18.
//

#include "driver.h"
#include "Interface.h"
#include <string>
#include "external/loadable_generated.h"
#include "DLA_desc.h"
#include "EMU_desc.h"
#include "Graph_generator.h"
#include <cstring>
#include <sys/stat.h> 　
#include <sys/types.h>

using std::string;
using std::vector;

bool Driver::engine_start(const string &py_name, const string &format, const string &image_name, const string &file_dir) {
    vector<string> configurations;

    //ofstream for the output python file.
    std::ofstream ofpy;
    ofpy.open(py_name);

    //Write down the necessary clauses.
    // Graph_base::graph_head(ofpy,format);

    //Index offset
    int off_set = 0;

    for(int i = 0;i<loadable->task_list()->size();i++){

        //Get the net_desc blob index from the name, which is obtained from the addr_index.
        //The index 0 of a addr_list always records the addr_index of a net_desc blob.
        int blob_index = get_blob_index( get_name(0,i));

        //Net Blob index of current task is not found, which means task fails.
        if(blob_index == -1) {
            printf("Task %d net blob unfound! Task fails!\n",i);
            return false;
        }

        //output path = file_dir/task[i]
        string current_path = file_dir+"task"+num_to_string(i);
        if(mkdir(current_path.c_str(),0755))
            return false;
        current_path+="/";

        //If this is a DLA task.
        if( loadable->task_list()->Get(i)->interface() == nvdla::loadable::Interface_DLA1) {

            //Set format for dla nodes, it is lightblue
            // Graph_base::set_node_format(ofpy,"style='filled', color='lightblue2'");

            //Set output names.
            std::ofstream ofs_net(current_path+"net_desc.txt"), ofs_surf(current_path+"surf_desc.txt"),
                    ofs_dep(current_path+"dep_desc.txt") ,ofs_op(current_path+"op_desc.txt");

            //Retrieve net_desc information
            Net_desc net_desc;
            net_desc.read_data(loadable->blobs()->Get(blob_index));
            net_desc.generate_file(ofs_net);

            //The addr_index is recorded in the net_desc blob. Note that these addr_indexes are task-wise.
            //Need to look up the addr_list for corresponding to get its absolute index.
            int surf_index = get_blob_index(get_name(net_desc.get_surf_index(),i));
            int dep_index = get_blob_index(get_name(net_desc.get_dep_index(),i));
            int op_index = get_blob_index(get_name(net_desc.get_op_index(),i));

            //Retrieve dep_graph_desc information
            Dep_graph_desc dep_graph;
            dep_graph.read_data(loadable->blobs()->Get(static_cast<flatbuffers::uoffset_t>(dep_index)));
            dep_graph.generate_file(ofs_dep);

            //Get configuration information from dep_graph
            auto configuration = dep_graph.get_configuration();

            //Retrieve surf_desc information
            Surf_desc surf_desc;
            surf_desc.read_data(loadable->blobs()->Get(static_cast<flatbuffers::uoffset_t>(surf_index)));
            surf_desc.read_configuration(configuration);
            surf_desc.generate_file(ofs_surf);

            //Retrieve op_desc information
            Op_desc op_desc;
            op_desc.read_data(loadable->blobs()->Get(static_cast<flatbuffers::uoffset_t>(op_index)));
            op_desc.read_configuration(configuration);
            op_desc.generate_file(ofs_op);

            //Draw processing flow
            DLA_graph dla_graph(dep_graph,addr_list,surf_desc,off_set);
            dla_graph.draw_data_flow(ofpy);
            off_set+=net_desc.get_num_op();

            ofs_dep.close();ofs_op.close();ofs_net.close();ofs_surf.close();
        }
        else {
            //Set format for emu nodes, it is red.
            // Graph_base::set_node_format(ofpy,"style='filled', color='red'");

            std::ofstream ofs_net(current_path+"net_desc.txt"), ofs_surf(current_path+"surf_desc.txt"),
                    ofs_op(current_path+"op_desc.txt");


            //Retrieve net_desc information
            EMU_Net_desc emu_net_desc;
            emu_net_desc.read_data(loadable->blobs()->Get(blob_index));
            emu_net_desc.generate_file(ofs_net);

            //The addr_index is recorded in the net_desc blob. Note that these addr_indexes are task-wise.
            //Need to look up the addr_list for corresponding to get its absolute index.
            int surf_index = get_blob_index(get_name(emu_net_desc.get_surf_index(),i));
            int op_index = get_blob_index(get_name(emu_net_desc.get_op_index(),i));

            //Retrieve emu_op_desc information
            EMU_Op_desc emu_op_desc;
            emu_op_desc.read_data(loadable->blobs()->Get(static_cast<flatbuffers::uoffset_t>(op_index)));
            emu_op_desc.generate_file(ofs_op);

            //Retrieve emu_op_buf information
            EMU_Op_buf emu_op_buf;
            emu_op_buf.read_data(loadable->blobs()->Get(static_cast<flatbuffers::uoffset_t>(surf_index)));
            emu_op_buf.generate_file(ofs_surf);

            //Draw processing flow
            // EMU_graph emu_graph(emu_op_desc, addr_list,emu_op_buf,off_set);
            // emu_graph.draw_data_flow(ofpy);
            // off_set+= emu_net_desc.get_num_op();

            // ofs_op.close();ofs_net.close();ofs_surf.close();

        }
    }
    //Write commands that is necessary at the end of each file.
    // Graph_base::graph_tail(ofpy,image_name);
    ofpy.close();


    return true;

}


int Driver::get_blob_index(string const &str) {
    auto blobs = loadable->blobs();
    for(int i = 0;i<blobs->size();i++)
    {
        auto entry = blobs->Get(i);
        if (!strcmp(str.c_str(),entry->name()->c_str()))
            return i;
    }
    return -1;
}
