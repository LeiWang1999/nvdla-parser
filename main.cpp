//
// Created by Deng Weijia on 8/23/18.
// The interactive interface reference some code from the nvdla/sw project
// https://github.com/nvdla/sw
//

#include <iostream>

#include "Interface.h"
#include "appargs.h"
#include "tools.h"
#include <cstring>
#include <exception>
#include <sys/stat.h>
#include <vector>
#include "stdio.h"
#include "Parser.h"

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
using namespace std;
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
    Parser lenet_mnist_parser(loadable);

    return 0;
}
