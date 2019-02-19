#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <vector>

namespace json
{
    struct Buffer;
    struct Node
    {
        virtual int parse(Buffer* buf) = 0;
        virtual void serialize(Buffer* buf) = 0;
    };
    struct Key : public Node
    {
        std::string data_;
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };
    struct Value : public Node
    {
        enum ValueType
        {
            E_STRING,
            E_INTERGER
        };
        ValueType type_;
        int i_;
        std::string str_;
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };
    struct Object : public Node
    {
        std::map<std::string, Node*> data_;
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };
    struct Array : public Node
    {
        std::vector<Node*> data_;
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };

    struct Buffer
    {
        std::string src_;
        size_t pos_{ 0 };
        bool next() { pos_++; return true; }
        char current() { return src_[pos_]; }
        char peek();
        bool is_end() { return pos_ >= src_.length(); }
        bool skip_white()
        {
            while (src_[pos_] == ' ' || src_[pos_] == '\t' || src_[pos_] == '\n' || src_[pos_] == '\r')
                pos_++;
        }
        size_t pos() { return pos_; }
        std::string range(size_t start, size_t end) { return src_.substr(start, end - start); }
        bool cur_is_digit() { return current() >= '0' && current() <= '9'; }
    };

    int parse_member(Buffer* buf, Object* obj);
    int parse_value(Buffer* buf, Node*& node);
}

#endif