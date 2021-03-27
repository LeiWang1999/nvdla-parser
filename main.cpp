//
// Created by Deng Weijia on 8/23/18.
// The interactive interface reference some code from the nvdla/sw project
// https://github.com/nvdla/sw
//

#include <iostream>

#include "Interface.h"
#include "driver.h"
#include "main.h"
#include "tools.h"
#include <cstring>
#include <vector>
#include <sys/stat.h> 　
#include <exception>

//Used to show help information.
void show_help(char * * argv){

    printf("Usage: %s [-options]\n",argv[0]);
    printf("Where options include:\n");
    printf("    -h                      Print this help message\n");
    printf("    --input <input_file>    Input file path\n");
    printf("    --image <output_file>   Output image file path\n");
    printf("    --output <output_file>  Output description file path\n");
    printf("    --format <format>       Designate the output format.\n"
           "                            Currently supported format: pdf, png, svg \n");



}

int main(int argc, char * argv[]) {

    Test_app_args test_app_args = Test_app_args();
    size_t ii = 1;
    while(true){
        if(ii >= argc )
            break;
        const char* arg = argv[ii];

        if (std::strcmp(arg, "-h") == 0) // help
        {
            // Print usage
            test_app_args.show_help = true;
            break;
        }
            // Input filename
        else if (std::strcmp(arg, "--input") == 0)
        {
            if (ii+1 >= argc)
            {
                // Expecting another parameter
                test_app_args.show_help = true;
                break;
            }

            test_app_args.inputName = std::string(argv[++ii]);
        }
            // Output image filename
        else if (std::strcmp(arg, "--image") == 0)
        {
            if (ii+1 >= argc)
            {
                // Expecting another parameter
                test_app_args.show_help = true;
                break;
            }

            test_app_args.outputName = std::string(argv[++ii]);
        }
            // output folder name
        else if (std::strcmp(arg, "--output") == 0)
        {
            if (ii+1 >= argc)
            {
                // Expecting another parameter
                test_app_args.show_help = true;
                break;
            }

            test_app_args.outputPath = std::string(argv[++ii]);
        }

            // output format
        else if (std::strcmp(arg, "--format") == 0)
        {
            if (ii+1 >= argc)
            {
                // Expecting another parameter
                test_app_args.show_help = true;
                break;
            }

            test_app_args.format = std::string(argv[++ii]);

        }
        else // unknown
        {
            test_app_args.show_help = true;
            break;
        }
        ii++;
    }

    if (!(strcmp(test_app_args.inputName.c_str(), "") && strcmp(test_app_args.outputName.c_str(), "")&&strcmp(test_app_args.outputPath.c_str(), ""))) {
        test_app_args.show_help = true;
    }
    if(strcmp(test_app_args.format.c_str(),"pdf")&&strcmp(test_app_args.format.c_str(),"png")&&strcmp(test_app_args.format.c_str(),"svg")) {
        // Wrong format
        test_app_args.show_help = true;
    }

    // For output folder ./ or ../, change folder name to ./output or ../output respectively.
    if(!strcmp(test_app_args.outputPath.c_str(),"./")&&strcmp(test_app_args.outputPath.c_str(),"../")) {
        test_app_args.outputPath+="output";
    }

    if(test_app_args.show_help)
        show_help(argv);

    printf("Generating graph file starts!\n");

    //Load loadable file.
    auto loadable = get_loadable(test_app_args.inputName);
    if(!loadable) {
        printf("Error! Cannot open loadable file.\n");
        return 0;
    }


    //Change the name of the python file if there is a file with the same name.
    string py_name;
    do {
        py_name = get_random_name() + ".txt";
    }while ( is_file_exists(py_name));

    //Change the name of the image file if there is a file with the same name.
    string graph_name = test_app_args.outputName;
    int index=1;
    while ( is_file_exists(graph_name+"."+test_app_args.format)){
        graph_name = test_app_args.outputName+num_to_string(index);
        printf("Output filename occupied. Output filename changed to %s\n",graph_name.c_str());
        index++;
    }

    //Change the name of the output folder if there is a folder with the same name.
    string folder_name = test_app_args.outputPath;
    if(folder_name.back() == '/')
        folder_name.resize(folder_name.size()-1);
    string ori_folder_name = folder_name;
    index = 1;
    while ( is_folder_exist(folder_name)){
        folder_name = ori_folder_name+num_to_string(index);
        printf("Output folder occupied. Output folder changed to %s\n",folder_name.c_str());
        index++;
    }

    //Create the folder.
    if(mkdir(folder_name.c_str(),0755)) {
        printf("Error when creating folder!\n");
        return 0;
    }

    folder_name += "/";

    //Decode the blobs data and draw the process graph.
    try {
        Driver driver(loadable);
        if (!driver.engine_start(py_name, test_app_args.format, graph_name, folder_name)){
            //Engine failed
            printf("Error when generating graph!\n");
            return 0;
        }
    }
    catch (std::exception & exc){
        printf("Error when generating graph! Error: %s\n",exc);
        return 0;
    }

    //Call python to output the graph file.
    try {
        FILE * fp;
        fp = popen(("python "+py_name).c_str(),"r");
        pclose(fp);
    }
    catch (std::exception & exc){
        printf("Error when writing graph file! Error: %s\n",exc);
        return 0;
    }

    //Erase the temp files.
    // try {
    //     FILE * fp;
    //     fp = popen(("rm "+py_name).c_str(),"r");
    //     pclose(fp);

    //     fp = popen(("rm "+graph_name).c_str(),"r");
    //     pclose(fp);
    // }
    // catch (std::exception & exc){
    //     printf("Error when deleting temporary files! Error: %s\n",exc);
    //     return 0;
    // }



    printf("Generating graph file finished with success!\n");



    return 0;
}
