#include "Header.h"


void Gradebook::add_student(const std::string& name, int id, int score) {
    if (stud_id.find(id) != stud_id.end()) {
        Student* stud = stud_id[id];
        stud->name = name;
        stud->score = score;
        return;
    }

    Student* stud = new Student(name, id, score);
    stud_name[name] = stud;
    stud_id[id] = stud;
    count += 1;
}

bool Gradebook::update_score(int id, int new_score) {
    if (stud_id.find(id) != stud_id.end()) {
        stud_id[id]->score = new_score;
        return true;
    }
    return false;
}
bool Gradebook::update_score(const std::string& name, int new_score) {
    if (stud_name.find(name) != stud_name.end()) {
        stud_name[name]->score = new_score;
        return true;
    }
    return false;
}

int Gradebook::get_score(const std::string& name) const {
    auto it = stud_name.find(name);
    if (it != stud_name.end())
        return it->second->score;
    return -1;
}
int Gradebook::get_score(int id) const {
    auto it = stud_id.find(id);
    if (it != stud_id.end())
        return it->second->score;
    return -1;
}


double Gradebook::average_score() const {
    if (count == 0)
        return 0.0;
    double sum = 0;
    for (const auto& it : stud_id)
        sum += it.second->score;
    return sum / count;
}

void Gradebook::print_max_score_student() const {
    if (count == 0) {
        std::cout << "Nobody students" << std::endl;
        return;
    }
    Student* max_stud = nullptr;
    int max = -1;
    for (const auto& it : stud_id) {
        if (it.second->score >= max) {
            max_stud = it.second;
            max = max_stud->score;
        }
    }
    std::cout << "Best student: " << max_stud->name << " (ID: " << max_stud->id << ") Score " << max_stud->score << std::endl;
}
void Gradebook::print_min_score_student() const {
    if (count == 0) {
        std::cout << "Nobody students" << std::endl;
        return;
    }
    Student* min_stud = nullptr;
    int min = -1;
    for (const auto& it : stud_id) {
        if (min == -1)
            min = it.second->score;
        if (it.second->score <= min) {
            min_stud = it.second;
            min = min_stud->score;
        }
    }
    std::cout << "Worst student: " << min_stud->name << " (ID: " << min_stud->id << ") Score " << min_stud->score << std::endl;
}

void Gradebook::print() const {
    std::cout << "Gradebook" << std::endl;
    for (const auto& it : stud_id)
        std::cout << "ID: " << it.second->id << " | Name: " << it.second->name << " -> Score: " << it.second->score << std::endl;
}

void Gradebook::print_since(int min) const {
    std::cout << "Students with score above " << min << ':' << std::endl;
    bool found = false;
    for (const auto& it : stud_id) {
        if (it.second->score >= min) {
            std::cout << "ID: " << it.second->id << " | Name: " << it.second->name << " -> Score: " << it.second->score << std::endl;
            found = true;
        }
    }
    if (!found)
        std::cout << "Nobody" << std::endl;
    std::cout << std::endl;
}

size_t Gradebook::count_before(int min) const {
    size_t count = 0;
    for (const auto& it : stud_id) {
        if (it.second->score < min)
            count++;
    }
    return count;
}

bool Gradebook::is_student(const std::string& name) const {
    return stud_name.find(name) != stud_name.end();
}
bool Gradebook::is_student(int id) const {
    return stud_id.find(id) != stud_id.end();
}

bool Gradebook::remove_student(int id) {
    auto it = stud_id.find(id);
    if (it == stud_id.end())
        return false;

    std::string name = it->second->name;
    stud_id.erase(id);
    stud_name.erase(name);
    return true;
}

bool Gradebook::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << count << "\n";
    for (const auto& it : stud_id)
        file << it.second->id << " " << it.second->score << " " << it.second->name << std::endl;
    return true;
}