#ifndef _ZMQSUBSCRIBER_H_
#define _ZMQSUBSCRIBER_H_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <map>
#include <thread>
#include <unordered_map>

#include "zmq.hpp"

struct SaveBufferIndex {
    std::uint32_t topic_id;
    std::uint32_t data_size;
    std::uint32_t pps_hit_id;
    std::uint64_t time_recv;
};

typedef struct {
    uint32_t datatype;
    uint32_t frameIndex;
    uint32_t datasize;
} To_Record_Header;
typedef struct {
    To_Record_Header head;
    std::string data;
} To_Record_Data;

class ZmqStructSend {
public:
    static ZmqStructSend* getInstance();

    ~ZmqStructSend();
    void AddStructData(SaveBufferIndex index_data, const std::string& data);
    void StartStruct();
    void StopStruct();
    void Run();

    class Recovery {
    public:
        ~Recovery() {
            if (ZmqStructSend::mInstance) {
                delete ZmqStructSend::mInstance;
                ZmqStructSend::mInstance = NULL;
            }
        }
    };

private:
    static ZmqStructSend* mInstance;
    ZmqStructSend(const std::string& address);

    zmq::context_t mContext;
    zmq::socket_t mPublisher;
    std::thread mThread;
    std::mutex mMutex;
    std::condition_variable mCond;
    std::list<zmq::message_t> mData;
    bool mStop;

    std::unordered_map<uint32_t, uint32_t> mCounter;

    int i = 0;
};
#endif