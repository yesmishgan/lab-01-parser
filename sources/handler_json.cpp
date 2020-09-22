
// Copyright 2020 Dolbnin Mikhail dolbnin@protonmail.com

#include "handler_json.hpp"
#include "student.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

handler_json::handler_json(const std::string &jsonPath) {
    json data;
    if (jsonPath[0] != '{') {
        if (jsonPath.empty()) {
            throw std::invalid_argument("the path is't available");
        }
        std::ifstream file{jsonPath};
        if (!file) {
            throw std::out_of_range{"unable to open json: " + jsonPath};
        }
        if(!(file >> data)){
            throw std::out_of_range("Incorrect json");
        }
    }else{
        data = json::parse(jsonPath);
    }
    if (data.empty()){
        throw std::invalid_argument("Object array is empty");
    }
    if (!data.at("items").is_array()){
        throw std::invalid_argument("JSON-file is not array. Try again");
    }
    if (data.at("items").size() != data.at("_meta").at("count")){
        throw std::out_of_range("_meta.count != len(items)");
    }
    size_arr = data.at("items").size();
    //size_arr = data.at("items").size();
    for (auto const& student : data.at("items")) {
        Student a(student);
        students.push_back(a);
    }
    size_t size = 0;
    for (auto i : students){
        if (i.getName().length() > size){size = i.getName().length();}
    }

    weight_lines[0] = size + 3;

    std::cout << std::left;
    for (size_t i = 0; i < 4; ++i){
        std::cout << std::setw(weight_lines[i]) << "| " + colomn[i];
    }
    std::cout << '|' << std::endl;
    for (size_t i = 0; i < 4; ++i){
        std::cout << std::setfill('-') << std::setw(weight_lines[i]) << '|';
    }

    std::cout << std::setfill(' ') << '|' << std::endl;
    for (size_t i = 0; i < students.size(); ++i){
        std::cout << std::left << std::setw(weight_lines[0])
            << "| " + students[i].getName();
        if ((std::any_cast<json> (students[i].getGroup())).is_number()){
            std::cout << "| " << std::setw(weight_lines[1] - 2)
            << std::any_cast<json> ((students[i].getGroup())).get<int>();
        }else{
            std::cout << "| " << std::setw(weight_lines[1] - 2)
            << std::any_cast<json>
                    ((students[i].getGroup())).get<std::string>();
        }
        std::cout << "| " << std::setw(weight_lines[2] - 2)
        << students[i].getAvg();
        if ((std::any_cast<json> (students[i].getDebt()).is_array())){
            if ((std::any_cast<json> (students[i].getDebt()).size()) > 1){
                std::cout << "| "
                << std::any_cast<json> (students[i].getDebt()).size()
                << std::setw(weight_lines[3] - 3) << " items";
            }else{
                std::vector<std::string> g =
                        std::any_cast<json>
                                (students[i].getDebt())
                                .get<std::vector<std::string>>();
                std::cout << "| " << std::setw(weight_lines[3] - 2) << g[0];
            }
        }else if ((std::any_cast<json> (students[i].getDebt()).is_string())){
            std::cout << "| " << std::setw(weight_lines[3] - 2) <<
                std::any_cast<json>(students[i].getDebt()).get<std::string>();
        }else{
            std::cout << std::setw(weight_lines[3]) << "| null";
        }
        std::cout << '|';
        std::cout << std::endl;
        for (size_t t = 0; t < 4; ++t){
            std::cout << std::setfill('-') << std::setw(weight_lines[t]) << '|';
        }
        std::cout << '|' << std::endl;
        std::cout << std::setfill(' ');
    }
}

std::string handler_json::getStudent(size_t i) {
    std::stringstream ss;
    ss << std::left << std::setw(weight_lines[0])
              << "| " + students[i].getName();
    if ((std::any_cast<json> (students[i].getGroup())).is_number()){
        ss << "| " << std::setw(weight_lines[1] - 2)
                  << std::any_cast<json> ((students[i].getGroup())).get<int>();
    }else{
        ss << "| " << std::setw(weight_lines[1] - 2)
                  << std::any_cast<json>
                          ((students[i].getGroup())).get<std::string>();
    }
    ss << "| " << std::setw(weight_lines[2] - 2)
              << students[i].getAvg();
    if ((std::any_cast<json> (students[i].getDebt()).is_array())){
        if ((std::any_cast<json> (students[i].getDebt()).size()) > 1){
            ss << "| "
                      << std::any_cast<json> (students[i].getDebt()).size()
                      << std::setw(weight_lines[3] - 3) << " items";
        }else{
            std::vector<std::string> g =
                    std::any_cast<json>
                            (students[i].getDebt())
                            .get<std::vector<std::string>>();
            ss << "| " << std::setw(weight_lines[3] - 2) << g[0];
        }
    }else if ((std::any_cast<json> (students[i].getDebt()).is_string())){
        ss << "| " << std::setw(weight_lines[3] - 2) <<
                  std::any_cast<json>(students[i].getDebt()).get<std::string>();
    }else{
        ss << std::setw(weight_lines[3]) << "| null";
    }
    ss << '|';
    return ss.str();
}
