#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <vector>
#include <list>

#define UNIQUE_KEY1

namespace json
{
    struct Buffer;
    struct Value;
    struct Object;
    struct Array;
    struct Node
    {
        Value& as_value();
        Object& as_object();
        Array& as_array();
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
            E_INTERGER,
            E_BOOLEAN,
            E_NULL,
        };
        ValueType type_;
        long i_;
        bool boolean_;
        std::string str_;
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };
    struct Object : public Node
    {
#ifdef UNIQUE_KEY
        std::map<std::string, Node*> data_;
#else
        std::list<std::pair<std::string, Node*>> data_;
#endif
        Node* operator[](const std::string& key);
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };

    struct Array : public Node
    {
        std::vector<Node*> data_;
        size_t size() { return data_.size(); }
        Node* operator[](size_t index);
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };

    struct Buffer
    {
        std::string src_;
        size_t line_{0};
        size_t column_{0};
        inline bool next() { pos_++; column_++; return true; }
        inline char current() { return src_[pos_]; }
        inline bool is_end() { return pos_ >= src_.length(); }
        inline bool skip_white()
        {
            while (src_[pos_] == ' ' || src_[pos_] == '\t' || src_[pos_] == '\n' || src_[pos_] == '\r')
            {
                if ('\n' == src_[pos_])
                {
                    line_++;
                    column_ = 0;
                }
                else
                {
                    column_++;
                }
                pos_++;
            }

        }
        inline size_t pos() { return pos_; }
        inline std::string range(size_t start, size_t end) { return src_.substr(start, end - start); }
        inline bool cur_is_digit() { return current() >= '0' && current() <= '9'; }

        // for write
        inline void write(const std::string& s) { src_+= s; }

    private:
        size_t pos_{ 0 };
    };

    int parse_member(Buffer* buf, Object* obj);
    int parse_value(Buffer* buf, Node*& node);
}

#endif