/*
 * This project is from:
 * http://www.umich.edu/~eecs381/proj0/
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cctype>

#include "strings.h"
#include "debug.h"

#include "library.h"
#include "catalog.h"

using std::cout;
using std::string;
using std::list;
using std::vector;

/*
 * this function splits strings into a vector for easier processing?
 */
static vector<string> split(const string input)
{
    vector<string> return_vector;
    string::const_iterator word_begin = input.begin(), word_end;

    while(word_begin != input.end())
    {
        // find the first non-whitespace character
        word_begin = find_if(word_begin, input.end(),
                             [](const char c) { return !std::isspace(c); });
        // find the first
        word_end = find_if(word_begin, input.end(),
                           [](const char c) { return std::isspace(c); });

        return_vector.push_back(string(word_begin, word_end));

        word_begin = word_end;
    }

    return return_vector;
}

static void parse(vector<string> input)
{
    if (input.empty())
        return;
    library *glibrary = library::instance();
    catalog *gcatalog = catalog::instance();
    // the first word is the command
    string command = input[0];

    if (command == "ar") {
        // add record
        string medium = input[1], title;
        for (auto it = input.begin() + 2; it != input.end(); ++it)
            title += *it + " ";
        // remove the last space
        title.pop_back();

        glibrary->add_record(medium, title);
    } else if (command == "ac") {
        // add collection to catalog
        string collection_name;
        for (auto it = input.begin() + 1; it != input.end(); ++it)
            collection_name += *it + " ";
        collection_name.pop_back();

        gcatalog->add_collection(collection_name);
    } else if (command == "pa") {
        // print allocations
        std::cout << str_mem_alloc << std::endl;
        glibrary->print_alloc();
        gcatalog->print_alloc();
    } else if (command == "pL") {
        // print library
        glibrary->print();
    } else if (command == "pr") {
        // print record id
        string record_id = input[1];
        glibrary->print_id(record_id);
    } else if (command == "pC") {
        // print catalog
        gcatalog->print();
    } else if (command == "fr") {
        // find and print record title
        string title;
        for (auto it = input.begin() + 1; it != input.end(); ++it)
            title += *it + " ";
        // remove the last space
        title.pop_back();

        glibrary->print_title(title);
    } else if (command == "mr") {
        // modify rating
        string id = input[1], rating = input[2];
        glibrary->modify_rating(id, rating);
    } else if (command == "dr") {
        // delete record with title
        string title;
        for (auto it = input.begin() + 1; it != input.end(); ++it)
            title += *it + " ";
        // remove the last space
        title.pop_back();
        glibrary->delete_record(title);
    } else if (command == "qq") {
        // quit
        cout << str_done << std::endl;
        exit(1);
    } else {
        cout << str_unhandled_command << std::endl;
    }
}

int main (void)
{
    while(1)
    {
        string user_input;
        cout << str_user_prompt;
        std::getline(std::cin, user_input);

        vector<string> parsed = split(user_input);

        parse(parsed);
    }
}
