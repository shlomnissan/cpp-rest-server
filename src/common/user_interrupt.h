/*
 * Created on Sat Mar 07 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#ifndef USER_INTERRUPT_H_ 
#define USER_INTERRUPT_H_

#include <condition_variable>
#include <mutex>
#include <iostream>
#include <csignal>

static std::condition_variable condition;
static std::mutex mutex;

class UserInterrupt {
public:
    static void Register() {
        signal(SIGINT, Handle);
    }

    static void Handle(int signal){
        if (signal == SIGINT) {
            condition.notify_one();
        }
    }

    static void Wait() {
        std::unique_lock<std::mutex> lock { mutex };
        condition.wait(lock);
        std::cout << "The service was interrupted" << "\n";
        lock.unlock();
    }
};

#endif  // USER_INTERRUPT_H_