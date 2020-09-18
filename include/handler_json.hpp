
// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com


#ifndef INCLUDE_HANDLER_JSON_HPP_
#define INCLUDE_HANDLER_JSON_HPP_

#include <string>
#include <any>
#include <nlohmann/json.hpp>
#include <fstream>

#include <vector>
//#include
//"../../.hunter/_Base/9a3594a/9b2c9d4/48401e9/Install/include/nlohmann/json.hpp"

using nlohmann::json;

class handler_json {
public:
    explicit handler_json(const std::string &json_path);

private:
    std::vector<int> weight_lines = {20, 10, 7, 15};
    std::vector<std::string> colomn = {"Name", "Group", "Avg", "Debt"};
};

#endif // INCLUDE_HANDLER_JSON_HPP_
