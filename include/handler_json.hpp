
// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com


#ifndef INCLUDE_HANDLER_JSON_HPP_
#define INCLUDE_HANDLER_JSON_HPP_

#include <string>
#include <any>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include "student.hpp"

using nlohmann::json;

class handler_json {
public:
    explicit handler_json(const std::string &json_path);
    int size_meta();
    std::string getStudent(size_t i);
private:
    std::vector<int> weight_lines = {20, 10, 7, 15};
    std::vector<std::string> colomn = {"Name", "Group", "Avg", "Debt"};
    size_t size_arr = 0;
    std::vector<Student> students;
};

#endif // INCLUDE_HANDLER_JSON_HPP_
