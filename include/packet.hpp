#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>
#include <vector>

namespace packet
{
    const std::string::const_iterator push_single_packet(
        const std::string &sender_name, const std::string::const_iterator next_packet_text, const std::string::const_iterator end, std::vector<uint8_t> &buffer);
}
#endif
