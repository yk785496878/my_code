#pragma once
#include <string>
#include <memory>

#include "structs.h"

class MsgBase
{
public:
    MsgBase();
    MsgBase(const double ts, const double ts_rcv, const unsigned int frame_id);
    virtual ~MsgBase(){};

    /**
     * @brief Get the type of the message
     */
    MsgType GetType() const { return m_data_type; };

    /**
     * @brief Get the frame id of the message
     */
    unsigned int GetFrameId() const {return m_frame_id;};

    /**
     * @brief Set the frame id of the message
     */
    void SetFrameId(const unsigned int id){m_frame_id = id;};

    /**
     * @brief Get the timestamp of the message
     */
    double GetTimestamp() const {return m_timestamp;};

    /**
     * @brief Set the timestamp of the message
     */
    void SetTimestamp(const double ts){m_timestamp = ts;};

    /**
     * @brief Get the timestampRcv of the message
     */
    double GetTimestampRcv() const {return m_ts_rcv;};

    /**
     * @brief Set the timestampRcv of the message
     */
    void SetTimestampRcv(const double ts){m_ts_rcv = ts;};


    virtual void PrintMsgInfo() = 0;
    void CopyFrom(const std::shared_ptr<MsgBase> ptr);

protected:
    std::string GetMsgStr(const MsgType type);

protected:
    double m_timestamp = 0;
    double m_ts_rcv = 0;
    unsigned int m_frame_id = 0;
    MsgType m_data_type;
};