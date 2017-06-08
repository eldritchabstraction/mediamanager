#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>

class record
{
public:
    record(std::string medium, std::string title, int id):
        title_(title), medium_(medium), rating_("u"), id_(id) {};

    void print (void) { std::cout << id_ << ": " << medium_ << " " << rating_
                                  << " " << title_ << std::endl; }

    friend std::ostream& operator<<(std::ostream &stream, record &r)
    {
        stream << r.id() << ": " << r.medium() << " " << r.rating() << " " << r.title();
        return stream;
    }

    std::string title(void) { return title_; }
    std::string medium(void) { return medium_; }
    std::string rating(void) { return rating_; }
    void set_rating(std::string rating) { rating_ = std::string(rating); }
    int id(void) { return id_; }

private:
    std::string title_;
    std::string medium_;
    std::string rating_;
    int id_;
};

#endif
