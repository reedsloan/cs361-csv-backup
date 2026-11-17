#include "backup.h"
#include <string>

namespace fs = std::filesystem;

fs::path create_backup(const fs::path& source_path)
{
    fs::path backup_folder = source_path.parent_path() / "backups";
    fs::create_directories(backup_folder);

    for (int number = 1; ; ++number)
    {
        std::string name = source_path.stem().string() + "_" +
                           std::to_string(number) + source_path.extension().string();

        fs::path backup_path = backup_folder / name;

        if (fs::copy_file(source_path, backup_path, fs::copy_options::skip_existing))
        {
            return backup_path;
        }
    }
}