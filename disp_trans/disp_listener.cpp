#include "disp_listener.h"

#include <random>

int GetUid(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000000);
    return dis(gen);
}

DispListener::DispListener()
{
    m_strID = std::to_string(GetUid());
}

DispListener::DispListener(const char *name){
    m_strID = name;
}

void DispListener::SetID(const char *id){
    // m_strID = id;
    memcpy(&m_strID[0], id, strlen(&id[0]));
}

char* DispListener::GetID(){
    return &m_strID[0];
}