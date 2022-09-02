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

TEST_CASE("test function set_header") {
    SECTION("in vector should be {169, 111} values") {
        std::vector<uint8_t> package(2);
        const size_t length_of_sender_name = 4;
        const size_t length_of_sender_message = 22;
        const size_t crc4_value = 15;
        set_header(package.begin(), length_of_sender_name, length_of_sender_message, crc4_value);

        std::vector<uint8_t> expected_values{169, 111};
        
        REQUIRE(package[0] == expected_values[0]);
        REQUIRE(package[1] == expected_values[1]);  
    }
    SECTION("in vector should be {169, 255} values") {
        std::vector<uint8_t> package(2);
        const size_t length_of_sender_name = 4;
        const size_t length_of_sender_message = 31;
        const size_t crc4_value = 15;
        set_header(package.begin(), length_of_sender_name, length_of_sender_message, crc4_value);

        std::vector<uint8_t> expected_values{169, 255};

        REQUIRE(package[0] == expected_values[0]);
        REQUIRE(package[1] == expected_values[1]);  
    }
}
