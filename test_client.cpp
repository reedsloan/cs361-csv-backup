// Requests a missing file first, then requests five backups of sample.csv.
// Prints each response so we can see the error and the five backup paths.
#include "third_party/httplib.h"
#include "third_party/json.hpp"

#include <filesystem>
#include <iostream>

using json = nlohmann::json;
namespace fs = std::filesystem;

bool request_backup(httplib::Client& client, const fs::path& source_path,
                    int expected_status)
{
    json input = {{"source_path", source_path.string()}};
    auto response = client.Post("/backup", input.dump(), "application/json");

    if (!response)
    {
        std::cerr << "Could not reach the backup service.\n";
        return false;
    }

    std::cout << response->status << " " << response->body << '\n';
    return response->status == expected_status;
}

int main()
{
    httplib::Client client("127.0.0.1", 8362);

    if (!request_backup(client, fs::absolute("missing.csv"), 404))
    {
        return 1;
    }

    for (int number = 1; number <= 5; ++number)
    {
        if (!request_backup(client, fs::absolute("sample.csv"), 201))
        {
            return 1;
        }
    }

    return 0;
}
