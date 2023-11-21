#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "zmq_subscriber.h"

// #define SENDDATA
#ifdef SENDDATA

int main(int argc, char** argv) {
    std::ifstream file("./config_file/base_config.json");
    nlohmann::json j;
    file >> j;

    std::string filePath = j["root_path"].get<std::string>();

    // std::ifstream ifs(
    //     "/home/yankun/Desktop/"
    //     "data_2023-09-04-11-13-21_msg_1.1.0_mainversion_default.bin",
    //     std::ios::binary);
    std::ifstream ifs(filePath.c_str(), std::ios::binary);
    if (!ifs.is_open()) {
        std::cout << "-----hhhh---";
        return 0;
    }

    std::string serialized_data_cache;
    char ptr[128 * 1024] = {};

    ZmqStructSend::getInstance()->StartStruct();
    int i = 0;

    while (true) {
        while (ifs.peek() != EOF) {
            // To_Record_Header a;
            // ifs.read((char*)&(a), sizeof(To_Record_Header));

            SaveBufferIndex aaa;
            ifs.read((char*)&(aaa), sizeof(SaveBufferIndex));
            // if(aaa.topic_id == 410){
            //     std::cout << "-----topic_id---" << aaa.topic_id << "---time_recv---" <<
            //     aaa.time_recv
            //           << "--size---" << aaa.data_size << std::endl;
            // }
            // std::cout << "-----topic_id---" << aaa.topic_id << "---time_recv---" << aaa.time_recv
            //           << "--size---" << aaa.data_size << std::endl;

            ifs.read(ptr, aaa.data_size);
            serialized_data_cache.assign(ptr, aaa.data_size);
            ZmqStructSend::getInstance()->AddStructData(aaa, serialized_data_cache);
            i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        ifs.clear();
        ifs.seekg(0, std::ios::beg);
    }

    ifs.close();

    std::cout << "end" << i;
    ZmqStructSend::getInstance()->StopStruct();
    return 0;
}

#endif

#define MULTSENDDATA
#ifdef MULTSENDDATA

int main(int argc, char** argv) {
    std::ifstream file("./config_file/base_config.json");
    nlohmann::json j;
    file >> j;

    std::string allFilePath = j["root_path"].get<std::string>();
    std::vector<std::string> filePaths;

    std::stringstream ss(allFilePath);
    std::string token;

    while (getline(ss, token, ';')) {
        filePaths.push_back(token);
    }

    for (const auto& str : filePaths) {
        std::cout << str << std::endl;
    }
    std::string serialized_data_cache;
    char ptr[128 * 1024] = {};

    ZmqStructSend::getInstance()->StartStruct();
    int i = 0;

    while (true) {
        for (const auto& filePath : filePaths) {
            std::ifstream ifs(filePath.c_str(), std::ios::binary);
            std::cout << filePath <<std::endl;
            if (!ifs.is_open()) {
                std::cout << "-----hhhh---";
                return 0;
            }
            while (ifs.peek() != EOF) {
                SaveBufferIndex aaa;
                ifs.read((char*)&(aaa), sizeof(SaveBufferIndex));
                ifs.read(ptr, aaa.data_size);
                serialized_data_cache.assign(ptr, aaa.data_size);
                ZmqStructSend::getInstance()->AddStructData(aaa, serialized_data_cache);
                i++;
                if(i > 1000){
                    std::cout << "now time stamp is : " << aaa.time_recv << std::endl;
                    i = 0;
                    
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            ifs.close();
        }
    }

    ZmqStructSend::getInstance()->StopStruct();
    return 0;
}

#endif

// #define CHECKDATA

#ifdef CHECKDATA

#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "zmq_subscriber.h"

int main(int argc, char** argv) {
    std::ifstream ifs("/home/20231018_110309/20231018_110839_struct_data.bin", std::ios::binary);
    // std::ofstream ofs(
    //     "/home/yankun/Desktop/"
    //     "data_2023-08-23-18-10-51_msg_1.1.0_mainversion_default.bin",
    //     std::ios::binary);
    if (!ifs.is_open()) {
        std::cout << "-----hhhh---";
        return 0;
    }

    // if (!ofs.is_open()) {
    //     std::cout << "-----ghhh---";
    //     return 0;
    // }

    std::string serialized_data_cache;
    char ptr[1024 * 1024] = {};
    int a[2000] = {0};

    // ZmqStructSend::getInstance()->StartStruct();
    int i = 0;
    int size = 0;
    // while (ifs.peek() != EOF) {
    while (ifs.peek() != EOF) {
        SaveBufferIndex aaa;
        ifs.read((char*)&(aaa), sizeof(SaveBufferIndex));

        if(aaa.topic_id == 1483 && aaa.time_recv < 100){
            std::cout << "-----topic_id---" << aaa.topic_id << "---time_recv---" << aaa.time_recv
                  << "--size---" << aaa.data_size << std::endl;
        }
        

        ifs.read(ptr, aaa.data_size);
        // StructPtr ptr(new To_Record_Data());
        // ifs.read((char*)&(ptr->head), sizeof(ptr->head));
        // std::vector<char> data(ptr->head.datasize);
        // ifs.read(data.data(), ptr->head.datasize);
        // ptr->data.assign(data.begin(), data.end());
        // rawData.emplace_back(ptr);

        // serialized_data_cache.assign(ptr, aaa.data_size);
        // ZmqStructSend::getInstance()->AddStructData(aaa, serialized_data_cache);
        a[aaa.topic_id]++;

        i++;

        // if (i > 109887) {
        //     ofs.write((char*)&a, sizeof(To_Record_Header));
        //     // ofs.write((char*)&aaa, sizeof(SaveBufferIndex));
        //     ofs.write(ptr, a.head.datasize);
        //     ofs.flush();
        // }
    }

    ifs.close();
    // ofs.close();

    std::cout << "end" << i;
    for (int i = 0; i < 2000; i++) {
        if (a[i] != 0) {
            std::cout << "data   topic:" << i << "  ------  " << a[i] << std::endl;
        }
    }
    // ZmqStructSend::getInstance()->StopStruct();
    return 0;
}

#endif