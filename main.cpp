#include "Header.h"

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