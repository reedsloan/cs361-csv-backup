// Receives a CSV path over HTTP and sends back the location of the backup.
// If the source file is missing, it sends an error and waits for the next request.
#include "backup.h"
#include "third_party/httplib.h"
#include "third_party/json.hpp"

#include <iostream>
#include <string>

using json = nlohmann::json;
namespace fs = std::filesystem;

void handle_backup(const httplib::Request& request, httplib::Response& response)
{
    json input = json::parse(request.body);
    fs::path source_path = input.at("source_path").get<std::string>();
    json result;

    if (!fs::exists(source_path))
    {
        response.status = 404;
        result = {
            {"success", false},
            {"error", "Source file not found: " + source_path.string()}
        };
    }
    else
    {
        fs::path backup_path = create_backup(source_path);

        response.status = 201;
        result = {
            {"success", true},
            {"backup_path", backup_path.string()}
        };
    }

    response.set_content(result.dump(), "application/json");
}

int main()
{
    httplib::Server server;
    server.Post("/backup", handle_backup);

    std::cout << "Starting CSV backup service on port 8362\n";

    if (!server.listen("127.0.0.1", 8362))
    {
        std::cerr << "Could not start the server.\n";
        return 1;
    }

    return 0;
}
