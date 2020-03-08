/*
 * Created on Sat Mar 07 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include <iostream>
#include <string>

#include "common/user_interrupt.h"
#include "gflags/gflags.h"

using namespace web;
using namespace web::http::experimental::listener;
using namespace web::json;

DEFINE_string(port, "8080", "server port");
DEFINE_string(host, "http://localhost", "server address");

void SendResponse(unsigned status_code,
                  const http::http_request& request,
                  const std::string& message,
                  bool error) {
    auto response = json::value::object();
    response["error"] = json::value::boolean(error);
    response["message"] = json::value::string(message);
    request.reply(status_code, response);
}

int main(int argc, char* argv[]) {
    gflags::SetUsageMessage("rest -port <PORT> -host <HOST>");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    UserInterrupt::Register();

    std::string host = FLAGS_host + ":" + FLAGS_port;

    auto listener = http_listener(host);

    // start http server
    listener.open().wait();
    std::cout << "Listening for HTTP requests at " << host << '\n';

    // handle GET request
    listener.support(http::methods::GET,
        [](const http::http_request& request){
        SendResponse(http::status_codes::OK, request, "Success", false);
    });

    // handle POST request
    listener.support(http::methods::POST,
        [](const http::http_request& request) {
        request.extract_json().then([&request](json::value data){
            try {
                auto key = data.at("key").as_string();
                auto value = data.at("value").as_string();
                std::cout << "Key: " << key << " "
                          << "Value: " << value << '\n';
                SendResponse(http::status_codes::OK,
                             request, "Success", false);
            } catch(const json::json_exception& e) {
                SendResponse(http::status_codes::BadRequest,
                             request, "Failure", true);
            }
        }).wait();
    });

    // wait for user interrupt
    UserInterrupt::Wait();

    // shutdown http server
    listener.close().wait();

    return 0;
}
