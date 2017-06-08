#include <iostream>
#include <string>

#include "collection.h"
#include "record.h"

using std::string;
using std::cout;

void collection::print()
{
    if (collection_.empty())
        cout << "None\n";
    for (auto it : collection_)
        cout << *it << std::endl;

}

void collection::add_member(record *record_ptr)
{
    collection_.push_back(record_ptr);
}
