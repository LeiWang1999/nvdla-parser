//
// Created by lei on 21-4-18.
//

#include <iostream>

#include "Interface.h"
#include "appargs.h"
#include "tools.h"
#include <vector>
#include "stdio.h"
#include "Parser.h"

using namespace std;
int main(int argc, char * argv[]) {

    Test_app_args test_app_args = Test_app_args();
    test_app_args.inputName = "../../data/lenet-mnist-caffe/fast-math.nvdla";
    //Load loadable file.
    auto loadable = get_loadable(test_app_args.inputName);
    if(!loadable) {
        printf("Error! Cannot open loadable file.\n");
        return 0;
    }
    Parser lenet_mnist_parser(loadable);
    union dla_surface_container * surface_container = lenet_mnist_parser.get_dla_surface_desc();
    struct dla_conv_surface_desc surface_idx0 = surface_container[0].conv_surface;
    struct dla_sdp_surface_desc surface_idx1 = surface_container[1].sdp_surface;
    struct dla_pdp_surface_desc surface_idx2 = surface_container[2].pdp_surface;

    return 0;
}
