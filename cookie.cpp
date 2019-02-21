#include "cookie.h"
#include <assert.h>
namespace cookie
{
    int Cookie::parse(Buffer* buf)
    {
        buf->skip_white();
        AvPair* pair = new AvPair;
        pair->parse(buf);
        data_.push_back(pair);

        buf->skip_white();
        while (buf->current() == ';')
        {
            buf->next();
            buf->skip_white();
            AvPair* pair = new AvPair;
            pair->parse(buf);
            data_.push_back(pair);
        }
    }

    void Cookie::serialize(Buffer* buf)
    {

    }

    int AvPair::parse(Buffer* buf)
    {
        buf->skip_white();
        auto pos_s = buf->pos();
        while (!buf->is_end() && buf->cur_is_token())
            buf->next();
        std::string token = buf->range(pos_s, buf->pos());
        buf->skip_white();
        if (buf->current() == '=')
        {
            buf->next();
            buf->skip_white();
            assert(buf->current() == '"' || buf->cur_is_token());
            if (buf->current() == '"')
            {
                buf->next();
                auto pos_s = buf->pos();
                while (!buf->is_end() && (buf->current() != '\n' && buf->current() != '"'))
                    buf->next();
                assert(buf->current() == '"');
                std::string v = buf->range(pos_s, buf->pos());
                data_.first = token;
                data_.second = "\"" + v + "\"";
                buf->next();
            }
            else
            {
                assert(buf->cur_is_token());
                auto pos_s = buf->pos();
                while (!buf->is_end() && buf->cur_is_token())
                    buf->next();
                std::string v = buf->range(pos_s, buf->pos());
                data_.first = token;
                data_.second = v;
            }
            no_value = false;
        }
        else
        {
            data_.first = token;
            no_value = true;
        }
        buf->skip_white();
    }

    void AvPair::serialize(Buffer* buf)
    {

    }
}