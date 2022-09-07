#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

struct Msg_t {
    std::string name;
    std::string text;

    Msg_t(const std::string &name, const std::string &text): name(name), text(text) {}
};

static const uint8_t crc4_tab[] = {
    0x0, 0x7, 0xe, 0x9, 0xb, 0xc, 0x5, 0x2,
    0x1, 0x6, 0xf, 0x8, 0xa, 0xd, 0x4, 0x3,
};
/**
 * crc4 - calculate the 4-bit crc of a value.
 * @c:    starting crc4
 * @x:    value to checksum
 * @bits: number of bits in @x to checksum
 *
 * Returns the crc4 value of @x, using polynomial 0b10111.
 *
 * The @x value is treated as left-aligned, and bits above @bits are ignored
 * in the crc calculations.
 */
uint8_t crc4(uint8_t c, uint64_t x, int bits)
{
    int i;
    /* mask off anything above the top bit */
    x &= (1ull << bits) - 1;
    /* Align to 4-bits */
    bits = (bits + 3) & ~0x3;
    /* Calculate crc4 over four-bit nibbles, starting at the MSbit */
    for (i = bits - 4; i >= 0; i -= 4)
        c = crc4_tab[c ^ ((x >> i) & 0xf)];
    
    return c;
}

size_t calculate_count_of_packages(const size_t length_of_sender_message, const size_t max_length_of_message_in_one_package) {
    return (length_of_sender_message / max_length_of_message_in_one_package) + ((length_of_sender_message % max_length_of_message_in_one_package) ? 1 : 0);
}

size_t calculate_size_of_packages_in_bytes(
    const size_t package_header_size_in_bytes, const size_t length_of_sender_name, const size_t length_of_sender_message, const size_t count_of_packages
) {
    return (package_header_size_in_bytes + length_of_sender_name) * count_of_packages + length_of_sender_message;
}

void set_flag(std::vector<uint8_t>::iterator it) {
    const uint8_t defaultFlag = 0x5;
    *it = defaultFlag;
    *it <<= 5;
}

void set_name_length(std::vector<uint8_t>::iterator it, const uint8_t length) {
    uint8_t temp = length << 1;
    *it |= temp;
}

void set_msg_length(std::vector<uint8_t>::iterator it, const uint8_t length) {
    uint8_t value_to_first_byte = (length & 0x10) >> 4;
    *it |= value_to_first_byte;

    uint8_t value_to_second_byte = length << 4;
    *(it + 1) = value_to_second_byte;
}

void set_crc4(std::vector<uint8_t>::iterator it, const uint8_t value) {
    *it |= value;
}

void set_header(std::vector<uint8_t>::iterator it, const uint8_t name_length, const uint8_t msg_length, const uint8_t crc4) {
    set_flag(it);
    set_name_length(it, name_length);
    set_msg_length(it, msg_length);
    set_crc4(it + 1, crc4);
}

void set_sender_name(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end, const std::string &name) {
    for(int i = 0; begin != end; i++, begin++) {
        *begin = name[i];
    }
}
void set_sender_msg(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end, const std::string &msg, uint8_t start_index) {
    for(; begin != end; start_index++, begin++) {
        *begin = msg[start_index];
    }
}

std::vector<uint8_t> make_buff(const Msg_t &msg) {
    const size_t max_length_of_sender_name = 15;
    if (msg.name.empty() || msg.name.length() > max_length_of_sender_name) {
        throw std::length_error("The sender's name must be between 1 and 15 characters.");
    }

    if (msg.text.empty()) {
        throw std::length_error("The sender's text message must not be empty.");
    }

    const size_t max_length_of_message_in_one_package = 31;
    const size_t count_of_packages = calculate_count_of_packages(msg.text.length(), max_length_of_message_in_one_package);

    const size_t package_header_size_in_bytes = 2;
    const size_t size = calculate_size_of_packages_in_bytes(package_header_size_in_bytes, msg.name.length(), msg.text.length(), count_of_packages);

    std::vector<uint8_t> bytes_of_packages(size);

    std::vector<uint8_t>::iterator it = bytes_of_packages.begin();
    for (size_t i = 0, msg_length = msg.text.length(), start_msg_index = 0; (i < count_of_packages) && (it != bytes_of_packages.end()); i++) {
        if (msg_length > max_length_of_message_in_one_package)
            set_header(it, msg.name.length(), max_length_of_message_in_one_package, crc4(4, 4, 8));
        else 
            set_header(it, msg.name.length(), msg_length, crc4(4, 4, 8));
        it += package_header_size_in_bytes;
        
        set_sender_name(it, it + msg.name.length(), msg.name);
        it += msg.name.length();

        if (msg_length > max_length_of_message_in_one_package) {
            set_sender_msg(it, it + max_length_of_message_in_one_package, msg.text, start_msg_index);
            it += max_length_of_message_in_one_package;
            start_msg_index += max_length_of_message_in_one_package;
            msg_length -= max_length_of_message_in_one_package;
        } else {
            set_sender_msg(it, it + msg_length, msg.text, start_msg_index);
            it += msg_length;
        }
    }

    return bytes_of_packages;
}

struct Header{
    uint8_t flag, name_length, message_length, crc4;
};

uint8_t get_flag(std::vector<uint8_t>::iterator it) {
    return *it >> 5;
}

uint8_t get_name_length(std::vector<uint8_t>::iterator it) {
    uint8_t name_length = *it << 3;
    name_length >>= 4;

    return name_length;
}

uint8_t get_msg_length(std::vector<uint8_t>::iterator it) {
    uint8_t first_part = *it & 0x1;
    first_part <<= 4;
    uint8_t second_part = (*(it + 1) & 0xF0) >> 4;
    
    return first_part | second_part;
}

uint8_t get_crc4(std::vector<uint8_t>::iterator it) {
    return *it & 0x0F;
}

Header get_header(std::vector<uint8_t>::iterator it) {
    Header header;
    
    header.flag = get_flag(it);
    header.name_length = get_name_length(it);
    header.message_length = get_msg_length(it);
    header.crc4 = get_crc4(it + 1);

    return header;
}

std::string get_sender_name(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end) {
    std::string name;
    
    for (; begin != end; begin++)
        name += *begin;

    return name;
}

std::string get_sender_message(std::vector<uint8_t>::iterator begin, size_t count) {
    std::string message;

    std::vector<uint8_t>::iterator end = begin + count;
    for (; begin != end; begin++) 
        message += *begin;

    return message;
}

Msg_t parse_buff(std::vector<uint8_t> &buff) {
    Header header;

    const size_t package_header_size_in_bytes = 2;
    const size_t max_length_of_message_in_one_package = 31;

    std::vector<uint8_t>::iterator it = buff.begin();
    std::string sender_name, sender_message;
    
    for (size_t i = 0; it < buff.end(); i++) {
        header = get_header(it);
        size_t temp_length = header.message_length;

        if (header.flag != 0x05 || header.crc4 != 3)
            throw "invalid package!";

        it += package_header_size_in_bytes;

        if (i == 0)
            sender_name = get_sender_name(it, it + header.name_length);
        
        it += header.name_length;
        
        if (temp_length >= max_length_of_message_in_one_package)
            sender_message += get_sender_message(it, max_length_of_message_in_one_package);
        else
            sender_message += get_sender_message(it, temp_length);

        it = it + max_length_of_message_in_one_package;
    }

    return Msg_t(sender_name, sender_message);
}

#endif
