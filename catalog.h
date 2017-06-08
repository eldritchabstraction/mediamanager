#ifndef CATALOG_H
#define CATALOG_H

#include <list>
#include <string>

#include "collection.h"

// this thing is a singleton as well
class catalog
{
public:
    static catalog *s_instance;

    catalog(): collection_count_(0) {};

    void add_collection(std::string collection_name);

    void add_member(std::string collection_name, std::string record_id);

    collection *find_collection_by_name(string collection_name);

    void print(void);
    void print_save(std::ofstream &save);
    void print_collection(std::string collection_name);
    void print_alloc(void);

    int collection_count(void) { return collection_count_; };

    void clear(void);

    static catalog* instance(void)
    {
        if (!s_instance)
            s_instance = new catalog;

        return s_instance;
    }

private:
    int collection_count_;

    std::list<collection*> catalog_;
};

#endif
