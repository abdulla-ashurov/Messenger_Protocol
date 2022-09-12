#include "../include/detail.hpp"
#include "../include/packet.hpp"
#include "../include/messenger.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("test function detail::reserve_memory_for_header")
{
    SECTION("vector size should be 2")
    {
        std::vector<uint8_t> header;
        detail::reserve_memory_for_header(header);

        size_t expected_size = 2;
        REQUIRE(header.size() == expected_size);
    }
    SECTION("vector size should be 7")
    {
        std::vector<uint8_t> header(5);
        detail::reserve_memory_for_header(header);

        size_t expected_size = 7;
        REQUIRE(header.size() == expected_size);
    }
}

TEST_CASE("test function detail::calculate_msg_size_for_one_packet")
{
    SECTION("function should return 12")
    {
        std::string msg = "Hello World!";

        const size_t expected_size = 12;
        REQUIRE(detail::calculate_msg_size_for_one_packet(msg.begin(), msg.end()) == expected_size);
    }
    SECTION("function should return 31")
    {
        std::string msg = "Hello World! How are you? Black";

        const size_t expected_size = 31;
        REQUIRE(detail::calculate_msg_size_for_one_packet(msg.begin(), msg.end()) == expected_size);
    }
    SECTION("function should return 31")
    {
        std::string msg = "Hello World! How are you? Black or White?";

        const size_t expected_size = 31;
        REQUIRE(detail::calculate_msg_size_for_one_packet(msg.begin(), msg.end()) == expected_size);
    }
}

TEST_CASE("test function detail::put_name")
{
    SECTION("in vector should be sender's name")
    {
        std::vector<uint8_t> buffer;

        std::string sender_name = "John";
        detail::put_name(sender_name.begin(), sender_name.end(), buffer);

        for (size_t i = 0; i < buffer.size(); i++)
            REQUIRE(buffer[i] == sender_name[i]);
    }
}

TEST_CASE("test function detaiL::put_message")
{
    SECTION("in vector should be sender's message")
    {
        std::vector<uint8_t> buffer;

        std::string sender_message = "Hello world! What's a new?";
        detail::put_message(sender_message.begin(), sender_message.end(), buffer);

        for (size_t i = 0; i < buffer.size(); i++)
            REQUIRE(buffer[i] == sender_message[i]);
    }
}

TEST_CASE("test function put_flag and get_flag")
{
    SECTION("in vector should be expected_value")
    {
        std::vector<uint8_t> package(1);
        detail::put_flag(package.begin());

        const uint8_t expected_value = 160;
        REQUIRE(int(package[0]) == expected_value);
    }
}

// TEST_CASE("test function set_name_length and get_name_length") {
//     SECTION("function get_name_length should return 0") {
//         std::vector<uint8_t> package(1);
//         const uint8_t name_length = 0;
//         set_name_length(package.begin(), name_length);

//         REQUIRE(get_name_length(package.begin()) == name_length);
//     }
//     SECTION("function get_name_length should return 7") {
//         std::vector<uint8_t> package(1);
//         const uint8_t name_length = 7;
//         set_name_length(package.begin(), name_length);

//         REQUIRE(get_name_length(package.begin()) == name_length);
//     }
//     SECTION("function get_name_length should return 15") {
//         std::vector<uint8_t> package(1);
//         const uint8_t name_length = 15;
//         set_name_length(package.begin(), name_length);

//         REQUIRE(get_name_length(package.begin()) == name_length);
//     }
// }

// TEST_CASE("test function set_msg_length and get_msg_length") {
//     SECTION("function get_msg_length should return 0") {
//         std::vector<uint8_t> package(2);
//         const uint8_t msg_length = 0;
//         set_msg_length(package.begin(), msg_length);

//         REQUIRE(get_msg_length(package.begin()) == msg_length);
//     }
//     SECTION("function get_msg_length should return 15") {
//         std::vector<uint8_t> package(2);
//         const size_t msg_length = 15;
//         set_msg_length(package.begin(), msg_length);

//         REQUIRE(get_msg_length(package.begin()) == msg_length);
//     }
//     SECTION("function get_msg_length should return 31") {
//         std::vector<uint8_t> package(2);
//         const size_t msg_length = 31;
//         set_msg_length(package.begin(), msg_length);

//         REQUIRE(get_msg_length(package.begin()) == msg_length);
//     }
// }

// TEST_CASE("test function set_crc4 and get_crc4") {
//     SECTION("function get_crc4 should return 0") {
//         std::vector<uint8_t> package(1);
//         const size_t crc4 = 0;
//         set_crc4(package.begin(), crc4);

//         REQUIRE(get_crc4(package.begin()) == crc4);
//     }
//     SECTION("function get_crc4 should return 7") {
//         std::vector<uint8_t> package(1);
//         const size_t crc4 = 7;
//         set_crc4(package.begin(), crc4);

//         REQUIRE(get_crc4(package.begin()) == crc4);
//     }
//     SECTION("function get_crc4 should return 15") {
//         std::vector<uint8_t> package(1);
//         const size_t crc4 = 15;
//         set_crc4(package.begin(), crc4);

//         REQUIRE(get_crc4(package.begin()) == crc4);
//     }
// }

// TEST_CASE("test function set_header and get_header") {
//     SECTION("function get_header should return type of Header with values {4, 22, 15}") {
//         std::vector<uint8_t> package(2);
//         const size_t length_of_sender_name = 4;
//         const size_t length_of_sender_message = 22;
//         const size_t crc4_value = 15;
//         set_header(package.begin(), length_of_sender_name, length_of_sender_message, crc4_value);

//         Header header = get_header(package.begin());

//         REQUIRE(header.name_length == length_of_sender_name);
//         REQUIRE(header.message_length == length_of_sender_message);
//         REQUIRE(header.crc4 == crc4_value);
//     }
//     SECTION("function get_header should return type of Header with values {4, 31, 15}") {
//         std::vector<uint8_t> package(2);
//         const size_t length_of_sender_name = 4;
//         const size_t length_of_sender_message = 31;
//         const size_t crc4_value = 15;
//         set_header(package.begin(), length_of_sender_name, length_of_sender_message, crc4_value);

//         Header header = get_header(package.begin());

//         REQUIRE(header.name_length == length_of_sender_name);
//         REQUIRE(header.message_length == length_of_sender_message);
//         REQUIRE(header.crc4 == crc4_value);
//     }
// }

// TEST_CASE("test function set_sender_name and get_sender_name") {
//     SECTION("function get_sender_name should return \"John\"") {
//         const std::string name = "John";
//         std::vector<uint8_t> package(name.length());
//         set_sender_name(package.begin(), package.end(), name);

//         REQUIRE(get_sender_name(package.begin(), package.end()) == name);
//     }
//     SECTION("function get_sender_name should return \"John Smith\"") {
//         const std::string name = "John Smith";
//         std::vector<uint8_t> package(name.length());
//         set_sender_name(package.begin(), package.end(), name);

//         REQUIRE(get_sender_name(package.begin(), package.end()) == name);
//     }
// }

// TEST_CASE("test function set_sender_msg and get_sender_msg") {
//     SECTION("function get_sender_msg should return \"Hello\"") {
//         const std::string msg = "Hello";
//         std::vector<uint8_t> package(msg.length());
//         set_sender_msg(package.begin(), package.end(), msg, 0);

//         REQUIRE(get_sender_message(package.begin(), msg.length()) == msg);
//     }
//     SECTION("function get_sender_msg should return \"Hello, John! How are you?\"") {
//         const std::string msg = "Hello, John! How are you?";
//         std::vector<uint8_t> package(msg.length());
//         set_sender_msg(package.begin(), package.end(), msg, 0);

//         REQUIRE(get_sender_message(package.begin(), msg.length()) == msg);
//     }
// }

// TEST_CASE("test function make_buff, when it returns 1 package") {
//     Msg_t msg{"John", "Hello World!"};
//     std::vector<uint8_t> bytes_of_packages = make_buff(msg);

//     SECTION("vector size should be 18 bytes") {
//         const size_t expected_size = 18;
//         REQUIRE(bytes_of_packages.size() == expected_size);
//     }
//     SECTION("check package header fields") {
//         std::vector<uint8_t> expected_header_values{168, 195};
//         const size_t package_header_size_in_bytes = 2;

//         for (size_t i = 0; i < package_header_size_in_bytes; i++)
//             REQUIRE(bytes_of_packages[i] == expected_header_values[i]);
//     }
//     SECTION("check sender name and sender message in package") {
//         const std::string expected_name = "John";
//         size_t start_index = 2, end_index = start_index + expected_name.length();

//         for (size_t i = 0; start_index < end_index; start_index++, i++)
//             REQUIRE(bytes_of_packages[start_index] == expected_name[i]);

//         const std::string expected_message = "Hello World!";

//         for (size_t i = 0; start_index < bytes_of_packages.size(); start_index++, i++)
//             REQUIRE(bytes_of_packages[start_index] == expected_message[i]);
//     }
// }

// TEST_CASE("test function make_buff, when it returns 2 package") {
//     Msg_t msg{"John Smith", "Hello, John! How are you? What's a new?"};
//     std::vector<uint8_t> bytes_of_packages = make_buff(msg);
//     const size_t package_header_size_in_bytes = 2;

//     SECTION("vector size should be 63 bytes") {
//         const size_t expected_size = 63;
//         REQUIRE(bytes_of_packages.size() == expected_size);
//     }
//     SECTION("check first package") {
//         std::vector<uint8_t> expected_header_values{181, 243};

//         size_t start_index = 0;
//         const size_t package_header_size_in_bytes = 2;

//         for (size_t i = 0; i < package_header_size_in_bytes; i++, start_index++)
//             REQUIRE(bytes_of_packages[start_index] == expected_header_values[i]);

//         const std::string expected_name = "John Smith";
//         size_t end_index = start_index + expected_name.length();

//         for (size_t i = 0; start_index < end_index; i++, start_index++)
//             REQUIRE(bytes_of_packages[start_index] == expected_name[i]);

//         const std::string expected_message = "Hello, John! How are you? What'";
//         end_index = start_index + 31;

//         for (size_t i = 0; start_index < end_index; i++, start_index++)
//             REQUIRE(bytes_of_packages[start_index] == expected_message[i]);
//     }

//     SECTION("check second package") {
//         std::vector<uint8_t> expected_header_values{180, 131};

//         size_t start_index = 43;
//         const size_t package_header_size_in_bytes = 2;

//         for (size_t i = 0; i < package_header_size_in_bytes; i++, start_index++)
//             REQUIRE(bytes_of_packages[start_index] == expected_header_values[i]);

//         const std::string expected_name = "John Smith";
//         size_t end_index = start_index + expected_name.length();

//         for (size_t i = 0; start_index < end_index; i++, start_index++)
//             REQUIRE(bytes_of_packages[start_index] == expected_name[i]);

//         const std::string expected_message = "s a new?";

//         for (size_t i = 0; start_index < bytes_of_packages.size(); i++, start_index++)
//             REQUIRE(bytes_of_packages[start_index] == expected_message[i]);
//     }
// }

// TEST_CASE("test function parse_buff") {
//     SECTION("function parse_buff should return type of Msg_t") {
//         Msg_t msg("John", "Hello World!");
//         std::vector<uint8_t> bytes_of_packages = make_buff(msg);

//         Msg_t received_msg = parse_buff(bytes_of_packages);

//         REQUIRE(received_msg.name == msg.name);
//         REQUIRE(received_msg.text == msg.text);
//     }
//     SECTION("function parse_buff should return type of Msg_t") {
//         Msg_t msg("John", "Hello, John! How are you? What's a new?");
//         std::vector<uint8_t> bytes_of_packages = make_buff(msg);

//         Msg_t received_msg = parse_buff(bytes_of_packages);

//         REQUIRE(received_msg.name == msg.name);
//         REQUIRE(received_msg.text == msg.text);
//     }
// }
