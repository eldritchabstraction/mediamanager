/*
 * This project is from:
 * http://www.umich.edu/~eecs381/proj0/
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <iterator>

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

static string construct_title(vector<string> &input, vector<string>::iterator &it)
{
    string title;
    for (; it != input.end(); ++it)
        title += *it + " ";
    // remove the last space
    title.pop_back();

    return title;
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
        string medium = input[1];
        vector<string>::iterator it = input.begin() + 2;
        string title = construct_title(input, it);
        glibrary->add_record(medium, title);
    } else if (command == "ac") {
        // add collection to catalog
        string collection_name = input[1];

        gcatalog->add_collection(collection_name);
    } else if (command == "am") {
        // add record id to collection
        string collection_name = input[1];
        string record_id = input[2];
        gcatalog->add_member(collection_name, record_id);
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
    } else if (command == "pc") {
        // print collection
        string collection_name = input[1];
        gcatalog->print_collection(collection_name);
    } else if (command == "fr") {
        // find and print record title
        string title = construct_title(input, ++input.begin());
        glibrary->print_title(title);
    } else if (command == "mr") {
        // modify rating
        string id = input[1], rating = input[2];
        glibrary->modify_rating(id, rating);
    } else if (command == "dr") {
        // delete record with title
        string title = construct_title(input, ++input.begin());
        glibrary->delete_record(title);
    } else if (command == "sA") {
        // save all
        string save_filename = input[1];
        std::ofstream save;

        save.open(save_filename);
        save << glibrary->records_count() << std::endl;
        glibrary->print_save(save);

        save << gcatalog->collection_count() << std::endl;
        gcatalog->print_save(save);

        save.close();
        cout << "Data saved\n";
    } else if (command == "rA") {
        // restore all
        string save_filename = input[1];
        std::ifstream save;

        save.open(save_filename);
        string line;
        std::vector<string> lines;
        while (std::getline(save, line))
            lines.push_back(line);

        std::vector<string>::iterator it = lines.begin();
        // the first line is the records count
        int records_count = std::stoi(*it, nullptr, 10);
        // iterate over the records
        for (int i = 0; i < records_count; i++)
        {
            // reusing the variable line declared above
            vector<string> line = split(*(++it));
            // iterate through the words in line
            std::vector<string>::iterator jt = line.begin();
            string record_id = *jt;
            record_id.pop_back();
            string medium = *(++jt);
            string rating = *(++jt);
            string title = construct_title(line, ++jt);

            glibrary->add_record(medium, title);
            if (rating != "u")
                glibrary->modify_rating(record_id, rating);
        }
        // this line is the collections count
        int collections_count = std::stoi(*(++it), nullptr, 10);
        // iterate over the collections
        for (int i = 0; i < collections_count; ++i)
        {
            // reusing the variable line declared above
            vector<string> line = split(*(++it));
            string collection_name = line[0];
            int members_count = std::stoi(line[1], nullptr, 10);

            gcatalog->add_collection(collection_name);
            // iterate over the members
            for (int j = 0; j < members_count; ++j)
            {
                int record_id = glibrary->find_record_by_title(*++it)->id();
                gcatalog->add_member(collection_name, std::to_string(record_id));
            }
        }

        cout << "Data loaded\n";

        save.close();
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
