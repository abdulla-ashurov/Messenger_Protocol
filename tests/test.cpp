#include "../include/header.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("test function calculate_count_of_packages") {
    SECTION("should be 3 packages") {
        const size_t length_of_sender_message = 63;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 3;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 3 packages") {
        const size_t length_of_sender_message = 77;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 3;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 3 packages") {
        const size_t length_of_sender_message = 93;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 3;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 2 packages") {
        const size_t length_of_sender_message = 32;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 2;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 2 packages") {
        const size_t length_of_sender_message = 55;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 2;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 2 packages") {
        const size_t length_of_sender_message = 62;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 2;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 1 packages") {
        const size_t length_of_sender_message = 1;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 1;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 1 packages") {
        const size_t length_of_sender_message = 15;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 1;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
    SECTION("should be 1 packages") {
        const size_t length_of_sender_message = 31;
        const size_t max_length_of_message_in_one_package = 31;
   
        const size_t expected_value = 1;
        REQUIRE(calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package) == expected_value);
    }
}

TEST_CASE("test function calculate_size_of_packages_in_bytes") {
    SECTION("should be 23 bytes") {
        const size_t package_header_size_in_bytes = 2;
        const size_t length_of_sender_name = 4;
        const size_t length_of_sender_message = 17;

        const size_t max_length_of_message_in_one_package = 31;
        const size_t count_of_packages = calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package);

        const size_t expected_value = 23;
        REQUIRE(calculate_size_of_packages_in_bytes(
            package_header_size_in_bytes, length_of_sender_name, length_of_sender_message, count_of_packages) == expected_value
        );
    }
    SECTION("should be 57 bytes") {
        const size_t package_header_size_in_bytes = 2;
        const size_t length_of_sender_name = 8;
        const size_t length_of_sender_message = 37;

        const size_t max_length_of_message_in_one_package = 31;
        const size_t count_of_packages = calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package);

        const size_t expected_value = 57;
        REQUIRE(calculate_size_of_packages_in_bytes(
            package_header_size_in_bytes, length_of_sender_name, length_of_sender_message, count_of_packages) == expected_value
        );
    }
    SECTION("should be 144 bytes") {
        const size_t package_header_size_in_bytes = 2;
        const size_t length_of_sender_name = 15;
        const size_t length_of_sender_message = 93;

        const size_t max_length_of_message_in_one_package = 31;
        const size_t count_of_packages = calculate_count_of_packages(length_of_sender_message, max_length_of_message_in_one_package);

        const size_t expected_value = 144;
        REQUIRE(calculate_size_of_packages_in_bytes(
            package_header_size_in_bytes, length_of_sender_name, length_of_sender_message, count_of_packages) == expected_value
        );
    }
}

TEST_CASE("test function set_flag") {
    SECTION("in vector should be {160} value") {
        std::vector<uint8_t> package(1);
        set_flag(package.begin());

        const size_t expected_value = 160;
        REQUIRE(package[0] == expected_value);
    }
}

TEST_CASE("test function set_name_length") {
    SECTION("in vector should be {0} value") {
        std::vector<uint8_t> package(1);
        const size_t name_length = 0;
        set_name_length(package.begin(), name_length);

        const size_t expected_value = 0;
        REQUIRE(package[0] == expected_value);
    }
    SECTION("in vector should be {28} value") {
        std::vector<uint8_t> package(1);
        const size_t name_length = 7;
        set_name_length(package.begin(), name_length);

        const size_t expected_value = 14;
        REQUIRE(package[0] == expected_value);
    }
    SECTION("in vector should be {30} value") {
        std::vector<uint8_t> package(1);
        const size_t name_length = 15;
        set_name_length(package.begin(), name_length);

        const size_t expected_value = 30;
        REQUIRE(package[0] == expected_value);
    }
}

TEST_CASE("test function set_msg_length") {
    SECTION("in vector should be {0, 0} values") {
        std::vector<uint8_t> package(2);
        const size_t msg_length = 0;
        set_msg_length(package.begin(), msg_length);

        std::vector<uint8_t> expected_values{0, 0};

        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_values[i]);
    }
    SECTION("in vector should be {0, 240} values") {
        std::vector<uint8_t> package(2);
        const size_t msg_length = 15;
        set_msg_length(package.begin(), msg_length);

        std::vector<uint8_t> expected_values{0, 240};

        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_values[i]);
    }
    SECTION("in vector should be {1, 240} values") {
        std::vector<uint8_t> package(2);
        const size_t msg_length = 31;
        set_msg_length(package.begin(), msg_length);

        std::vector<uint8_t> expected_values{1, 240};

        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_values[i]);
    }
}

TEST_CASE("test function set_crc4") {
    SECTION("in vector should be {0} values") {
        std::vector<uint8_t> package(1);
        const size_t crc4 = 0;
        set_crc4(package.begin(), crc4);

        const size_t expected_values = 0;
        REQUIRE(package[0] == expected_values);
    }
    SECTION("in vector should be {7} values") {
        std::vector<uint8_t> package(1);
        const size_t crc4 = 7;
        set_crc4(package.begin(), crc4);

        const size_t expected_values = 7;
        REQUIRE(package[0] == expected_values);
    }
    SECTION("in vector should be {15} values") {
        std::vector<uint8_t> package(1);
        const size_t crc4 = 15;
        set_crc4(package.begin(), crc4);

        const size_t expected_values = 15;
        REQUIRE(package[0] == expected_values);
    }
}

TEST_CASE("test function set_header") {
    SECTION("in vector should be {169, 111} values") {
        std::vector<uint8_t> package(2);
        const size_t length_of_sender_name = 4;
        const size_t length_of_sender_message = 22;
        const size_t crc4_value = 15;
        set_header(package.begin(), length_of_sender_name, length_of_sender_message, crc4_value);

        std::vector<uint8_t> expected_values{169, 111};
        
        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_values[i]);
    }
    SECTION("in vector should be {169, 255} values") {
        std::vector<uint8_t> package(2);
        const size_t length_of_sender_name = 4;
        const size_t length_of_sender_message = 31;
        const size_t crc4_value = 15;
        set_header(package.begin(), length_of_sender_name, length_of_sender_message, crc4_value);

        std::vector<uint8_t> expected_values{169, 255};

        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_values[i]);
    }
}

TEST_CASE("test function set_sender_name") {
    SECTION("in vector should be \"John\"") {
        const std::string name = "John";
        std::vector<uint8_t> package(name.length());
        set_sender_name(package.begin(), package.end(), name);

        const std::string expected_name = "John";

        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_name[i]);
    }
    SECTION("in vector should be \"John Smith\"") {
        const std::string name = "John Smith";
        std::vector<uint8_t> package(name.length());
        set_sender_name(package.begin(), package.end(), name);

        const std::string expected_name = "John Smith";
        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_name[i]);
    }
}

TEST_CASE("test function set_sender_msg") {
    SECTION("in vector should be \"Hello\"") {
        const std::string msg = "Hello";
        std::vector<uint8_t> package(msg.length());
        set_sender_msg(package.begin(), package.end(), msg, 0);

        const std::string expected_msg = "Hello";
        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_msg[i]);
    }
    SECTION("in vector should be \"Hello, John! How are you? What's a new?\"") {
        const std::string msg = "Hello, John! How are you?";
        std::vector<uint8_t> package(msg.length());
        set_sender_msg(package.begin(), package.end(), msg, 0);

        const std::string expected_msg = "Hello, John! How are you?";
        for (size_t i = 0; i < package.size(); i++)
            REQUIRE(package[i] == expected_msg[i]);
    }
}

TEST_CASE("test function make_buff, when it returns 1 package") {
    Msg_t msg{"John", "Hello World!"};
    std::vector<uint8_t> bytes_of_packages = make_buff(msg);
    
    SECTION("vector size should be 18 bytes") {
        const size_t expected_size = 18;
        REQUIRE(bytes_of_packages.size() == expected_size);
    }
    SECTION("check package header fields") {
        std::vector<uint8_t> expected_header_values{168, 192};
        const size_t package_header_size_in_bytes = 2;

        for (size_t i = 0; i < package_header_size_in_bytes; i++)
            REQUIRE(bytes_of_packages[i] == expected_header_values[i]);
    }
    SECTION("check sender name and sender message in package") {
        const std::string expected_name = "John";
        size_t start_index = 2, end_index = start_index + expected_name.length();
        
        for (size_t i = 0; start_index < end_index; start_index++, i++)
            REQUIRE(bytes_of_packages[start_index] == expected_name[i]);

        const std::string expected_message = "Hello World!";
        
        for (size_t i = 0; start_index < bytes_of_packages.size(); start_index++, i++)
            REQUIRE(bytes_of_packages[start_index] == expected_message[i]);
    }
}

TEST_CASE("test function make_buff, when it returns 2 package") {
    Msg_t msg{"John Smith", "Hello, John! How are you? What's a new?"};
    std::vector<uint8_t> bytes_of_packages = make_buff(msg);
    const size_t package_header_size_in_bytes = 2;
    
    SECTION("vector size should be 63 bytes") {
        const size_t expected_size = 63;
        REQUIRE(bytes_of_packages.size() == expected_size);
    }
    SECTION("check first package") {
        std::vector<uint8_t> expected_header_values{181, 240};

        size_t start_index = 0;
        const size_t package_header_size_in_bytes = 2;

        for (size_t i = 0; i < package_header_size_in_bytes; i++, start_index++)
            REQUIRE(bytes_of_packages[start_index] == expected_header_values[i]);

        const std::string expected_name = "John Smith";
        size_t end_index = start_index + expected_name.length();
        
        for (size_t i = 0; start_index < end_index; i++, start_index++)
            REQUIRE(bytes_of_packages[start_index] == expected_name[i]);

        const std::string expected_message = "Hello, John! How are you? What'";
        end_index = start_index + 31;

        for (size_t i = 0; start_index < end_index; i++, start_index++)
            REQUIRE(bytes_of_packages[start_index] == expected_message[i]);
    }
    
    SECTION("check second package") {
        std::vector<uint8_t> expected_header_values{180, 128};

        size_t start_index = 43;
        const size_t package_header_size_in_bytes = 2;

        for (size_t i = 0; i < package_header_size_in_bytes; i++, start_index++)
            REQUIRE(bytes_of_packages[start_index] == expected_header_values[i]);

        const std::string expected_name = "John Smith";
        size_t end_index = start_index + expected_name.length();
        
        for (size_t i = 0; start_index < end_index; i++, start_index++)
            REQUIRE(bytes_of_packages[start_index] == expected_name[i]);

        const std::string expected_message = "s a new?";

        for (size_t i = 0; start_index < bytes_of_packages.size(); i++, start_index++)
            REQUIRE(bytes_of_packages[start_index] == expected_message[i]);
    }
}
