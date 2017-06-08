#ifndef STRINGS_H
#define STRINGS_H
/* Notes:
1. Study the samples to see instances of these strings in use.

2. Two or more strings on the same line would be part of the same
line of output, with some variable value(s) output between them.

*/

#include <string>

using std::string;

/* top level messages */
const string str_user_prompt = "\nEnter command: ";
const string str_done = "Done";

/* print command messages */

/* library */
const string str_lib_empty = "Library is empty";

/* catalog */
const string str_cat_empty = "Catalog is empty";

const string str_mem_alloc = "Memory allocations:";
const string str_records = "Records: ";
const string str_collections = "Collections: ";

/* Record output */
// ": " " u "  /* used when rating is zero */
// ": "       /* used when rating is non-zero */

/* add/modify/delete/save/restore command messages */
// "Member " " added"
//"Record " " deleted"
//"Collection " " deleted"
//"Member " " deleted"
const string str_coll_deleted = "All collections deleted";
const string str_record_deleted = "All records deleted";
const string str_data_deleted = "All data deleted";

/* command error messages */
const string str_unhandled_command = "Unrecognized command!";
const string str_lib_dupe = "Library already has a record with this title!";
const string str_coll_dupe = "Catalog already has a collection with this name!";
//"Record is already a member in the collection!"
//"Record is not a member in the collection!"
//"Cannot delete a record that is a member of a collection!"
//"Cannot clear all records unless all collections are empty!"
const string str_record_title_not_exist = "No record with that title!";
const string str_record_id_not_exist = "No record with that ID!";
const string str_coll_not_exist = "No collection with that name!";
//"Could not read a title!"
//"Could not read an integer value!"
const string str_rating_oob = "Rating is out of range!";
//"Could not open file!"
//"Invalid data found in file!"
#endif
