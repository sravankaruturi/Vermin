//
// Created by Sravan Karuturi on 11/6/18.
//

#pragma once

#include <fstream>

namespace pe_helpers {

    void store_strings(std::string _input, std::ofstream &_out);

    void read_strings(std::string &_output, std::ifstream &_in);

}
