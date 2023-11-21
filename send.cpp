// #include <chrono>
// #include <fstream>
// #include <iostream>
// #include <nlohmann/json.hpp>

// #include "zmq_subscriber.h"

// int main(int argc, char** argv) {
//     std::ifstream ifs(
//         "/home/yankun/Desktop/workspace_yk/sim_send/"
//         "data_2023-07-06-09-55-26_msg_1.0.0_mainversion_01-01-0126-C107.bin",
//         std::ios::binary);
//     if (!ifs.is_open()) {
//         std::cout << "-----hhhh---";
//         return 0;
//     }

//     std::string serialized_data_cache;
//     char ptr[128 * 1024] = {};

//     ZmqStructSend::getInstance()->StartStruct();
//     int i = 0;

//     while (ifs.peek() != EOF) {
//         To_Record_Header a;

//         ifs.read((char*)&(a.head), sizeof(To_Record_Header));
//         std::cout << "-----datatype---" << a.head.datatype << "---frameindex---"
//                   << a.head.frameIndex << "--size---" << a.head.datasize << std::endl;

//         SaveBufferIndex aaa;
//         ifs.read((char*)&(aaa), sizeof(SaveBufferIndex));

//         std::cout << "-----topic_id---" << aaa.topic_id << "---time_recv---" << aaa.time_recv
//                   << "--size---" << aaa.data_size << std::endl;
//         a.datasize = aaa.data_size + sizeof(SaveBufferIndex);
//         a.datatype = aaa.topic_id;
//         a.frameIndex = 0;

//         ifs.read(ptr, aaa.data_size);
//         // serialized_data_cache.assign(ptr, aaa.data_size);
//         ZmqStructSend::getInstance()->AddStructData(aaa, serialized_data_cache);

//         i++;
//     }

//     ifs.close();

//     std::cout << "end" << i;
//     ZmqStructSend::getInstance()->StopStruct();
//     return 0;
// }








// #include <chrono>
// #include <fstream>
// #include <iostream>
// #include <nlohmann/json.hpp>

// #include "zmq_subscriber.h"

// int main(int argc, char** argv) {
//     // std::ifstream ifs(
//     //     "/home/yankun/Desktop/workspace_yk/sim_send/data_2023-06-21-16-18-09_pps_03.08.47.bin",
//     //     std::ios::binary);
//     std::ifstream ifs(
//         "/home/yankun/Desktop/workspace_yk/sim_send/"
//         "data_2023-07-06-09-55-26_msg_1.0.0_mainversion_01-01-0126-C107.bin",
//         std::ios::binary);
//     std::ofstream ofs(
//         "/home/yankun/Desktop/workspace_yk/sim_send/"
//         "mainversion_01-01-0126-C107.bin",
//         std::ios::binary);
//     if (!ifs.is_open()) {
//         std::cout << "-----hhhh---";
//         return 0;
//     }

//     if (!ofs.is_open()) {
//         std::cout << "-----ghhh---";
//         return 0;
//     }

//     std::string serialized_data_cache;
//     char ptr[128 * 1024] = {};

//     // ZmqStructSend::getInstance()->StartStruct();
//     int i = 0;

//     while (ifs.peek() != EOF) {
//         To_Record_Header a;
//         // ifs.read((char*)&(a.head), sizeof(To_Record_Header));

//         // std::cout << "-----datatype---" << a.head.datatype << "---frameindex---"
//         //           << a.head.frameIndex << "--size---" << a.head.datasize << std::endl;

//         // ifs.seekg(a.head.datasize, ifs.cur);

//         SaveBufferIndex aaa;
//         ifs.read((char*)&(aaa), sizeof(SaveBufferIndex));

//         std::cout << "-----topic_id---" << aaa.topic_id << "---time_recv---" << aaa.time_recv
//                   << "--size---" << aaa.data_size << std::endl;
//         a.datasize = aaa.data_size + sizeof(SaveBufferIndex);
//         a.datatype = aaa.topic_id;
//         a.frameIndex = 0;

//         ifs.read(ptr, aaa.data_size);
//         // serialized_data_cache.assign(ptr, aaa.data_size);
//         ZmqStructSend::getInstance()->AddStructData(aaa, serialized_data_cache);

//         i++;
//         // if (aaa.time_recv > 1687336824139 && aaa.time_recv < 1687336981246)
//         {
//             ofs.write((char*)&a, sizeof(To_Record_Header));
//             ofs.write((char*)&aaa, sizeof(SaveBufferIndex));
//             ofs.write(ptr, aaa.data_size);
//             ofs.flush();
//         }
//     }

//     ifs.close();
//     ofs.close();

//     std::cout << "end" << i;
//     // ZmqStructSend::getInstance()->StopStruct();
//     return 0;
// }