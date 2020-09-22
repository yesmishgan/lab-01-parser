// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <handler_json.hpp>
#include <sstream>

TEST(handler_json, empty_path){
    ASSERT_THROW(handler_json(""), std::invalid_argument);
}

TEST(handler_json, empty_student){
    ASSERT_THROW(Student(json::parse(R"({})")), std::invalid_argument);
}

TEST(handler_json, empty_array){
    ASSERT_THROW(handler_json((R"({})")), std::invalid_argument);
}

TEST(handler_json, incorrect_avg){
    ASSERT_THROW(Student(json::parse(R"({
      "name": "Ivanov Petr",
      "group": "1",
      "avg": [],
      "debt": "AY"
    })")), std::invalid_argument);
}

TEST(handler_json, invalid_path){
    ASSERT_THROW(handler_json("/sd.json"), std::out_of_range);
}

TEST(handler_json, simple_array){
    handler_json a(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
    ASSERT_EQ(a.getStudent(2),
            "| Pertov Nikita | IU8-31  | 3.33 | Network      |");
}

TEST(handler_json, json_is_not_array){
    ASSERT_THROW(handler_json(R"({
  "items" : 5
})"),
            std::invalid_argument);
}

TEST(handler_json, correct_object){
    ASSERT_THROW(handler_json("tes.json"), std::out_of_range);
}

TEST(handler_json, open_file){
    handler_json a("../test.json");
    ASSERT_EQ(a.getStudent(0),
              "| Ivanov Petr   | 1       | 4.25 | null         |");
}

TEST(handler_json, size_test){
    ASSERT_THROW(handler_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 5
  }
})"), std::out_of_range);
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
    handler_json a(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
    ASSERT_EQ(a.getStudent(0),
            "| Ivanov Petr   | 1       | 4.25 | null         |");
    ASSERT_EQ(a.getStudent(1),
            "| Sidorov Ivan  | 31      | 4    | C++          |");
    ASSERT_EQ(a.getStudent(2),
            "| Pertov Nikita | IU8-31  | 3.33 | 3 items      |");
}

