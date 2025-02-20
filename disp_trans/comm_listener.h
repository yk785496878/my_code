
#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include <thread>
#include <chrono>

#include "./defines.h"
#include "./data/structs.h"
#include "./data/msg_1.h"
#include "./data/msg_2.h"


BEGIN_NS_AD
/**
 * @brief
 *
 */
// class COMM_API CommListener
class CommListener
{
public:
    /**
     * @brief Construct a new Comm Listener object
     *
     */
    CommListener();
    /**
     * @brief Construct a new Comm Listener object
     *
     * @param name
     */
    explicit CommListener(const char *name);
    /**
     * @brief Destroy the Comm Listener object
     *
     */
    virtual ~CommListener() {};

    /**
     * @brief Msg1
    */
    virtual void OnMsg1(const std::shared_ptr<Msg1> ptr){};

    /**
     * @brief Msg2
    */
    virtual void OnMsg2(const std::shared_ptr<Msg2> ptr){};

public:
    /**
     * @brief
     *
     * @param id
     */
    void SetID(const char *id);

    /**
     * @brief
     *
     * @return char*
     */
    char *GetID();

protected:
    /**
     * @brief
     *
     */
    std::string strID;
};
END_NS_AD
