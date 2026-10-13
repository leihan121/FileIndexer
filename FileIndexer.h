#pragma once
#include "FileInfo.h"
#include <string>
#include <vector>

class FileIndexer
{
    private:
        std::vector<FileInfo> files;
    public:
        void scanDiectoy(const std::sting& path);
        void showFiles() const;
        void findByName(const std::string& name) const;
        void showByExtension(const std::string& extension) const;
        void sortBySize(bool ascending);
        void saveIndex(const std::string& filename) const;
        void loadIndex(const std::string& filename);    
};