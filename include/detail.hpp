#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <vector>
#include <string>

namespace detail
{
    const size_t packet_header_size = 2;
    const size_t max_message_size_in_one_packet = 31;

    const uint8_t default_flag = 0x5;
    const uint8_t default_crc4 = 0x0F;
    
    std::vector<uint8_t>::iterator reserve_memory_for_header(std::vector<uint8_t> &buffer);
    
    size_t calculate_msg_size_for_one_packet(std::string::const_iterator begin, std::string::const_iterator end);
    void put_name(std::string::const_iterator begin, std::string::const_iterator end, std::vector<uint8_t> &buffer);
    void put_message(std::string::const_iterator begin, std::string::const_iterator end, std::vector<uint8_t> &buffer);

    void put_flag(std::vector<uint8_t>::iterator it, const uint8_t flag);
    void put_name_length(std::vector<uint8_t>::iterator it, const uint8_t length);
    void put_msg_length(std::vector<uint8_t>::iterator first_byte, std::vector<uint8_t>::iterator second_byte, const uint8_t length);
    void put_crc4(std::vector<uint8_t>::iterator it, const uint8_t crc4);
    void copy_header_to_buffer(std::vector<uint8_t> &header, std::vector<uint8_t>::iterator header_buffer_begin, std::vector<uint8_t>::iterator header_buffer_end);
    void put_header(const uint8_t flag, const uint8_t name_length, const uint8_t msg_length, const uint8_t crc4, std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);

    struct Header
    {
        uint8_t flag, name_length, msg_length, crc4;

        Header(const uint8_t flag, const uint8_t name_length, const uint8_t msg_length, const uint8_t crc4)
            : flag(flag), name_length(name_length), msg_length(msg_length), crc4(crc4) {}
    };

    std::string get_name(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);
    std::string get_message(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);

    uint8_t get_flag(std::vector<uint8_t>::const_iterator it);
    uint8_t get_name_length(std::vector<uint8_t>::const_iterator it);
    uint8_t get_msg_length(std::vector<uint8_t>::const_iterator first_byte, std::vector<uint8_t>::const_iterator second_byte);
    uint8_t get_crc4(std::vector<uint8_t>::const_iterator it);
    Header get_header(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);

    bool is_valid_header(const Header &header);
}

#endif
