#include <filesystem>
#include <iostream>

void fileAdd(const std::string &fileName) {
    namespace fs = std::filesystem;

    if (!fs::exists(fileName)) {
        std::cout << "File doesn't exist";
        return;
    }

    if (fs::exists(".minigit/addedFiles/" + fileName)) {
        fs::remove(".minigit/addedFiles/" + fileName);
    }
    fs::copy_file(fileName, ".minigit/addedFiles/" + fileName);

    std::cout << "File: " << fileName << " Added\n";
}
