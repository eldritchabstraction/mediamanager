#include <iostream>
#include <string>
#include <algorithm>

#include "strings.h"
#include "catalog.h"

using std::cout;
using std::string;

catalog * catalog::s_instance = NULL;

struct collection_compare
{
public:
    collection_compare(string candidate): candidate_(candidate) {};

    bool operator()(collection &c)
    {
        return (c.name() == candidate_);
    }


private:
    string candidate_;
};

void catalog::add_collection(string name)
{
    auto collection_it = find_if(catalog_.begin(), catalog_.end(), collection_compare(name));

    if (collection_it != catalog_.end())
    {
        cout << str_cat_coll_dupe << std::endl;
        return;
    }

    catalog_.push_back(collection(name));
    cout << "Collection " << name << " added\n";

    collection_count_++;
}

void catalog::add_member(string name, string id)
{

}

void catalog::print_collection(string name)
{
    auto collection_it = find_if(catalog_.begin(), catalog_.end(), collection_compare(name));

    if (collection_it == catalog_.end())
    {
        cout << str_cat_not_exist << std::endl;
        return;
    }

    cout << "Collection " << name << " contains:\n";
    collection_it->print();
}

void catalog::print(void)
{
    if (catalog_.empty())
    {
        cout << str_cat_empty << std::endl;
        return;
    }

    cout << "Catalog contains " << collection_count_ << " collections:/n";

    for (auto collection_it : catalog_)
    {
        cout << "Collection " << collection_it.name() << " contains:\n";
        collection_it.print();
    }
}

void catalog::print_alloc(void)
{
    cout << "Collections: " << collection_count_ << std::endl;
}
