#pragma once

#include<thread>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<stdio.h>

template <class T>
class ThreadSafeQueue{
    public:
        void Insert(T value);
        bool Popup(T &value);
        bool Empty() const;
		unsigned int Size() const;
        void Notify();

    private:
        mutable std::mutex mut_;
        std::queue<T> que_;
        std::condition_variable cond_;
        int timeout_ms_ = 800;
};

template <class T>
void ThreadSafeQueue<T>::Insert(T value){
    std::lock_guard<std::mutex> lk(mut_);
    que_.push(value);
    cond_.notify_one();
}

template <class T>
void ThreadSafeQueue<T>::Notify(){
    cond_.notify_one();
}


template <class T>
bool ThreadSafeQueue<T>::Popup(T &value){
    std::unique_lock<std::mutex> lk(mut_);
    auto b = cond_.wait_until(lk, std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms_), [this]{return !que_.empty();}); // 如果lamda表达式 [this]{return !que_.empty(); 返回 true, 也就是队列非空，则上锁，继续执行下面的语句；
    if (b) {
        value = que_.front();                          // 如果lamda表达式返回False, 也就是队列为空，则解开锁，该线程进入wait，阻塞模式，等待被唤醒
        que_.pop();
    }
    return b;
}


template <class T>
bool ThreadSafeQueue<T>::Empty() const{
    std::lock_guard<std::mutex> lk(mut_);
    return que_.empty();
}

template <class T>
unsigned int ThreadSafeQueue<T>::Size() const{
    std::lock_guard<std::mutex> lk(mut_);
    return que_.size();
}
