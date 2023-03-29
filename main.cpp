#include <iostream>

#include "base/config.h"

int main(int argc, char *argv[])
{
    auto config = JsonConfig::getInstance();
    if (config->LoadFile("./config_file/base_config.json"))
    {
        auto mFilePath = config->Get<std::string>("root_path");
        std::cout << mFilePath << std::endl;
    }

    return 0;
}