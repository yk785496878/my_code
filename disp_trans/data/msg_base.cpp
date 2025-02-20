#include "msg_base.h"

MsgBase::MsgBase()
{
    m_timestamp = 0;
    m_ts_rcv = 0;
    m_frame_id = 0;
}

MsgBase::MsgBase(const double timestamp, const double ts_rcv, const unsigned int frame_id)
{
    m_timestamp = timestamp;
    m_ts_rcv = ts_rcv;
    m_frame_id = frame_id;
}

void MsgBase::CopyFrom(const std::shared_ptr<MsgBase> ptr)
{
    m_timestamp = ptr->GetTimestamp();
    m_ts_rcv = ptr->GetTimestampRcv();
    m_frame_id = ptr->GetFrameId();
    m_data_type = ptr->GetType();
}

std::string MsgBase::GetMsgStr(const MsgType type)
{
    switch (type)
    {
    case MSG_1:
    {
        return "MSG_TYPE_1";
    }
    break;

    case MSG_2:
    {
        return "MSG_TYPE_2";
    }
    break;
    }    
    return std::string("");
}