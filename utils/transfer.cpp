#include <filesystem>
#include <iostream>
#include <string>

using namespace std::filesystem;
void transferDirToDir(path src, path des, bool inMainDir = false) {

    for (path entry : recursive_directory_iterator(src)) {
        if (inMainDir) {
            if (entry.string().find("./.git") != std::string::npos ||
                entry.string().find("./.minigit") != std::string::npos) {
                continue;
            }
        }

        if (is_directory(entry)) {
            create_directory(des / entry);
            continue;
        }

        copy_file(entry, des / entry);
    }
}
