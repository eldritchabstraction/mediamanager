#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <iostream>
#include <string>
#include <list>

#include "record.h"

// a collection is a list of records

// a catalog is a list of collections

/*
 * a container that stores references to a set of records
 */
class collection
{
public:
    collection(std::string name): name_(name) {};
    void add_member(record *record_ptr);
    int member_count() { return collection_.size(); }

    void print(void);
    // used explicitly for saves, which is annoying
    void print_title(std::ofstream &save);

    std::string name() { return name_; }

private:
    std::string name_;
    std::list<record*> collection_;
};




#endif
