#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <vector>
#include <string>

namespace detail
{
    const size_t packet_header_size = 2;
    const size_t max_message_size_in_one_packet = 31;

    const uint8_t defaultFlag = 0x5;
    const uint8_t defaultCRC4 = 0x0F;
    
    std::vector<uint8_t>::iterator reserve_memory_for_header(std::vector<uint8_t> &buffer);
    
    size_t calculate_msg_size_for_one_packet(std::string::const_iterator begin, std::string::const_iterator end);
    void put_name(const std::string &name, std::vector<uint8_t> &buffer);
    void put_message(std::string::const_iterator begin, std::string::const_iterator end, std::vector<uint8_t> &buffer);

    void put_flag(std::vector<uint8_t>::iterator it);
    void put_name_length(std::vector<uint8_t>::iterator it, const uint8_t length);
    void put_msg_length(std::vector<uint8_t>::iterator first_byte, std::vector<uint8_t>::iterator second_byte, const uint8_t length);
    void put_crc4(std::vector<uint8_t>::iterator it, const uint8_t crc4);
    void copy_header_to_buffer(std::vector<uint8_t> &header, std::vector<uint8_t>::iterator header_buffer_begin, std::vector<uint8_t>::iterator header_buffer_end);
    void put_header(const uint8_t name_length, const uint8_t msg_length, const uint8_t crcr4, std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end);
}

#endif
