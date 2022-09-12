#include "../include/messenger.hpp"
#include "../include/packet.hpp"

namespace messenger
{
    std::vector<uint8_t> make_buff(const Msg_t &msg)
    {
        const size_t max_sender_name_length = 15;

        if (msg.name.empty() || msg.name.length() > max_sender_name_length)
            throw std::length_error("The sender's name must be between 1 and 15 characters");
        if (msg.message.empty())
            throw std::length_error("The sender's message cannot be empty");

        std::vector<uint8_t> buffer;
        std::string::const_iterator next_packet_message = msg.message.cbegin();

        while (next_packet_message != msg.message.cend())
            next_packet_message = packet::push_single_packet(msg.name, next_packet_message, msg.message.cend(), buffer);

        return buffer;
    }

    Msg_t parse_buff(const std::vector<uint8_t> &buff)
    {
        if (buff.empty() || buff.size() < min_buffer_size)
            throw std::invalid_argument("invalid buffer!");

        Internal_Msg_t next_packet;
        next_packet.it = buff.begin();
        
        next_packet = packet::read_single_packet(next_packet.it, buff.end());
        Msg_t parsed_buff(next_packet.name, next_packet.message);

        while (next_packet.it != buff.end())
        {
            next_packet = packet::read_single_packet(next_packet.it, buff.end());
            if (next_packet.name != parsed_buff.name)
                throw std::invalid_argument("invalid sender_name field in buffer!");

            parsed_buff.message += next_packet.message;
        }

        return parsed_buff;
    }
}
