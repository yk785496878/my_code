#include "msg_2.h"
#include <iostream>
Msg2::Msg2() : MsgBase() {
    m_data_type = MSG_1;
    m_msg_2_data = 0;
}

Msg2::Msg2(const double ts, const double ts_rcv, const unsigned int frame_id) : MsgBase(ts, ts_rcv, frame_id)
{
    m_data_type = MSG_1;
    m_msg_2_data = 0;
}

void Msg2::CopyFrom(const std::shared_ptr<Msg2> ptr)
{
    MsgBase::CopyFrom(ptr);
    m_msg_2_data = ptr->m_msg_2_data;
}

void Msg2::PrintMsgInfo()
{
    std::cout << "type = " << GetMsgStr(m_data_type) << " timestamp = " << GetTimestamp() << " ts_rcv = " << GetTimestampRcv() << " frame_id = " << GetFrameId() << std::endl;
    std::cout << "Msg2: m_msg_2_data = " << m_msg_2_data << std::endl;
}