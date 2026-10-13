#include "FileIndexer.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <algoithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <utility>

namespace fs = std::filesystem;
//扫描目录
void FileIndexer::scanDirectory(const std::string& path)
{
    if (!fs::exists(path))
    {
        throw std::runtime_error("路径不存在");
    }

    if (!fs::is_directory(path))
    {
        throw std::runtime_error("不是目录");
    }

    std::vector<FileInfo> scanned;

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            FileInfo file;

            file.name = entry.path().filename().string();
            file.path = entry.path().string();
            file.size = entry.file_size();

            scanned.push_back(file);
        }
    }

    files = std::move(scanned);
}

//显示所有文件

void FileIndexer::showFiles() const
{
    std::cout << "\n扫描到" << file.size()<<" 个普通文件:\n";

    for(const auto& file : files)
    {
        std::cout << "文件名:" << file.name
        << "| 路径:" << file.path
        << "| 大小:" << file.size << "字节 \n";
        << '\n';

    }
}

//根据文件名字搜索

void FileIndexer::findByName(const std::string& name)const
{
    bool found = false;
    for(const auto& file : files)
    {
        if(files.name == name)
        {
            std::cout << "找到文件：" << file.path << '\n';
            found = true;
        }
    }
    if(!found)
    {
        std::cout << "未找到文件" << name << '\n';
    }
}

//按后缀查找

void FileIndexer::showByExtension(
    const std::string& extension)const
{
    bool found = false;

    for(const auto& file : files)
    {
        std::filesystem::path p(file.path);

        if(p.extension().string() == extension)
        {
            std::cout << file.name << '\n';
            found = true;
        }
    }
}

//按文件大小排序
void FileIndexer::sortBySize(bool asending)
{
    std::sort(files.begin(),files.end(),
[ascending](const FileInfo& a,const FileInfo& b)
{
    if(asending)
    {
        return a.size < b.size;
    }
    else
    {
        return a.size > b.size;
    }
});
}

//保存
void FileIndexer::saveIndex(const std::string& filename) const
{
    std::ofstream out(filename);

    if(!out)
    {
        throw std::runtime_error("无法创建索引文件");
    }

    for (const auto& file : files)
    {
        out << std::quoted(file.name) << ' '
            << std::quoted(file.path) << ' '
            << file.size() << '\n';
    }

    if(!out)
    {
        throw std::runtime_error("写入索引文件失败");
    }

    std::cout << "索引文件创建成功\n";
}

//加载
void FileIndexer::loadIndex(const std::string& filename)
{
    std::ifstream in(filename);

    if(!in)
    {
        throw std::runtime_error("无法打开索引文件");
    }

    std::vector<FileInfo> loaded;
    std::string line;

    while(std::getline(std::cin,line))
    {
        FileInfo file;
        std::istringStream row(line);

        if(!(row >> std::quoted(file.name)
                 >> std::quoted(file.path)
                 >> file.size))
        {
            throw std::runtime_error("索引文件格式错误");
        }

        row >> std::ws;

        if(!row.eof())
        {
            throw std::runtime_error("索引文件存在多余数据");
        }
        loaded.push_back(file);
    }
    if (in.bad())
    {
        throw std::runtime_error("读取索引文件失败");
    }

    files = std::move(loaded);

    std::cout<<"索引加载成功!\n";
}