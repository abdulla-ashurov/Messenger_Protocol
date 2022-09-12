#include "../include/detail.hpp"

namespace detail
{
    std::vector<uint8_t>::iterator reserve_memory_for_header(std::vector<uint8_t> &buffer)
    {
        buffer.resize(buffer.size() + packet_header_size);
        std::vector<uint8_t>::iterator header_begin = buffer.end() - packet_header_size;

        return header_begin;
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

    void put_name(std::string::const_iterator begin, std::string::const_iterator end, std::vector<uint8_t> &buffer)
    {
        for (; begin != end; begin++)
            buffer.push_back(*begin);
    }

    void put_message(std::string::const_iterator begin, std::string::const_iterator end, std::vector<uint8_t> &buffer)
    {
        for (; begin != end; begin++)
            buffer.push_back(*begin);
    }

    void put_flag(std::vector<uint8_t>::iterator it, const uint8_t flag)
    {
        *it = flag;
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

    void put_header(
        const uint8_t flag, const uint8_t name_length, const uint8_t msg_length, const uint8_t crc4,
        std::vector<uint8_t>::iterator header_buffer_begin, std::vector<uint8_t>::iterator header_buffer_end)
    {
        std::vector<uint8_t> header_values(detail::packet_header_size);

        put_flag(header_values.begin(), flag);
        put_name_length(header_values.begin(), name_length);
        put_msg_length(header_values.begin(), header_values.begin() + 1, msg_length);
        put_crc4(header_values.begin() + 1, crc4);

        copy_header_to_buffer(header_values, header_buffer_begin, header_buffer_end);
    }

    uint8_t get_flag(std::vector<uint8_t>::const_iterator it)
    {
        return *it >> 5;
    }

    uint8_t get_name_length(std::vector<uint8_t>::const_iterator it)
    {
        uint8_t name_length = *it << 3;
        name_length >>= 4;

        return name_length;
    }

    uint8_t get_msg_length(std::vector<uint8_t>::const_iterator first_byte, std::vector<uint8_t>::const_iterator second_byte)
    {
        uint8_t first_part = *first_byte & 0x1;
        first_part <<= 4;
        uint8_t second_part = (*second_byte & 0xF0) >> 4;
    
        return first_part | second_part;
    }

    uint8_t get_crc4(std::vector<uint8_t>::const_iterator it)
    {
        return *it & 0x0F;
    }

    Header get_header(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end)
    {
        if (std::distance(begin, end) != packet_header_size)
            throw std::invalid_argument("invalid header size");

        uint8_t flag = get_flag(begin);
        uint8_t name_length = get_name_length(begin);
        uint8_t msg_length = get_msg_length(begin, begin + 1);
        uint8_t crcr4 = get_crc4(begin + 1);

        return Header(flag, name_length, msg_length, crcr4);
    }

    bool is_valid_header(const Header &header)
    {
        return header.flag == default_flag && header.crc4 == default_crc4;
    }

    std::string get_name(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end)
    {
        std::string sender_name;
        for (; begin != end; begin++)
            sender_name += *begin;
        
        return sender_name;
    }

    std::string get_message(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end)
    {
        std::string sender_msg;
        for (; begin != end; begin++)
            sender_msg += *begin;
        
        return sender_msg;
    }
}
