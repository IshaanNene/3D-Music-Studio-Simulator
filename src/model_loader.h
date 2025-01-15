#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>

class ModelLoader {
public:
    // Function to load a model from a file
    void loadModel(const std::string& filepath);

    // Function to render the loaded model
    void render();
};

#endif // MODEL_LOADER_H
