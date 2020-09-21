// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <handler_json.hpp>
#include <sstream>

TEST(handler_json, empty_path){
    ASSERT_THROW(handler_json(""), std::invalid_argument);
}

TEST(handler_json, invalid_path){
    ASSERT_THROW(handler_json("/sd.json"), std::out_of_range);
}

TEST(handler_json, json_is_not_array){
    ASSERT_THROW(handler_json("../tests/is_not_array.json"),
            std::invalid_argument);
}

TEST(handler_json, size_test){
    handler_json a("../tests/test.json");
    ASSERT_EQ(a.size_meta(), 3);
}

TEST(handler_json, correct_input_1){
    Student a(json::parse(R"({
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": "AY"
    })"));
    ASSERT_EQ(a.getName(), "Ivanov Petr");
    ASSERT_EQ(std::any_cast<json>(a.getGroup()).get<std::string>(), "1");
    ASSERT_EQ(std::any_cast<json>(a.getDebt()).get<std::string>(), "AY");
    ASSERT_DOUBLE_EQ(a.getAvg(), 4.25);
}

TEST(handler_json, correct_input_2){
    Student a(json::parse(R"({
      "name": "Ivanov Petr",
      "group": 100,
      "avg": 5.00,
      "debt": ["AY"]
    })"));
    ASSERT_EQ(a.getName(), "Ivanov Petr");
    ASSERT_EQ(std::any_cast<json>(a.getGroup()).get<int>(), 100);
    ASSERT_TRUE(std::any_cast<json>(a.getDebt()).is_array());
    ASSERT_DOUBLE_EQ(a.getAvg(), 5.00);
}

TEST(handler_json, correct_out){
    handler_json a("../tests/test.json");
    ASSERT_EQ(a.getStudent(0),
            "| Ivanov Petr   | 1       | 4.25 | null         |");
    ASSERT_EQ(a.getStudent(1),
            "| Sidorov Ivan  | 31      | 4    | C++          |");
    ASSERT_EQ(a.getStudent(2),
            "| Pertov Nikita | IU8-31  | 3.33 | 3 items      |");
}

