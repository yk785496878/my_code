#include "zmq_subscriber.h"
#include <iostream>

ZmqStructSend *ZmqStructSend::mInstance = NULL;

ZmqStructSend *ZmqStructSend::getInstance() {
    if (mInstance == NULL) {
        std::string sub_ip = "*";
        int sub_port = 5009;
        std::cout << sub_ip <<std::endl;
        mInstance = new ZmqStructSend("tcp://" + sub_ip + ":" + std::to_string(sub_port));
        static Recovery recvory;
    }

    return mInstance;
}

ZmqStructSend::ZmqStructSend(const std::string &address)
    : mContext(1), mPublisher(mContext, ZMQ_PUB) {
    mPublisher.bind(address);
}

ZmqStructSend::~ZmqStructSend() { StopStruct(); }

void ZmqStructSend::AddStructData(SaveBufferIndex index_data, const std::string &data) {

    auto it = mCounter.find(index_data.topic_id);
    if (it == mCounter.end()) {
        mCounter[index_data.topic_id] = 0;
        it = mCounter.find(index_data.topic_id);
    } else {
        it->second++;
    }
    if (!mStop) {
        zmq::message_t msg(data.size() + sizeof(index_data) + 8);
        memcpy(msg.data(), &(it->second), sizeof(int32_t));
        memcpy(msg.data() + 4, &index_data.topic_id, sizeof(int32_t));
        memcpy(msg.data() + 4 + 4, &index_data, sizeof(index_data));
        memcpy(msg.data() + 4 + 4 + sizeof(index_data), data.c_str(), data.size());
        std::lock_guard<std::mutex> lock(mMutex);
        mData.push_back(std::move(msg));
        mCond.notify_all();
    }
}

void ZmqStructSend::StartStruct() {
    mStop = false;
    mThread = std::thread(&ZmqStructSend::Run, this);
}

void ZmqStructSend::StopStruct() {
    mStop = true;
    mCond.notify_all();
    if (mThread.joinable()) {
        mThread.join();
    }
}

void ZmqStructSend::Run() {
    while (!mStop) {
        while (mData.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // std::cout <<"no data" <<std::endl;
            if(mStop){
                break;
            }
            continue;
        }
        std::lock_guard<std::mutex> lock(mMutex);
        auto it = mData.begin();
        while (it != mData.end()) {
            mPublisher.send(std::move(*it), zmq::send_flags::none);
            it++;
        }
        // std::cout <<"send data" <<std::endl;
        mData.clear();
    }
}