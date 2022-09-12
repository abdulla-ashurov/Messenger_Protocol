#ifndef PACKET_HPP
#define PACKET_HPP

#include "messenger.hpp"

namespace packet
{
    const std::string::const_iterator push_single_packet(
        const std::string &sender_name, const std::string::const_iterator next_packet_text, const std::string::const_iterator end, std::vector<uint8_t> &buffer);

    messenger::Internal_Msg_t read_single_packet(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);
}
#endif
