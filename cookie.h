#ifndef COOKIE_H
#define COOKIE_H

#include <map>
#include <string>
#include <list>
namespace cookie
{
    struct Buffer;
    struct Node
    {
        virtual int parse(Buffer* buf) = 0;
        virtual void serialize(Buffer* buf) = 0;
    };
    struct AvPair;
    struct Cookie : public Node
    {
        std::list<AvPair*> data_;
        virtual int parse(Buffer* buf) override;
        virtual void serialize(Buffer* buf) override;
    };

    struct AvPair : public Node
    {
        std::pair<std::string, std::string> data_;
        bool no_value{false};
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
            while (src_[pos_] == '\t' || src_[pos_] == '\n' || src_[pos_] == '\r')
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
        inline bool cur_is_token()
        {
            char c = src_[pos_];
            return (c >= '0' && c <= '9') ||
                    (c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z') ||
                    (c == '-' || c == ' ' || c == '/' || c == '_' || c == ':' || c == ',');
        }
        // for write
        inline void write(const std::string& s) { src_+= s; }

    private:
        size_t pos_{ 0 };
    };
}


#endif