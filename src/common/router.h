/*
 * Created on Sat Mar 14 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#ifndef SRC_COMMON_ROUTER_H_
#define SRC_COMMON_ROUTER_H_

#include <memory>
#include <cpprest/http_listener.h>

#include "./server.h"

using namespace web;
using namespace http;
using namespace web::http::experimental::listener;

class Router {
public:
    explicit Router(const std::unique_ptr<Server>& server);

private:
    void HandleRequest(const http_request& message);
};

#endif  // SRC_COMMON_ROUTER_H_
