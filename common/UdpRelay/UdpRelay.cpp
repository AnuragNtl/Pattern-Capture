#include <boost/asio.hpp>
#include "UdpRelay.h"

namespace asio = boost::asio;
namespace ip = asio::ip;

void UdpRelayHook :: executeHook(const HookData &hookData) {
    PatternCapture::HookProperties properties = hookData.hookProperties;
    if (!(properties.hasProperty(UDP_RELAY_HOST) && 
            properties.hasProperty(UDP_RELAY_PORT))) {
        throw std::exception();
    }
    relayUdp(properties[UDP_RELAY_HOST], properties[UDP_RELAY_PORT], PatternCapture::BinData(properties[MESSAGE]));
}

bool relayUdp(string host, string port, PatternCapture::BinData message) {
    boost::asio::io_service io_service;
    ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), 0));
    ip::udp::resolver resolver(io_service);
    ip::udp::resolver::query query(ip::udp::v4(), host,
            port);
    ip::udp::resolver::iterator iter = resolver.resolve(query);
    ip::udp::endpoint endpoint = *iter;
    socket.send_to(boost::asio::buffer(message.data, message.length), endpoint);
    return true;
}

bool UdpRelay :: getOutput(PatternCapture::BinData input, map<string, string> params) const {
    string required[] = {UDP_RELAY_HOST, UDP_RELAY_PORT};
    for (string param : required) {
        if (params.find(param) == params.end()) {
            throw std::exception();
        }
    }
    return relayUdp(params[UDP_RELAY_HOST], params[UDP_RELAY_PORT], input);
}

HookType UdpRelayHook :: getHookType() {
    return HookType::EXECUTE_AFTER;
}

std::string UdpRelayHook :: getId() const {
    return "udpRelayHook";
}

std::string UdpRelay :: getId() const {
    return "udpRelay";
}

std::vector<std::string> getDependencyTypes() {
    return {DEPENDENCY_TYPE_HOOKS, "relay"};
}

std::set<std::string> UdpRelayHook :: getRequiredParameters() {
    return {UDP_RELAY_HOST, UDP_RELAY_PORT, MESSAGE, MESSAGE_LENGTH};
}

Dependency* getDependency(const char *dependencyName) {
    if (strcmp(dependencyName, "udpRelay") == 0) {
        return new UdpRelayHook;
    } else {
        return new UdpRelay;
    }
}

