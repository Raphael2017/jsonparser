#include "json.h"
#include <assert.h>

namespace json
{
    int Key::parse(Buffer* buf)
    {
        buf->skip_white();
        if (buf->is_end())
            return -1;
        assert(buf->current() == '"');
        buf->next();
        size_t pos_s = buf->pos();
        while (!buf->is_end() && buf->current() != '"')
            buf->next();
        if (buf->current() != '"')
            return -1;
        data_ = buf->range(pos_s, buf->pos());
        buf->next();
        return 0;
    }

    void Key::serialize(Buffer* buf)
    {

    }

    int Value::parse(Buffer* buf)
    {
        buf->skip_white();
        if (buf->is_end())
            return -1;
        switch (type_)
        {
            case E_STRING:
            {
                assert(buf->current() == '"');
                buf->next();
                size_t pos_s = buf->pos();
                while (!buf->is_end() && buf->current() != '"')
                    buf->next();
                if (buf->current() != '"')
                    return -1;
                str_ = buf->range(pos_s, buf->pos());
                buf->next();
                return 0;
            }
                break;
            case E_INTERGER:
            {
                assert(buf->cur_is_digit());
                size_t pos_s = buf->pos();
                while (!buf->is_end() && buf->cur_is_digit())
                    buf->next();
                std::string N = buf->range(pos_s, buf->pos());
                i_ = atoi(N.c_str());
                return 0;
            }
                break;
            default:
                assert(false);  /* unreachable */
        }
        return 0;
    }

    void Value::serialize(Buffer* buf)
    {

    }

    int Object::parse(Buffer* buf)
    {
        buf->skip_white();
        assert(buf->current() == '{');
        buf->next();
        while (true)
        {
            if (buf->current() != '}')
            {
                if (-1 == parse_member(buf, this))
                    return -1;
            }
            switch (buf->current())
            {
                case ',' :
                {
                    buf->next();
                }
                    break;
                case '{' :
                {
                    Object* obj = new Object;
                    if (-1 == obj->parse(buf))
                        return -1;
                }
                    break;
                case '[' :
                {
                    Array* arr = new Array;
                    arr->parse(buf);
                }
                    break;
                case '}' :
                {
                    buf->next();
                    return 0;
                }
                    break;
                default:
                    assert(false);
            }

        }
    }

    void Object::serialize(Buffer* buf)
    {

    }

    int Array::parse(Buffer* buf)
    {
        buf->skip_white();
        assert(buf->current() == '[');
        buf->next();
        while (true)
        {
            if (buf->current() != ']')
            {
                Node* node = nullptr;
                if (-1 == parse_value(buf, node))
                    return -1;
                else
                    this->data_.push_back(node);
            }
            switch (buf->current())
            {
                case ',' :
                {
                    buf->next();
                }
                    break;
                case '{' :
                {
                    Object* obj = new Object;
                    if (-1 == obj->parse(buf))
                        return -1;
                }
                    break;
                case '[' :
                {
                    Array* arr = new Array;
                    arr->parse(buf);
                }
                    break;
                case ']' :
                {
                    buf->next();
                    return 0;
                }
                    break;
                default:
                    assert(false);
            }
        }
    }

    void Array::serialize(Buffer* buf)
    {

    }

    int parse_member(Buffer* buf, Object* obj)
    {
        buf->skip_white();
        auto c = buf->current();
        assert(buf->current() == '"');
        Key key;
        key.parse(buf);
        buf->skip_white();
        assert(buf->current() == ':');
        buf->next();
        buf->skip_white();
        Node* node = nullptr;
        parse_value(buf, node);
        obj->data_[key.data_] = node;
        buf->skip_white();
    }

    int parse_value(Buffer* buf, Node*& node)
    {
        buf->skip_white();
        switch (buf->current())
        {
            case '"':
            {
                Value* v = new Value;
                v->type_ = Value::E_STRING;
                v->parse(buf);
                node = v;
            }
                break;
            case '[':
            {
                Array* ar = new Array;
                ar->parse(buf);
                node = ar;
            }
                break;
            case '{':
            {
                Object* obj = new Object;
                obj->parse(buf);
                node = obj;
            }
                break;
            default:
            {
                Value* v = new Value;
                v->type_ = Value::E_INTERGER;
                v->parse(buf);
                node = v;
            }
        }
        buf->skip_white();
        return 0;
    }
}