#include <filesystem>
#include <iostream>
#include <string>

void fileAdd(const std::string &fileName) {
    namespace fs = std::filesystem;

    if (fileName == ".") {
        fs::remove_all("./.minigit/addedFiles");
        fs::create_directory("./.minigit/addedFiles");

        std::string path = ".";

        for (const auto &entry : fs::recursive_directory_iterator(path)) {
            if (entry.path().string().find("/.git") != std::string::npos ||
                entry.path().string().find("/.minigit") != std::string::npos) {
                continue;
            }

            if (fs::is_directory(entry.path())) {
                fs::create_directories((fs::path)("./.minigit/addedFiles") /
                                       entry.path());
                continue;
            }

            fs::copy_file(entry.path(),
                          ((fs::path) "./.minigit/addedFiles") / entry.path());
        }

        return;
    }

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
