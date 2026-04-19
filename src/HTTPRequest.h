#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>

class HTTPRequest {
private:
    std::string method;
    std::string uri;
    std::string version;

public:
    HTTPRequest(const std::string& raw_request);

    std::string getMethod()  const { return method;  }
    std::string getURI()     const { return uri;     }
    std::string getVersion() const { return version; }
};

#endif