#include "../include/detail.hpp"

namespace detail
{
    std::vector<uint8_t>::iterator reserve_memory_for_header(std::vector<uint8_t> &buffer) 
    {
        buffer.resize(buffer.size() + packet_header_size);
        std::vector<uint8_t>::iterator header_begin = buffer.end() - packet_header_size;

        return header_begin;
    }

    void put_name(const std::string &name, std::vector<uint8_t> &buffer) 
    {
        for (size_t i = 0; i < name.length(); i++) {
            buffer.push_back(name[i]);
        }
    }

    size_t calculate_msg_size_for_one_packet(std::string::const_iterator begin, std::string::const_iterator end) 
    {
        size_t message_length;

        if (std::distance(begin, end) > max_message_size_in_one_packet)
            message_length = max_message_size_in_one_packet;
        else
            message_length = std::distance(begin, end);

        return message_length;
    }

    void put_message(std::string::const_iterator begin, std::string::const_iterator end, std::vector<uint8_t> &buffer) 
    {
        for (; begin != end; begin++)
            buffer.push_back(*begin);
    }

    void put_flag(std::vector<uint8_t>::iterator it) 
    {
        *it = defaultFlag;
        *it <<= 5;
    }

    void put_name_length(std::vector<uint8_t>::iterator it, const uint8_t length)
    {
        *it |= (length << 1);
    }

    void put_msg_length(std::vector<uint8_t>::iterator first_byte, std::vector<uint8_t>::iterator second_byte, const uint8_t length)
    {
        uint8_t value_to_first_byte = (length & 0x10) >> 4;
        *first_byte |= value_to_first_byte;

        uint8_t value_to_second_byte = (length << 4);
        *second_byte = value_to_second_byte;
    }

    void put_crc4(std::vector<uint8_t>::iterator it, const uint8_t crc4) 
    {
        *it |= crc4;
    }

    void copy_header_to_buffer(std::vector<uint8_t> &header, std::vector<uint8_t>::iterator header_buffer_begin, std::vector<uint8_t>::iterator header_buffer_end)
    {
        for (size_t i = 0; (i < packet_header_size) && (header_buffer_begin != header_buffer_end); i++, header_buffer_begin++)
            *header_buffer_begin = header[i];
    }

    void put_header(const uint8_t name_length, const uint8_t msg_length, const uint8_t crcr4, std::vector<uint8_t>::iterator header_buffer_begin, std::vector<uint8_t>::iterator header_buffer_end)
    {
        std::vector<uint8_t> header_values(detail::packet_header_size);

        put_flag(header_values.begin());
        put_name_length(header_values.begin(), name_length);
        put_msg_length(header_values.begin(), header_values.begin() + 1, msg_length);
        put_crc4(header_values.begin() + 1, crcr4);
        
        copy_header_to_buffer(header_values, header_buffer_begin, header_buffer_end);
    }
}
