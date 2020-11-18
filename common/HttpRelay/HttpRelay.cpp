#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <regex>

#define DOMAIN_REGEX "(?<http.+//).+(?=/)"
#define PATH_REGEX "(?<http.+//.+?/).+$"

using namespace std;
namespace beast = boost::beast;
using namespace boost::asio;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

#include "HttpRelay.h"
using namespace PatternCapture;

HttpRelayDependency :: HttpRelayDependency(string url, string method, string payload, map<string, string> headers, HookType hookType, http::verb verb) : url(url), method(method), payload(payload), headers(headers), hookType(hookType), verb(verb) {
    this->host = extractRegex(DOMAIN_REGEX, url);
    path = extractRegex(PATH_REGEX, url);
}
string HttpRelayDependency :: extractRegex(string regex, string s) {
    smatch match;
    regex_match(s, match, std::regex(DOMAIN_REGEX), regex_constants::match_default);
    if(match.size() > 0) {
        return match[0];
    } else  {
        return string();
    }
}

string HttpRelayDependency :: getOutput(string input, map<string, string> inputParams) { 
    return string();
}


void HttpRelayDependency :: executeHook(const Node &node) {

}

HookType HttpRelayDependency :: getHookType() {
    return hookType;
}

string HttpRelayDependency :: getResponse() const {

    boost::asio::io_context ioc;
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    auto lookup = resolver.resolve(host);
    stream.connect(lookup);
    http::request<http::string_body> request(verb, path, 11);

    for(auto &item : headers) {
        request.set(item.first, item.second);
    }
    request.body() = payload;
    http::write(stream, request);

    beast::flat_buffer buffer;

    http::response<http::dynamic_body> res;

    http::read(stream, buffer, res);

    string responseString = beast::buffers_to_string(res.body().data());

    beast::error_code errorCode;

    stream.socket().shutdown(tcp::socket::shutdown_both, errorCode);

    if(errorCode && errorCode != beast::errc::not_connected)
        throw beast::system_error{errorCode};

    return responseString;

}


