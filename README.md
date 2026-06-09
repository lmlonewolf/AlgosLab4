# Лабораторная работа 4

# Электронный журнал группы (Gradebook)

## В ходе работы был реализован следующий функционал
### Обязательная часть
* Добавление студента в журнал
* Выставление или обновление балла
* Получение балла по имени или ID
* Вывод всех студентов и их результатов
### Вариативная часть
1. Подсчитывать средний балл по всем студентам
2. Находить студента с максимальным баллом
3. Находить студента с минимальным баллом
4. Выводить только тех студентов, чей балл не ниже заданного
5. Подсчитывать количество студентов, не прошедших порог
6. Добавить удаление студента из журнала
7. Проверять, есть ли студент с заданным именем или ID
8. Сохранять журнал в файл

---

## Реализация
### Класс `Gradebook`
**Структура**
```cpp
class Gradebook {
    struct Student {
        std::string name;
        int id = -1;
        int score = -1;
    };

    int count = 0;
    std::map<std::string, size_t> name_index;
    std::map<int, size_t> id_index;


public:
// Обязательная часть
    void add_student(const std::string& name, int id, int score);
    bool update_score(int id, int new_score);
    bool update_score(const std::string& name, int new_score);
    int get_score(const std::string& name) const;
    int get_score(int id) const;

// Вариативная часть
    double get_average_score(void) const;
    void print_max_score_student(void) const;
    void print_min_score_student(void) const;
    void print_above_threshold(int threshold) const;
    size_t count_below_threshold(int threshold) const;
    bool has_student(const std::string& name) const;
    bool has_student(int id) const;
    bool remove_student(int id);
    bool remove_student(const std::string& name);
    bool save_to_file(const std::string& filename) const;
    void print(void) const;
};
```


**Основные методы**
```cpp
// Добавить студента
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

// Обновить балл
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

// Получить балл
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
```

**Вариативная часть**
```cpp
// Средний балл
double Gradebook::average_score() const {
    if (count == 0)
        return 0.0;
    double sum = 0;
    for (const auto& it : stud_id)
        sum += it.second->score;
    return sum / count;
}

// Студент с максимальным баллом
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

// Студент с минимальным баллом
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

// Студенты с баллом выше порога
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

// Количество студентов с баллом ниже порога
size_t Gradebook::count_before(int min) const {
    size_t count = 0;
    for (const auto& it : stud_id) {
        if (it.second->score < min)
            count++;
    }
    return count;
}

// Проверка наличия студента в журнале
bool Gradebook::is_student(const std::string& name) const {
    return name_index.find(name) != name_index.end();
}
bool Gradebook::is_student(int id) const {
    return id_index.find(id) != id_index.end();
}

// Удаление студента
bool Gradebook::remove_student(int id) {
    auto it = stud_id.find(id);
    if (it == stud_id.end())
        return false;

    std::string name = it->second->name;
    stud_id.erase(id);
    stud_name.erase(name);
    return true;
}

// Сохранение в файл
bool Gradebook::save_to_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << count << "\n";
    for (const auto& it : stud_id)
        file << it.second->id << " " << it.second->score << " " << it.second->name << std::endl;
    return true;
}
```

---

## Тестирование работоспособности (`main.cpp`)
```cpp
int main() {
    Gradebook journal;

    journal.add_student("Ivan", 101, 45);
    journal.add_student("Anna", 102, 92);
    journal.add_student("Maria", 103, 85);
    journal.add_student("Petr", 104, 55);

    journal.print();

    std::cout << "Is Ann in Gradebook? " << (journal.is_student("Anna") ? "Yes" : "No") << std::endl;


    std::cout << "Average score: " << journal.average_score() << std::endl;
    journal.print_max_score_student();
    journal.print_min_score_student();
    std::cout << std::endl;

    int since = 60;
    journal.print_since(since);
    std::cout << "Count students with score lower minimum: "
        << journal.count_before(since) << std::endl;

    std::cout << "Delete studen with ID 104" << std::endl;
    journal.remove_student(104);
    journal.print();

    std::string filename = "journal.txt";
    if (journal.save_to_file(filename)) {
        std::cout << "Save succses to file: " << filename << std::endl;
    }

    return 0;
}
```
