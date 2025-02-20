#include "msg_handler.h"

#include <memory>

#include "./defines.h"

#define MAX_REPORT 500
#define MAX_REPORT_2 1000

BEGIN_NS_AD
MsgHandler::MsgHandler()
{
    start();
}

MsgHandler::MsgHandler(const std::shared_ptr<CommListener> listener) : m_listener(listener)
{
    start();
}

MsgHandler::~MsgHandler()
{
    stop();
}

void MsgHandler::run()
{
    while (!m_stop)
    {
        std::shared_ptr<MsgBase> msg = nullptr;
        if (m_queue.Popup(msg))
        {
            Notify(msg);
        }
    }
}

void MsgHandler::Notify(const std::shared_ptr<MsgBase> ptr)
{
    if (!m_listener || !ptr)
    {
        return;
    }
    switch (ptr->GetType())
    {
    case MSG_1:
    {
        auto data = std::dynamic_pointer_cast<Msg1>(ptr);
        m_listener->OnMsg1(data);
    }
    break;
    case MSG_2:
    {
        auto data = std::dynamic_pointer_cast<Msg2>(ptr);
        m_listener->OnMsg2(data);
    }
    break;
                
    default:
        break;
    }
}

void MsgHandler::AddData(const std::shared_ptr<MsgBase> ptr)
{
    if (!ptr)
        return;

    auto num = m_queue.Size();
    // bool b1 =  num <= MAX_REPORT || (ptr->GetDataType() == MSG_LANE_CHANGE) \
    // || (ptr->GetDataType() == MSG_PILOT_MODE) || (ptr->GetDataType() == MSG_SPEEDLIMIT) \
    // || (ptr->GetDataType() == MSG_LANE_OFFSET) || (ptr->GetDataType() == MSG_VEHICLE_ALARM)\
    // || (ptr->GetDataType() == MSG_BROADCAST);
    bool b2 = num <= MAX_REPORT_2;
    // if (b1 && b2)
    if (b2)
    {
        m_queue.Insert(ptr);
        //std::cout<<"queue_size:"<<m_queue.Size()<<std::endl;
    }
    else
    {
        // COMM_WARN_LOG("discard type={}", ptr->GetDataType());
    }
}

END_NS_AD
