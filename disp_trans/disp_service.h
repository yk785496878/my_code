#pragma once

#include <thread>
#include <map>

#include "disp_listener.h"

class DispService
{
public:
    DispService();
    virtual ~DispService();

    DispService(const DispService &) = delete;
    DispService &operator=(const DispService &) = delete;
    static DispService &GetInstance();

    bool Reg(const std::shared_ptr<DispListener> &listener);
    bool UnReg(const std::shared_ptr<DispListener> &listener);

    void Release();

    template <class Tex, class EMsgType>
    void Publish(Tex &msg, EMsgType type, unsigned int frame_id)
    {
    }

private:
    std::mutex m_mutex;
    std::map<std::string, std::shared_ptr<DispListener>> m_listeners;
    // std::map<std::string, std::shared
};
