#include "disp_service.h"
#include "./defines.h"
#include <iostream>
BEGIN_NS_AD
DispService::DispService()
{
}

DispService::~DispService()
{
}

DispService &DispService::GetInstance()
{
    static DispService instance;
    return instance;
}

void DispService::Release()
{
    std::lock_guard<std::mutex> guard(m_mtx);
    auto itP = m_publishers.begin();
    while (itP != m_publishers.end())
    {
        itP->second->stop();
        itP++;
    }

    m_publishers.clear();
    m_listeners.clear();
}

bool DispService::Reg(const std::shared_ptr<CommListener> &pl)
{
    std::lock_guard<std::mutex> guard(m_mtx);
    if (m_listeners.find(pl->GetID()) != m_listeners.end())
    {
        std::cout << "Listener already registered" << std::endl;
        return false;
    }

    if (pl)
    {
        std::cout << "reg Listener" << std::endl;
        m_listeners.insert(std::map<std::string, std::shared_ptr<CommListener>>::value_type(pl->GetID(), pl));
        auto pub = std::shared_ptr<MsgHandler>(new MsgHandler(pl));
        m_publishers.insert(std::map<std::string, std::shared_ptr<MsgHandler>>::value_type(pl->GetID(), pub));
    }

    return true;
}

bool DispService::UnReg(const std::shared_ptr<CommListener> &pl)
{
    bool bReturn = false;
    std::lock_guard<std::mutex> guard(m_mtx);
    auto itP = m_publishers.find(pl->GetID());
    if (itP != m_publishers.end())
    {
        itP->second->stop();
        m_publishers.erase(itP);
        bReturn = true;
    }

    auto it = m_listeners.find(pl->GetID());
    if (it != m_listeners.end())
    {
        m_listeners.erase(it);
        bReturn = true;
    }

    return bReturn;
}

END_NS_AD
