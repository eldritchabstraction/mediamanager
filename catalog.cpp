#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "strings.h"
#include "catalog.h"
#include "library.h"

using std::cout;
using std::string;

catalog * catalog::s_instance = NULL;

struct collection_cmp_ftor
{
public:
    collection_cmp_ftor(string name): name_(name) {};

    bool operator()(collection *c)
    {
        if (c->name() == name_)
            return 1;
        else
            return 0;
    }
private:
    string name_;
};

void catalog::add_collection(string name)
{
    collection *p = find_collection_by_name(name);

    if (p != nullptr)
    {
        cout << str_coll_dupe << std::endl;
        return;
    }

    catalog_.push_back(new collection(name));
    cout << "Collection " << name << " added\n";

    collection_count_++;
}

void catalog::add_member(string name, string id)
{
    // check if collection exists
    collection *c_p = find_collection_by_name(name);

    if (c_p == nullptr)
    {
        cout << str_coll_not_exist << std::endl;
        return;
    }

    record *r_p = library::instance()->find_record_by_id(id);

    if (r_p == nullptr)
    {
        cout << str_record_id_not_exist << std::endl;
        return;
    }

    c_p->add_member(r_p);

    cout << "Member " << id << " " << r_p->title() << " added\n";
}

collection *catalog::find_collection_by_name(string name)
{
    auto it = find_if(catalog_.begin(), catalog_.end(), collection_cmp_ftor(name));

    if (it == catalog_.end())
        return nullptr;
    else
        return *it;
}

void catalog::print_collection(string name)
{
    collection *p = find_collection_by_name(name);

    if (p == nullptr)
    {
        cout << str_coll_not_exist << std::endl;
        return;
    }

    cout << "Collection " << name << " contains:" << std::endl;;
    p->print();
}

void catalog::print(void)
{
    if (catalog_.empty())
    {
        cout << str_cat_empty << std::endl;
        return;
    }

    cout << "Catalog contains " << collection_count_ << " collections:" << std::endl;

    for (auto p : catalog_)
    {
        cout << "Collection " << p->name() << " contains:" << std::endl;
        p->print();
    }
}

void catalog::print_save(std::ofstream &save)
{
    if (catalog_.empty())
    {
        return;
    }

    for (auto p : catalog_)
    {
        save << p->name() << " " << p->member_count() << std::endl;
        p->print_title(save);
    }

}

void catalog::print_alloc(void)
{
    cout << "Collections: " << collection_count_ << std::endl;
}
