#include <string>
#include <vector>

const std::string::const_iterator push_single_packet(
    const std::string &sender_name, const std::string &sender_message, const std::string::const_iterator end, const std::vector<uint8_t> buffer
);
