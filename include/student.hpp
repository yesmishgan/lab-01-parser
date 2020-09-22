
// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_


#include <any>
#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;

struct Student {
public:
    explicit Student(const json& j);
    const std::string& getName();
    const std::any getGroup();
    double getAvg();
    const std::any getDebt();
private:
    std::string Name;
    std::any Group;
    double Avg;
    std::any Debt;
};


#endif //INCLUDE_STUDENT_HPP_
