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

        Msg_t() {}
        Msg_t(const std::string &name, const std::string &message) : name(name), message(message) {}
    };

    struct Internal_Msg_t
    {
        std::string name;
        std::string message;
        std::vector<uint8_t>::const_iterator it;

        Internal_Msg_t() {}
        Internal_Msg_t(const std::string &name, const std::string &message, std::vector<uint8_t>::const_iterator it) 
            : name(name), message(message), it(it){}
    };

    const size_t min_buffer_size = 4;

    std::vector<uint8_t> make_buff(const Msg_t &msg);
    Msg_t parse_buff(std::vector<uint8_t> &buff);
}

#endif
