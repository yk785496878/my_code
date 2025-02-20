#pragma once

#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

#include "./common/runner.h"
#include "./comm_listener.h"
#include "./common/safe_queue.h"
#include "./data/structs.h"
#include "./data/msg_base.h"

BEGIN_NS_AD
class MsgHandler : public Runnable
{
public:
    MsgHandler();
    MsgHandler(const std::shared_ptr<CommListener> listener);
    virtual ~MsgHandler();
    void AddData(const std::shared_ptr<MsgBase> ptr);

protected:
    void run() override;
    void Notify(const std::shared_ptr<MsgBase> ptr);

protected:
    std::shared_ptr<CommListener> m_listener;
    ThreadSafeQueue<std::shared_ptr<MsgBase>> m_queue;
};
END_NS_AD