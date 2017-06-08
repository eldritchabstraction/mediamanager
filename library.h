#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "record.h"

/*
 * notes: a singleton to hold all records
 */
class library
{
public:
    static library *s_instance;
    library(): id_counter_(1), records_count_(0) {};

    void add_record(std::string medium, std::string title);
    void delete_record(std::string title);
    int modify_record(record x);

    void modify_rating(std::string record_id, std::string rating);

    int validate_id(std::string record_id);
    int validate_title(std::string title);

    record * find_record_by_title(string title);
    record * find_record_by_id(string id);

    void print(void);
    void print_save(std::ofstream &save);
    void print_alloc(void);
    void print_id(std::string record_id);
    void print_title(std::string title);

    void clear(void);

    static library * instance()
    {
        if (!s_instance)
            s_instance = new library;

        return s_instance;
    }

    int records_count(void) { return records_count_; }

    void set_id_counter(int id_counter) { id_counter_ = id_counter; }
private:
    int validate_medium(std::string medium);

    int id_counter_;
    int records_count_;
    std::vector<record*> library_;
};

#endif
