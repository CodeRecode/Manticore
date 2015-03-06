#include "Model.h"

Model::Model(std::string filename) {    
    std::ifstream modelFile(filename);
    std::string type, path, line;
	while (std::getline(modelFile, line)) {
        if (line.length() == 0)
            continue;
        std::istringstream iss(line);
        iss >> type;
        if (type == "v") {

        }
        else if (type == "vt") {

        }
        else if (type == "vn") {

        }
    }
}