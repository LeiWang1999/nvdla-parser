//
// Created by Deng Weijia on 8/23/18.
// The interactive interface reference some code from the nvdla/sw project
// https://github.com/nvdla/sw
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
    //Load loadable file.
    auto loadable = get_loadable(test_app_args.inputName);
    if(!loadable) {
        printf("Error! Cannot open loadable file.\n");
        return 0;
    }
    Parser lenet_mnist_parser(loadable);

    return 0;
}
