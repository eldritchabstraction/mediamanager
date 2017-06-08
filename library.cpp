#include <iostream>
#include <fstream>
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

struct record_cmp_ftor
{
public:
    record_cmp_ftor(int id): id_(id), title_("") {};
    record_cmp_ftor(string title): title_(title), id_(0) {};
    bool operator()(record *r)
    {
        if (r->title() == title_)
            return 1;
        else if (r->id() == id_)
            return 1;
        else
            return 0;
    }

private:
    int id_;
    string title_;
};

void library::add_record(string medium, string title)
{
    // check for invalid medium
    if (validate_medium(medium))
        error_print("invalid medium: " + medium);

    // check for duplicate names
    record *p = find_record_by_title(title);

    if (p != nullptr)
    {
        cout << str_lib_dupe << std::endl;
        return;
    }

    library_.push_back(new record(medium, title, id_counter_));
    cout << "Record " << id_counter_  << " added\n";

    id_counter_++;
    records_count_++;
}

void library::print(void)
{
    if (library_.empty())
    {
        cout << str_lib_empty << std::endl;
        return;
    }

    cout << "Library contains " << records_count_ << " records:\n";
    for (auto p: library_)
    {
        cout << *p << std::endl;
    }
}

void library::print_save(std::ofstream &save)
{
    if (library_.empty())
    {
        return;
    }

    for (auto p: library_)
    {
        save << *p << std::endl;
    }
}

void library::print_alloc(void)
{
    cout << "Records: " << records_count_ << std::endl;
}

void library::print_id(string id)
{
    record *p = find_record_by_id(id);

    if (p == nullptr)
    {
        cout << str_record_id_not_exist << std::endl;
        return;
    }

    cout << *p << std::endl;
}

void library::print_title(string title)
{
    record *p = find_record_by_title(title);

    if (p == nullptr)
    {
        cout << str_record_title_not_exist << std::endl;
        return;
    }

    cout << *p << std::endl;
}

void library::modify_rating(string id, string rating)
{
    if (std::stoi(rating, nullptr, 10) > 5)
    {
        std::cout << str_rating_oob << std::endl;
        return;
    }

    record *p = find_record_by_id(id);

    if (p == nullptr)
    {
        cout << str_record_id_not_exist << std::endl;
        return;
    }

    p->set_rating(rating);

    cout << "Rating for record " << p->id() << " changed to " << rating << std::endl;
}

void library::delete_record(string title)
{
    record *p = find_record_by_title(title);

    if (p == nullptr)
    {
        cout << str_record_title_not_exist << std::endl;
        return;
    }

    std::cout << "Record " << p->id() << " " << p->title() << " deleted\n";

    // time to exercise the erase/remove idiom
    library_.erase(std::remove_if(library_.begin(), library_.end(),
                   record_cmp_ftor(title)), library_.end());

    records_count_--;
}

record * library::find_record_by_id(string id)
{
    auto it = find_if(library_.begin(), library_.end(),
                      record_cmp_ftor(std::stoi(id, nullptr, 10)));

    if (it == library_.end())
    {
        return nullptr;
    }
    else
    {
        return *it;
    }
}

record * library::find_record_by_title(string title)
{
    auto it = find_if(library_.begin(), library_.end(),
                      record_cmp_ftor(title));

    if (it == library_.end())
    {
        return nullptr;
    }
    else
    {
        return *it;
    }
}

int library::validate_medium(string medium)
{
    return (medium != "DVD" && medium != "VHS");
}

void library::clear(void)
{
    id_counter_ = 1;
    records_count_ = 0;
    for (auto r : library_)
        delete r;
    library_.clear();

}

