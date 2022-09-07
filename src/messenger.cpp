#include "../include/messenger.hpp"
#include "../include/common.hpp"

std::vector<uint8_t> make_buff(const Msg_t &msg) {
    const size_t max_sender_name_length = 15;

    if (msg.name.empty() || msg.name.length() > max_sender_name_length)
        throw std::length_error("The sender's name must be between 1 and 15 characters");
    if (msg.message.empty())
        throw std::length_error("The sender's message cannot be empty");

    std::vector<uint8_t> buffer;
    std::string::const_iterator next_packet_message = msg.message.cbegin();

    while (next_packet_message != msg.message.cend())
        next_packet_message = push_single_packet(msg.name, msg.message, msg.message.cend(), buffer);

    return buffer;
}
