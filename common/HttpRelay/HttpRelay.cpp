#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

using namespace std;
namespace beast = boost::beast;
using namespace boost::asio;
namespace http = beast::http;
using tcp = boost::asio::ip::tcp;

#include "HttpRelay.h"
using namespace PatternCapture;

HttpRelayDependency :: HttpRelayDependency(string url, string method, string payload, HookType hookType) : url(url), method(method), payload(payload), hookType(hookType) { }


string HttpRelayDependency :: getOutput(string input, map<string, string> inputParams) { }


void HttpRelayDependency :: executeHook(const Node &node) {

}

HookType HttpRelayDependency :: getHookType() {
    return hookType;
}

string HttpRelayDependency :: getResponse() const {

    boost::asio::io_context ioc;

}


