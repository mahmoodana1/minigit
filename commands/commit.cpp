#include "../utils/utils.h"
#include "commands.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

std::string generateUniqueId() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t timeNow = system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&timeNow);

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1000, 9999);
    int randomPart = dist(rng);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%d%m%Y%H%M%S") << std::setw(3)
        << std::setfill('0') << ms.count() << randomPart;

    return oss.str();
}

namespace fs = std::filesystem;
void commitChanges(const std::string &message) {
    if (fs::is_empty(".minigit/addedFiles")) {
        std::cout << "You have to add files before making a commit\n";
        return;
    }

    std::string commitId = generateUniqueId();

    fs::path basePath = fs::path(".minigit/commits");
    fs::path commitPath = basePath / fs::path(commitId);
    fs::create_directory(commitPath);
    fs::create_directory(commitPath.string() + "/files");

    // creating the date string
    auto now = std::chrono::system_clock::now();

    std::time_t cNow = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&cNow);

    std::ostringstream dateString;
    dateString << std::put_time(localTime, "%d%m%Y%H");

    // createing the info.txt file for the commit
    std::ofstream file(commitPath.string() + "/info.txt", std::ios::app);

    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
    }

    file << "CommitId: " << commitId << '\n';
    file << "Date: " << dateString.str() << '\n';
    file << "Message: " << message << '\n';

    file.close();

    // transfering committed files and folders
    transferDirToDir(fs::path(".minigit/addedFiles"),
                     fs::path(commitPath / fs::path("files")));
}
