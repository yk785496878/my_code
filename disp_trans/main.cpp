#include <iostream>
#include "disp_service.h"
#include "data/msg_1.h"
#include "data/structs.h"

class MyListener : public ad::navi::CommListener
{
private:
    std::mutex mtx;

public:
    void OnMsg1(const std::shared_ptr<Msg1> ptr){
        printf(" receive msg1  \n");
    };

    void OnMsg2(const std::shared_ptr<Msg2> ptr){
        printf(" receive msg2  \n");
    };
};

int main()
{
    MyListener listener;
    auto pl = std::shared_ptr<MyListener>(&listener);
    ad::navi::DispService::GetInstance().Reg(pl);
    auto rt = std::make_shared<Msg1>();
    ad::navi::DispService::GetInstance().Publish(rt, MSG_1, 0);
    std::cout << "Hello World!\n";
    return 0;
}