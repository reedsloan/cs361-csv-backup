// Declares the function that takes a CSV path and returns the path to its backup.
#ifndef BACKUP_H
#define BACKUP_H

#include <filesystem>

std::filesystem::path create_backup(const std::filesystem::path& source_path);

#endif
