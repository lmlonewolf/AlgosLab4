#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>

class Gradebook
{
    struct Student {
        std::string name;
        int id = -1;
        int score = -1;
    };

    int count = 0;
    std::map<std::string, Student*> stud_name;
    std::map<int, Student*> stud_id;

public:
    void add_student(const std::string &name, int id, int score);
    bool update_score(int id, int new_score);
    bool update_score(const std::string &name, int new_score);
    int get_score(const std::string &name) const;
    int get_score(int id) const;

    double average_score() const;
    void print_max_score_student() const;
    void print_min_score_student() const;
    void print() const;
    void print_since(int min) const;
    size_t count_before(int min) const;
    bool is_student(const std::string &name) const;
    bool is_student(int id) const;
    bool remove_student(int id);
    bool save_to_file(const std::string &filename) const;
};