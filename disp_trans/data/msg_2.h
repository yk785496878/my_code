#pragma once
#include "msg_base.h"

/**
 * example 2
 */
class Msg2 : public MsgBase
{
public:
    Msg2();
    Msg2(const double ts, const double ts_rcv, const unsigned int frame_id);
    void CopyFrom(const std::shared_ptr<Msg2> ptr);
    void PrintMsgInfo();

private:
    int m_msg_2_data;
};