
// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "student.hpp"
//#include "nlohmann/json.hpp"

using nlohmann::json;

Student::Student() {}

Student::Student(const json &j) {
    if (j.empty()){
        throw std::invalid_argument("Object student is empty");
    }
    Name = j.at("name").get<std::string>();
    Group = std::any{j.at("group")};
    if (j.at("avg").is_string()) {
        Avg = std::stod(j.at("avg").get<std::string>());
    } else if (j.at("avg").is_number()) {
        Avg = j.at("avg").get<double>();
    }else{
        throw std::invalid_argument("Avg cannot be another type!");
    }
    Debt = std::any{j.at("debt")};
}

const std::string &Student::getName() { return Name; }

const std::any Student::getGroup() { return Group; }

double Student::getAvg() { return Avg; }

const std::any Student::getDebt() { return Debt; }
