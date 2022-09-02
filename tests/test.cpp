#include "../include/header.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("check function calculate_count_of_packages") {
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

TEST_CASE("check function calculate_size_of_packages_in_bytes") {
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
