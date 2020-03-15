/*
 * Created on Sat Mar 14 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#ifndef SRC_COMMON_SERVER_H_
#define SRC_COMMON_SERVER_H_

#include <cpprest/http_listener.h>
#include <string>

using namespace web;
using namespace web::http::experimental::listener;

class Server {
public:
    explicit Server(const std::string& host);

    pplx::task<void> Start();
    pplx::task<void> Shutdown();

    http_listener& listener() {
        return listener_;
    }

private:
    http_listener listener_;
    std:: string host_;
};

#endif  // SRC_COMMON_SERVER_H_
