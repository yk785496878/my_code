#pragma once

#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

class Runnable
{
public:
    Runnable() : m_stop(false), m_thread() {}
    virtual ~Runnable()
    {
        try
        {
            stop();
        }
        catch (...)
        { /*??*/
        }
    }
    Runnable(Runnable const &) = delete;
    Runnable &operator=(Runnable const &) = delete;
    void start()
    {
        std::unique_lock<std::mutex> mylock(m_mtx,std::try_to_lock);
        if (!mylock.owns_lock()) {
            return;
        }
        if (!m_running)
        {
            m_running = true;
            m_stop = false;
            m_thread = std::thread(&Runnable::run, this);
        }
    }
    void stop()
    {/*
        std::unique_lock<std::mutex> mylock(m_mtx,try_to_lock);
        if (!mylock.owns_lock()) {
            return;
        }*/
        if (m_running && m_thread.joinable())
        {
            m_stop = true;
            m_cv.notify_one();
            m_thread.join();
            m_running = false;
        }
    }
    bool is_running()
    {
        return m_running;
    }
    bool is_joinable()
    {
        return m_thread.joinable();
    }

    void set_name(const std::string name)
    {
        /*
                #if defined(__linux__)
                    pthread_setname_np(m_thread.native_handle(), name.c_str());
                #elif defined(__APPLE__)
                    pthread_setname_np(name.c_str());
                #elif defined(_WIN32)
                    pthread_setname_np(m_thread.native_handle(), name.c_str());
                #endif
          */
    }

    void notify_one ()
    {
        m_cv.notify_one();
    }

protected:
    virtual void run() = 0;
    // std::atomic<bool> m_stop;
    bool m_stop = false;
    std::condition_variable m_cv;
    bool m_running = false;
    std::mutex m_mtx;

private:
    std::thread m_thread;
};
