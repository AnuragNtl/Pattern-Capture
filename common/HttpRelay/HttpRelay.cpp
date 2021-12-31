#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#define DOMAIN_REGEX "(?<=http.+//).+?(?=(/|:|$))"
#define PATH_REGEX "(?<=http.+//.+?/).+$"
#define PORT_REGEX "(?<=http.+//.+?:)[0-9]*(?=(/|$))"

using namespace std;
namespace beast = boost::beast;
using namespace boost::asio;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

#include "HttpRelay.h"
using namespace PatternCapture;

HttpRelayDependency :: HttpRelayDependency(string url, string payload, map<string, string> headers, http::verb verb) : url(url), payload(payload), headers(headers), verb(verb) {
    initializeVerbMap(); 
    extractHostPortPathFromUrl(url);
}

void HttpRelayDependency :: extractHostPortPathFromUrl(string url) {
    this->host = extractRegex(DOMAIN_REGEX, url);
    if(host.size() == 0) {
        throw std::exception();
    }
    this->path = "/";
    string path = extractRegex(PATH_REGEX, url);
    if(path.size() > 0) {
        this->path = path;
    }
    this->port = DEFAULT_PORT;
    string port = extractRegex(PORT_REGEX, url);
    if(port.size() > 0) {
        this->port = port;
    }
}

HttpRelayDependency :: HttpRelayDependency() {

    cout << DOMAIN_REGEX << "\n" << PATH_REGEX << "\n" << PORT_REGEX << "\n";
   initializeVerbMap(); 

}

void HttpRelayDependency :: initializeVerbMap() {

    if(httpVerbMap.size() > 0) return;

    httpVerbMap["get"] = http::verb::get;
    httpVerbMap["post"] = http::verb::post;
    httpVerbMap["put"] = http::verb::put;
    httpVerbMap["patch"] = http::verb::patch;
    httpVerbMap["delete"] = http::verb::delete_;
    httpVerbMap["head"] = http::verb::head;
    httpVerbMap["options"] = http::verb::options;
}

string HttpRelayDependency :: extractRegex(string regex, string s) {
    /*
    smatch match;
    std::regex regexExpression(regex);
    regex_match(s, match, regexExpression, regex_constants::match_default);
    if(match.size() > 0) {
        return match[0];
    } else  {
        return string();
    }
    */
    boost::regex expr{regex};
    boost::sregex_iterator itBegin(s.begin(), s.end(), expr), itEnd;
    if(itBegin != itEnd) {
        return itBegin->str();
    } else {
        return string();
    }
}

string HttpRelayDependency :: getOutput(string input, map<string, string> inputParams) const { 
    HttpRelayDependency httpRelay;
    httpRelay.loadParams(inputParams);
    return httpRelay.getResponse();
}


HookType HttpRelayHook :: getHookType() {
    return hookType;
}

string HttpRelayDependency :: getResponse() const {

    boost::asio::io_context ioc;
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);
auto lookup = resolver.resolve(host, port);
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

    cout << "http response : \n" << responseString << "\n--\n";

    return responseString;

}

void HttpRelayDependency :: loadParams(map<string, string> &params) {

    if(params.find(URL_KEY) == params.end()) {

        if(params.find(HOST_KEY) == params.end() 
                || params.find(PORT_KEY) == params.end() 
                || params.find(PATH_KEY) == params.end()) {
            throw std::exception();
        }
        host = params[HOST_KEY];
        port = params[PORT_KEY];
        path = params[PATH_KEY];
        if(path.size() == 0)
            path = "/";
    }

    url = params[URL_KEY];
    extractHostPortPathFromUrl(url);

    payload = params[PAYLOAD_KEY];
    
    string rawHeaders = params[HEADERS_KEY];

    vector<string> headers;
    boost::split(headers, rawHeaders, boost::is_any_of(HEADER_DELIMITER));
    for(string header : headers) {
        vector<string> nameValuePair;
        boost::split(nameValuePair, header, boost::is_any_of(HEADER_NAME_VALUE_DELIMITER));
        boost::trim(nameValuePair[0]);
        boost::trim(nameValuePair[1]);
        if(nameValuePair.size() == 2) {
            this->headers[nameValuePair[0]] = nameValuePair[1];
        }
    }

    verb = http::verb::get;

    if(httpVerbMap.find(VERB_KEY) != httpVerbMap.end()) {

        verb = httpVerbMap[VERB_KEY];
    }
    

}

map<string, http::verb> HttpRelayDependency :: httpVerbMap = map<string, http::verb>();

string HttpRelayHook :: getId() const {

    return "httpRelayHook";

}

void HttpRelayHook :: executeHook(const HookData &hookData) {

    const Node &node = hookData.node;
    map<string, string> inputParams = hookData.hookProperties.properties;

    if(inputParams["hookType"] == "EXECUTE_BEFORE") {
        hookType = EXECUTE_BEFORE;
    } else if(inputParams["hookType"] == "EXECUTE_AFTER") {
        hookType = EXECUTE_AFTER;
    } else { 
        hookType = EXECUTE_ON_CALL;
    }
    HttpRelayDependency relayDependency;
    relayDependency.getOutput(string(), inputParams);
}

vector<string> getDependencyTypes() {

    return {"httpRelayDependency", DEPENDENCY_TYPE_HOOKS};

}

Dependency* getDependency(const char *dependencyName) {

    if(string(dependencyName) == DEPENDENCY_TYPE_HOOKS) {
        return new HttpRelayHook;
    } else {
        return new HttpRelayDependency;
    }

}

string HttpRelayDependency :: getId() const {

    return "httpRelayDependency";
}



