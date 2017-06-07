#include <iostream>
#include <string>
#include <algorithm>

#include "strings.h"
#include "catalog.h"

using std::cout;
using std::string;

catalog * catalog::s_instance = NULL;

struct collection_cmp_ftor
{
public:
    collection_cmp_ftor(string candidate): candidate_(candidate) {};

    bool operator()(collection *c)
    {
        return (c->name() == candidate_);
    }
private:
    string candidate_;
};

void catalog::add_collection(string name)
{
    collection *p = find_collection_by_name(name);

    if (p != nullptr)
    {
        cout << str_cat_coll_dupe << std::endl;
        return;
    }

    catalog_.push_back(new collection(name));
    cout << "Collection " << name << " added\n";

    collection_count_++;
}

void catalog::add_member(string name, string id)
{


}

collection *catalog::find_collection_by_name(string name)
{
    auto it = find_if(catalog_.begin(), catalog_.end(), collection_cmp_ftor(name));

    if (it != catalog_.end())
        return nullptr;
    else
        return *it;
}

void catalog::print_collection(string name)
{
    collection *p = find_collection_by_name(name);

    if (p == nullptr)
    {
        cout << str_cat_not_exist << std::endl;
        return;
    }

    cout << "Collection " << name << " contains:\n";
    p->print();
}

void catalog::print(void)
{
    if (catalog_.empty())
    {
        cout << str_cat_empty << std::endl;
        return;
    }

    cout << "Catalog contains " << collection_count_ << " collections:/n";

    for (auto p : catalog_)
    {
        cout << "Collection " << p->name() << " contains:\n";
        p->print();
    }
}

void catalog::print_alloc(void)
{
    cout << "Collections: " << collection_count_ << std::endl;
}
