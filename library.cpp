#include <iostream>
#include <string>
#include <algorithm>

#include "strings.h"
#include "error.h"
#include "library.h"
#include "record.h"

using std::string;
using std::cout;

// initialize static instance
library *library::s_instance = 0;

int library::add_record(string medium, string title)
{
    // check for invalid medium
    if (validate_medium(medium))
        error_print("invalid medium: " + medium);

    // check for duplicate names
    for (auto it = library_.begin(); it != library_.end(); ++it)
    {
        if (it->title() == title)
        {
            cout << str_lib_dupe << std::endl;
            return 1;
        }
    }

    library_.push_back(record(medium, title, id_counter_));
    cout << "Record " << id_counter_  << " added\n";

    id_counter_++;
    records_count_++;

    return 0;
}

void library::print(void)
{
    if (library_.empty())
    {
        cout << str_lib_empty << std::endl;
        return;
    }

    cout << "Library contains " << records_count_ << " records:\n";
    for (auto record_it : library_)
    {
        record_it.print();
    }
}

void library::print_alloc(void)
{
    cout << "Records: " << records_count_ << std::endl;
}

struct ftor_record_id_cmp
{
public:
    ftor_record_id_cmp(int id): candidate_(id) {};
    bool operator()(record &r) { return (r.id() == candidate_); }

private:
    int candidate_;
};

void library::print_id(string id)
{
    auto record_it = find_if(library_.begin(), library_.end(),
                             ftor_record_id_cmp(std::stoi(id, nullptr, 10)));

    if (record_it == library_.end())
    {
        cout << str_record_id_not_exist << std::endl;
        return;
    }

    record_it->print();
}

struct ftor_record_title_cmp
{
public:
    ftor_record_title_cmp(string title): candidate_(title) {};
    bool operator()(record &r) { return (r.title() == candidate_); }

private:
    string candidate_;
};

void library::print_title(string title)
{
    auto record_it = find_if(library_.begin(), library_.end(),
                             ftor_record_title_cmp(title));

    if (record_it == library_.end())
    {
        cout << str_record_title_not_exist << std::endl;
        return;
    }

    record_it->print();
}

void library::modify_rating(string id, string rating)
{
    if (std::stoi(rating, nullptr, 10) > 5)
    {
        std::cout << str_rating_oob << std::endl;
        return;
    }
    auto record_it = find_if(library_.begin(), library_.end(),
                             ftor_record_id_cmp(std::stoi(id, nullptr, 10)));

    if (record_it == library_.end())
    {
        cout << str_record_id_not_exist << std::endl;
        return;
    }

    record_it->set_rating(rating);

    cout << "Rating for record " << record_it->id() << " changed to " << rating << std::endl;
}

void library::delete_record(string title)
{
    auto record_it = find_if(library_.begin(), library_.end(),
                             ftor_record_title_cmp(title));

    if (record_it == library_.end())
    {
        cout << str_record_title_not_exist << std::endl;
        return;
    }

    std::cout << "Record " << record_it->id() << " " << record_it->title() << " deleted\n";

    library_.erase(record_it);
    records_count_--;
}

int library::validate_medium(string medium)
{
    return (medium != "DVD" && medium != "VHS");
}

