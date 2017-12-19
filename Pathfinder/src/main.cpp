#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>


int main(int argc, char** argv) {
    using namespace boost::program_options;
    options_description desc;
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    
    notify(vm); 
    return 0;
}
