#include "Header.h"


void Gradebook::more_size() {
    if (capacity == 0)
        capacity = 4;
    else
        capacity *= 2;
    Student* new_students = new Student[capacity];

    for (size_t i = 0; i < size; ++i)
        new_students[i] = students[i];

    delete[] students;
    students = new_students;
}

void Gradebook::rebuild_indexes() {
    name_index.clear();
    id_index.clear();
    for (size_t i = 0; i < size; ++i) {
        name_index[students[i].name] = i;
        id_index[students[i].id] = i;
    }
}

Gradebook::Gradebook() : students(nullptr), capacity(0), size(0) {}

Gradebook::~Gradebook() {
    delete[] students;
}


void Gradebook::add_student(const std::string& name, int id, int score) {
    auto it = id_index.find(id);
    if (it != id_index.end()) {
        size_t idx = it->second;
        students[idx].name = name;
        students[idx].score = score;
        name_index[name] = idx;
        return;
    }

    if (size >= capacity)
        more_size();

    size_t new_idx = size;
    students[new_idx] = { name, id, score };
    size++;

    name_index[name] = new_idx;
    id_index[id] = new_idx;
}

bool Gradebook::update_score(int id, int new_score) {
    auto it = id_index.find(id);
    if (it != id_index.end()) {
        students[it->second].score = new_score;
        return true;
    }
    return false;
}

bool Gradebook::update_score(const std::string& name, int new_score) {
    auto it = name_index.find(name);
    if (it != name_index.end()) {
        students[it->second].score = new_score;
        return true;
    }
    return false;
}

int Gradebook::get_score(const std::string& name) const {
    auto it = name_index.find(name);
    if (it != name_index.end())
        return students[it->second].score;
    return -1;
}

int Gradebook::get_score(int id) const {
    auto it = id_index.find(id);
    if (it != id_index.end())
        return students[it->second].score;
    return -1;
}

double Gradebook::average_score() const {
    if (size == 0)
        return 0.0;
    double sum = 0;
    for (size_t i = 0; i < size; ++i)
        sum += students[i].score;
    return sum / size;
}

int Gradebook::print_max_score_student() const {
    if (size == 0) return -1;
    size_t max_idx = 0;
    for (size_t i = 1; i < size; ++i) {
        if (students[i].score > students[max_idx].score)
            max_idx = i;
    }
    std::cout << "Best student: " << students[max_idx].name << " (ID: " << students[max_idx].id << ") Score " << students[max_idx].score << std::endl;
    return students[max_idx].score;
}

int Gradebook::print_min_score_student() const {
    if (size == 0) return -1;
    size_t min_idx = 0;
    for (size_t i = 1; i < size; ++i) {
        if (students[i].score < students[min_idx].score)
            min_idx = i;
    }
    std::cout << "Worst student: " << students[min_idx].name << " (ID: " << students[min_idx].id << ") Score " << students[min_idx].score << std::endl;
    return students[min_idx].score;
}

void Gradebook::print() const {
    std::cout << "Gradebook" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << "ID: " << students[i].id
            << " | Name: " << students[i].name
            << " -> Score: " << students[i].score << std::endl;
    }
    std::cout << std::endl;
}

void Gradebook::print_since(int min) const {
    std::cout << "Students with score above " << min << ':' << std::endl;
    bool found = false;
    for (size_t i = 0; i < size; ++i) {
        if (students[i].score >= min) {
            std::cout << "ID: " << students[i].id << " | Name: " << students[i].name << " -> Score: " << students[i].score << std::endl;
            found = true;
        }
    }
    if (!found)
        std::cout << "Nobody" << std::endl;
    std::cout << std::endl;
}

size_t Gradebook::count_before(int min) const {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (students[i].score < min)
            count++;
    }
    return count;
}

bool Gradebook::is_student(const std::string& name) const {
    return name_index.find(name) != name_index.end();
}

bool Gradebook::is_student(int id) const {
    return id_index.find(id) != id_index.end();
}

bool Gradebook::remove_student(int id) {
    auto it = id_index.find(id);
    if (it == id_index.end())
        return false;

    size_t target_idx = it->second;

    for (size_t i = target_idx; i < size - 1; ++i)
        students[i] = students[i + 1];
    size--;

    rebuild_indexes();
    return true;
}

bool Gradebook::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << size << "\n";
    for (size_t i = 0; i < size; ++i)
        file << students[i].id << " " << students[i].score << " " << students[i].name << std::endl;
    return true;
}