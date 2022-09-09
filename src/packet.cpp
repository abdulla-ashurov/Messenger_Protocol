#include "../include/packet.hpp"
#include "../include/detail.hpp"
#include "../include/detail.hpp"

namespace packet
{
    const std::string::const_iterator push_single_packet(
        const std::string &sender_name, std::string::const_iterator next_packet_text, std::string::const_iterator end, std::vector<uint8_t> &buffer)
    {
        std::vector<uint8_t>::iterator header_begin = detail::reserve_memory_for_header(buffer);
        std::vector<uint8_t>::iterator header_end = buffer.end();

        detail::put_name(sender_name, buffer);
        
        const size_t message_length = detail::calculate_msg_size_for_one_packet(next_packet_text, end);
        end = next_packet_text + message_length;
        detail::put_message(next_packet_text, end, buffer);

        detail::put_header(sender_name.length(), message_length, detail::defaultCRC4, header_begin, header_end);    

        return end;
    }
}
