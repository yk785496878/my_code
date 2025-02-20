#pragma once
#include "msg_base.h"

/**
 * example 1
 */
class Msg1 : public MsgBase
{
public:
    Msg1();
    Msg1(const double ts, const double ts_rcv, const unsigned int frame_id);
    void CopyFrom(const std::shared_ptr<Msg1> ptr);
    void PrintMsgInfo();

private:
    int m_msg_1_data;
};