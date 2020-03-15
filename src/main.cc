/*
 * Created on Sat Mar 07 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include <iostream>
#include <string>
#include <memory>

#include "gflags/gflags.h"
#include "common/user_interrupt.h"
#include "common/server.h"
#include "common/router.h"

DEFINE_string(port, "8080", "server port");
DEFINE_string(host, "http://localhost", "server address");

using std::make_unique;

int main(int argc, char* argv[]) {
    gflags::SetUsageMessage("rest -port <PORT> -host <HOST>");
    gflags::SetVersionString("1.0.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    UserInterrupt::Register();

    std::string host = FLAGS_host + ":" + FLAGS_port;
    auto server = make_unique<Server>(host);

    Router router(server);

    // Start server and wait for requests
    server->Start().wait();
    UserInterrupt::Wait();

    // Shutdown server and clean up
    server->Shutdown();
    return 0;
}
