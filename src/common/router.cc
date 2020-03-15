/*
 * Created on Sat Mar 14 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#include "./router.h"

#include <cpprest/json.h>
#include <iostream>

Router::Router(const std::unique_ptr<Server>& server) {
    server->listener().support(methods::GET,
        std::bind(&Router::HandleRequest, this, std::placeholders::_1));

    server->listener().support(methods::POST,
        std::bind(&Router::HandleRequest, this, std::placeholders::_1));
}

void Router::HandleRequest(const http_request& request) {
    auto response = json::value::object();
    response["error"] = json::value::boolean(false);
    response["message"] = json::value::string("success");
    request.reply(http::status_codes::OK, response);
}