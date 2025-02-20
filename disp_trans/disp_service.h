#pragma once

#include <thread>
#include <map>
#include <mutex>

#include "disp_listener.h"
#include "msg_handler.h"
BEGIN_NS_AD
class DispService
{
public:
    DispService();
    virtual ~DispService();

    DispService(const DispService &) = delete;
    DispService &operator=(const DispService &) = delete;
    static DispService &GetInstance();

    bool Reg(const std::shared_ptr<CommListener> &listener);
    bool UnReg(const std::shared_ptr<CommListener> &listener);

    void Release();

    template <class Tex, class EMsgType>
    void Publish(Tex &obj, EMsgType emt, unsigned int frame_id)
    {
        if (!obj) return; 
        std::lock_guard<std::mutex> guard(m_mtx);
        auto it = m_publishers.begin();
        while (it != m_publishers.end())
        {
            auto pl = it->second;
            if (pl)
            {
                pl->AddData(obj);
                pl->notify_one();
            }
            it++;
        }

        obj->PrintMsgInfo();
    }

private:
    std::mutex m_mtx;
    std::map<std::string, std::shared_ptr<CommListener>> m_listeners;
    std::map<std::string, std::shared_ptr<MsgHandler>> m_publishers;
};
END_NS_AD