#include <filesystem>
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

        path relativePath = relative(entry, src);

        if (is_directory(entry)) {
            create_directories(des / relativePath);
            continue;
        }

        if (is_regular_file(entry)) {
            copy_file(entry, des / relativePath,
                      copy_options::overwrite_existing);
        }
    }
}
