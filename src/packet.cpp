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

        detail::put_name(sender_name.begin(), sender_name.end(), buffer);
        
        const size_t message_length = detail::calculate_msg_size_for_one_packet(next_packet_text, end);
        end = next_packet_text + message_length;
        detail::put_message(next_packet_text, end, buffer);

        detail::put_header(detail::default_flag, sender_name.length(), message_length, detail::default_crc4, header_begin, header_end);    

        return end;
    }

    messenger::Internal_Msg_t read_single_packet(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end)
    {
        detail::Header header = detail::get_header(begin, begin + detail::packet_header_size);
        if (!detail::is_valid_header(header))
            throw std::invalid_argument("invalid header field in buffer");
        begin += detail::packet_header_size;

        std::string sender_name = detail::get_name(begin, begin + header.name_length);
        begin += header.name_length;
        
        std::string sender_msg = detail::get_message(begin, begin + header.msg_length);
        begin += header.msg_length;

        return messenger::Internal_Msg_t(sender_name, sender_msg, begin);
    }
}
