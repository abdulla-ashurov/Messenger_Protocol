# Messenger_Protocol
Messenger Protocol

## Source code
```cpp
#include <iostream>
#include <bitset>
#include <vector>

void setFlag(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end) {
    *begin = 0x5;
    *begin <<= 5;
}

void setNameLength(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end, uint8_t name_length) {
    name_length <<= 1;
    *begin |= name_length;
}

void setMsgLength(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end, uint8_t msg_length) {
    uint8_t value_to_first_byte = msg_length & 0x8;
    *begin |= value_to_first_byte;

    uint8_t value_to_second_byte = msg_length << 4;
    *(begin + 1) = value_to_second_byte;
}

void setCRC4(std::vector<uint8_t>::iterator begin, std::vector<uint8_t>::iterator end, uint8_t crc) {
    *(begin + 1) |= crc;
}

void setSenderName(std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end, const std::string &sender_name) {
    for(int i = 0; begin != end; i++, begin++) {
        *begin = sender_name[i];
        std::cout << *begin;
    }
}

void setMsg(std::vector<std::uint8_t>::iterator begin, std::vector<std::uint8_t>::iterator end, const std::string &msg) {
    for(int i = 0; begin != end; i++, begin++) {
        *begin = msg[i];
        std::cout << *begin;
    }
}

int main()
{
    std::vector<uint8_t> v(12); // 2 + 4(Jack\0) + 6(Hello!\0) = 12 bytes

    setFlag(v.begin(), v.end());
    setNameLength(v.begin(), v.end(), 4);
    setMsgLength(v.begin(), v.end(), 6);
    setCRC4(v.begin(), v.end(), 15);

    setSenderName(v.begin() + 2, v.end() + 4, "jack");
    setMsg(v.begin() + 6, v.end(), "Hello!");

    std::cout << std::endl << std::endl;

    for (size_t i = 0; i < v.size(); i++) {
        std::cout << std::bitset<8>(v[i]) << std::endl;
    }

    return 0;
}
```
