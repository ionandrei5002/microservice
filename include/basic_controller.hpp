#pragma once

#include <string>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include "controller.hpp"
#include "network_utils.hpp"

using namespace web;
using namespace http::experimental::listener;

namespace cfx {
    class BasicController {
    protected:
        http_listener _listener; // main micro service network endpoint

    public:
        BasicController() {}
        virtual ~BasicController() {}

        void setEndpoint(const std::string & value) {
            uri endpointURI(value);
            uri_builder endpointBuilder;

            endpointBuilder.set_scheme(endpointURI.scheme());
            if (endpointURI.host() == "host_auto_ip4") {
                endpointBuilder.set_host(NetworkUtils::hostIP4());        
            }
            else if (endpointURI.host() == "host_auto_ip6") {
                endpointBuilder.set_host(NetworkUtils::hostIP6());
            }
            endpointBuilder.set_port(endpointURI.port());
            endpointBuilder.set_path(endpointURI.path());

            _listener = http_listener(endpointBuilder.to_uri());
        }

        std::string endpoint() const {
            return _listener.uri().to_string();
        }

        pplx::task<void> accept() {
            initRestOpHandlers();
            return _listener.open();
        }

        pplx::task<void> shutdown() {
            return _listener.close();
        }

        std::vector<utility::string_t> requestPath(const http_request & message) {
            auto relativePath = uri::decode(message.relative_uri().path());
            return uri::split_path(relativePath);        
        }

        virtual void initRestOpHandlers() { 
            /* had to be implemented by the child class */ 
        }
    };
}