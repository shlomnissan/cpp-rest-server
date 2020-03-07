/*
 * Created on Sat Mar 07 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#include <iostream>
#include <string>

#include <cpprest/http_listener.h>

#include "common/user_interrupt.h"
#include "gflags/gflags.h"

using namespace web::http::experimental::listener;

DEFINE_string(port, "8080", "server port");
DEFINE_string(host, "http://localhost", "server address");

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
    
    // wait for user interrupt
    UserInterrupt::Wait();
    
    // shutdown http server
    listener.close().wait();

    return 0;
}