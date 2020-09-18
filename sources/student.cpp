
// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "student.hpp"
//#include "nlohmann/json.hpp"

using nlohmann::json;

Student::Student() {}

Student::Student(const json &j) {
    Name = j.at("name").get<std::string>();
    Group = std::any{j.at("group")};
    if (j.at("avg").is_string()) {
        Avg = std::stod(j.at("avg").get<std::string>());
    }
    if (j.at("avg").is_number()) {
        Avg = j.at("avg").get<double>();
    }
    Debt = std::any{j.at("debt")};
}

const std::string &Student::getName() { return Name; }

const std::any Student::getGroup() { return Group; }

double Student::getAvg() { return Avg; }

const std::any Student::getDebt() { return Debt; }
