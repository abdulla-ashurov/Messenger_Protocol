#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <string>
#include <vector>

namespace messenger
{
    struct Msg_t
    {
        std::string name;
        std::string message;

        Msg_t(const std::string &name, const std::string &message) : name(name), message(message) {}
    };

    std::vector<uint8_t> make_buff(const Msg_t &msg);
}

#endif
