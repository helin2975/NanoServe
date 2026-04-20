#include "HTTPRequest.h"
#include <sstream>

HTTPRequest::HTTPRequest(const std::string& raw_request) {
    if (raw_request.empty()) {
        method  = "";
        uri     = "/";
        version = "HTTP/1.1";
        return;
    }

    std::istringstream stream(raw_request);
    stream >> method >> uri >> version;

    if (method.empty()) method   = "GET";
    if (uri.empty())    uri      = "/";
    if (version.empty()) version = "HTTP/1.1";
}