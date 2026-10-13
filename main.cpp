#include "FileIndexer.h"

#include <iostream>
#include <string>
#include <exception>

int main()
{
    FileIndexer indexer;

    while (true)
    {
        std::cout << "\n========== FileIndexer V5 ==========\n";
        std::cout << "1. 扫描目录\n";
        std::cout << "2. 显示所有文件\n";
        std::cout << "3. 按文件名搜索\n";
        std::cout << "4. 按文件后缀筛选\n";
        std::cout << "5. 按大小升序排序\n";
        std::cout << "6. 按大小降序排序\n";
        std::cout << "7. 保存索引\n";
        std::cout << "8. 加载索引\n";
        std::cout << "0. 退出程序\n";
        std::cout << "请选择：";

        std::string choice;

        if (!std::getline(std::cin, choice))
        {
            break;
        }

        if (choice == "0")
        {
            std::cout << "程序退出\n";
            break;
        }

        try
        {
            if (choice == "1")
            {
                std::string path;

                std::cout << "请输入目录路径：";
                std::getline(std::cin, path);

                indexer.scanDirectory(path);
                std::cout << "扫描完成\n";
            }
            else if (choice == "2")
            {
                indexer.showFiles();
            }
            else if (choice == "3")
            {
                std::string name;

                std::cout << "请输入文件名：";
                std::getline(std::cin, name);

                indexer.findByName(name);
            }
            else if (choice == "4")
            {
                std::string extension;

                std::cout << "请输入文件后缀，例如 .cpp：";
                std::getline(std::cin, extension);

                indexer.showByExtension(extension);
            }
            else if (choice == "5")
            {
                indexer.sortBySize(true);
                indexer.showFiles();
            }
            else if (choice == "6")
            {
                indexer.sortBySize(false);
                indexer.showFiles();
            }
            else if (choice == "7")
            {
                indexer.saveIndex("index.txt");
            }
            else if (choice == "8")
            {
                indexer.loadIndex("index.txt");
            }
            else
            {
                std::cout << "无效选项\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "错误：" << e.what() << '\n';
        }
    }

    return 0;
}