#ifndef HEADER
#define HEADER

#include <iostream>

struct Msg_t {
    std::string name;
    std::string text;

    Msg_t(const std::string &name, const std::string &text): name(name), text(text) {}
};

void setFlag();
void setNameLength();
void setMsgLength();
void setCRC4();
void setSenderName();
void setSenderMsg();

const size_t calculate_count_of_packages(const size_t length_of_sender_message, const size_t max_length_of_message_in_one_package) {
    return (length_of_sender_message / max_length_of_message_in_one_package) + ((length_of_sender_message % max_length_of_message_in_one_package) ? 1 : 0);
}

const size_t calculate_size_of_packages_in_bytes(
    const size_t package_header_size_in_bytes, const size_t length_of_sender_name, const size_t length_of_sender_message, const size_t count_of_packages
) {
    return (package_header_size_in_bytes + length_of_sender_name) * count_of_packages + length_of_sender_message;
}

// std::vector<uint8_t> make_buff(const Msg_t &msg) {
//     const size_t max_length_of_sender_name = 15;
//     if (msg.name.empty() || msg.name.length() > max_length_of_sender_name) {
//         throw std::length_error("The sender's name must be between 1 and 15 characters.");
//     }

//     if (msg.text.empty()) {
//         throw std::length_error("The sender's text message must not be empty.");
//     }

//     const size_t max_length_of_message_in_one_package = 31;
//     const size_t count_of_packages = calculate_count_of_packages(msg.text.length(), max_length_of_message_in_one_package);

//     const size_t package_header_size_in_bytes = 2;
//     const size_t size = calculate_size_of_packages_in_bytes(package_header_size_in_bytes, msg.name.length(), msg.text.length(), count_of_packages);
// }

#endif 
