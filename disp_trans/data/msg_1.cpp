#include "msg_1.h"
#include <iostream>

Msg1::Msg1() : MsgBase() {
    m_data_type = MSG_1;
    m_msg_1_data = 0;
}

Msg1::Msg1(const double ts, const double ts_rcv, const unsigned int frame_id) : MsgBase(ts, ts_rcv, frame_id)
{
    m_data_type = MSG_1;
    m_msg_1_data = 0;
}

void Msg1::CopyFrom(const std::shared_ptr<Msg1> ptr)
{
    MsgBase::CopyFrom(ptr);
    m_msg_1_data = ptr->m_msg_1_data;
}

void Msg1::PrintMsgInfo()
{
    std::cout << "type = " << GetMsgStr(m_data_type) << " timestamp = " << GetTimestamp() << " ts_rcv = " << GetTimestampRcv() << " frame_id = " << GetFrameId() << std::endl;
    std::cout << "Msg1: m_msg_1_data = " << m_msg_1_data << std::endl;
}