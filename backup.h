#ifndef BACKUP_H
#define BACKUP_H

#include <filesystem>

// Defined in backup.cpp:
std::filesystem::path create_backup(const std::filesystem::path& source_path);

#endif