/*
 * Created on Sat Mar 14 2020 by Shlomi Nissan
 * Copyright (c) 2020 Betamark
 */

#include <iostream>

#include "./server.h"

Server::Server(const std::string& host)
    : host_(host),
      listener_(http_listener(host)) {}

pplx::task<void> Server::Start() {
    std::cout << "Listening for HTTP requests at " << host_ << '\n';
    return listener_.open();
}

pplx::task<void> Server::Shutdown() {
    std::cout << "Shutting down\n";
    return listener_.close();
}
