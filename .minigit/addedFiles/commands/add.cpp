#include <filesystem>
#include <iostream>
#include <string>

void fileAdd(const std::string &fileName) {
    namespace fs = std::filesystem;

    if (fileName == ".") {
        fs::remove_all("./.minigit/addedFiles");
        fs::create_directory("./.minigit/addedFiles");

        for (const auto &entry : fs::recursive_directory_iterator(".")) {
            const auto &path = entry.path();

            if (path.string().find("/.git") != std::string::npos ||
                path.string().find("/.minigit") != std::string::npos) {
                continue;
            }

            fs::path relativePath = fs::relative(path, ".");
            fs::path targetPath =
                fs::path("./.minigit/addedFiles") / relativePath;

            if (fs::is_directory(path)) {
                fs::create_directories(targetPath);
            } else if (fs::is_regular_file(path)) {
                fs::copy_file(path, targetPath,
                              fs::copy_options::overwrite_existing);

                std::cout << relativePath.string() << " ADDED.\n";
            }
        }

        return;
    }

    if (!fs::exists(fileName)) {
        std::cout << "File: " << fileName << " doesn't exist";
        return;
    }

    fs::path dest = fs::path(".minigit/addedFiles") / fileName;

    fs::create_directories(dest.parent_path());
    fs::copy_file(fileName, dest, fs::copy_options::overwrite_existing);

    std::cout << "File: " << fileName << " Added\n";
}
