//
// Created by Deng Weijia on 8/22/18.
// This file reference the flatbuffer examples.
//

///Tools that deal with the process of reading loadable file.

#ifndef NVDLA_DEPICTER_INTERFACE_H
#define NVDLA_DEPICTER_INTERFACE_H

#include "external/loadable_generated.h"
#include <string>

//Get the pointer of the loadable file.
const nvdla::loadable::Loadable * get_loadable(const std::string & filename);



#endif //NVDLA_DEPICTER_INTERFACE_H


