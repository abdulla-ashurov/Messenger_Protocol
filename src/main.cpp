#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

struct msg_t
{
    msg_t(const std::string &nm, const std::string &txt)
        : name(nm), text(txt)
    {
    }

    std::string name; /**< message sender's name */
    std::string text; /**< message text */
};

const size_t calculate_size_of_package_in_bytes(const msg_t &msg) {
    const size_t package_header_size_in_bytes = 2;
    const size_t count_of_packages = (msg.text.length() / 31) + ((msg.text.length() % 31) ? 1 : 0);
    const size_t size_in_bytes = (package_header_size_in_bytes + msg.name.length()) * count_of_packages + msg.text.length();

    return size_in_bytes;
}

void setFlag(std::vector<uint8_t>::iterator begin) {
    *begin = 0x5;
    *begin <<= 5;
}

void setNameLength(std::vector<uint8_t>::iterator begin, uint8_t length) {
    length <<= 1;
    *begin |= length;
}

void setMsgLength(std::vector<uint8_t>::iterator begin, uint8_t length) {
    uint8_t value_to_first_byte = (length & 0x10) >> 4;
    *begin |= value_to_first_byte;

    uint8_t value_to_second_byte = length << 4;
    *(begin + 1) = value_to_second_byte;
}

void setCRC4(std::vector<uint8_t>::iterator begin, uint8_t crc) {
    *begin |= crc;
}

void setSenderName(std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end, const std::string &sender_name) {
    for(int i = 0; begin != end; i++, begin++) {
        *begin = sender_name[i];
    }
}

void setMsg(std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end, const std::string &msg, size_t start_msg_index) {
    for(; begin != end; start_msg_index++, begin++) {
        *begin = msg[start_msg_index];
    }
}

void print(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end) {
    for (; begin != end; begin++) {
        std::cout << "bitset: " << std::bitset<8>(*begin) << "\t value: " << *begin << std::endl;
    }
}

std::vector<uint8_t> make_buff(const msg_t &msg) {
    const size_t max_length_of_name = 15;
    if (msg.name.empty() || msg.name.length() > max_length_of_name) {
        throw std::length_error("sender name must be between 1 to 15 characters");
    }

    if (msg.text.empty()) {
        throw std::length_error("text message must not be empty");
    }

    const size_t package_header_size_in_bytes = 2;
    const size_t count_of_packages = (msg.text.length() / 31) + ((msg.text.length() % 31) ? 1 : 0);
    const size_t size = (package_header_size_in_bytes + msg.name.length()) * count_of_packages + msg.text.length();
    std::vector<uint8_t> bytes_of_packages(size);

    const size_t max_length_of_text_in_one_package = 31;

    size_t text_length = msg.text.length();
    size_t text_index = 0;
    std::vector<uint8_t>::iterator current = bytes_of_packages.begin();

    for (size_t i = 0; i < count_of_packages; i++) {
        setFlag(current);
        setNameLength(current, msg.name.length());
        setMsgLength(current, text_length / max_length_of_text_in_one_package ? max_length_of_text_in_one_package : text_length % max_length_of_text_in_one_package);
        text_length -= max_length_of_text_in_one_package;
        current++;

        setCRC4(current, 15);
        current++;

        setSenderName(current, current + msg.name.length(), msg.name);
        current += msg.name.length();

        if ((i + 1) == size) {
            setMsg(current, current + text_length, msg.text, text_index);
            current += msg.text.length();
            text_index += text_length;
        } else {
            setMsg(current, current + max_length_of_text_in_one_package, msg.text, text_index);
            current += max_length_of_text_in_one_package;
            text_index += max_length_of_text_in_one_package;
        }
    }

    return bytes_of_packages;
}

int main()
{
    msg_t msg("John", "Hello World! How are you? What's a new?");
    
    std::vector<uint8_t> packages = make_buff(msg);

    std::cout << "Name size is " << msg.name.length() << std::endl;
    std::cout << "Msg size is " << msg.text.length() << std::endl << std::endl;
    
    print(packages.begin(), packages.end());

    return 0;
}
