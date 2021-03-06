#include "json.h"
#include <assert.h>

namespace json
{
    Value& Node::as_value()
    {
        return *dynamic_cast<Value*>(this);
    }

    Object& Node::as_object()
    {
        return *dynamic_cast<Object*>(this);
    }

    Array& Node::as_array()
    {
        return *dynamic_cast<Array*>(this);
    }


    int Key::parse(Buffer* buf)
    {
        buf->skip_white();
        if (buf->is_end())
            return -1;
        assert(buf->current() == '"');
        buf->next();
        size_t pos_s = buf->pos();
        while (!buf->is_end() && buf->current() != '"')
        {
            if (buf->current() == '\\')
            {
                buf->next();
                buf->next();
            }
            else
                buf->next();
        }

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
                {
                    if (buf->current() == '\\')
                    {
                        buf->next();
                        buf->next();
                    }
                    else
                        buf->next();
                }
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
                i_ = atol(N.c_str());
                return 0;
            }
                break;
            case E_BOOLEAN:
            {
                assert(buf->current() == 't' || buf->current() == 'f');
                if (buf->current() == 't')
                {
                    buf->next();
                    if (buf->is_end() || buf->current() != 'r')
                        return -1;
                    buf->next();
                    if (buf->is_end() || buf->current() != 'u')
                        return -1;
                    buf->next();
                    if (buf->is_end() || buf->current() != 'e')
                        return -1;
                    boolean_ = true;
                    buf->next();
                }
                else if (buf->current() == 'f')
                {
                    buf->next();
                    if (buf->is_end() || buf->current() != 'a')
                        return -1;
                    buf->next();
                    if (buf->is_end() || buf->current() != 'l')
                        return -1;
                    buf->next();
                    if (buf->is_end() || buf->current() != 's')
                        return -1;
                    buf->next();
                    if (buf->is_end() || buf->current() != 'e')
                        return -1;
                    boolean_ = false;
                    buf->next();
                }
                else
                {
                    return -1;
                }
            }
                break;
            case E_NULL:
            {
                assert(buf->current() == 'n');
                buf->next();
                if (buf->is_end() || buf->current() != 'u')
                    return -1;
                buf->next();
                if (buf->is_end() || buf->current() != 'l')
                    return -1;
                buf->next();
                if (buf->is_end() || buf->current() != 'l')
                    return -1;
                buf->next();
            }
                break;
            default:
                assert(false);  /* unreachable */
        }
        return 0;
    }

    void Value::serialize(Buffer* buf)
    {
        switch (type_)
        {
            case E_STRING:
            {
                buf->write("\"");
                buf->write(str_);
                buf->write("\"");
            }
                break;
            case E_INTERGER:
            {
                buf->write(std::to_string(i_));
            }
                break;
            case E_BOOLEAN:
            {
                if (boolean_)
                    buf->write("true");
                else
                    buf->write("false");
            }
                break;
            case E_NULL:
            {
                buf->write("null");
            }
                break;
            default:
                assert(false);  /* unreachable */
        }
    }

    Node* Object::operator[](const std::string& key)
    {
#ifdef UNIQUE_KEY
        auto fd = data_.find(key);
        if (fd != data_.end())
            return fd->second;
        else
            return nullptr;
#else
        return nullptr;
#endif
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
                {
                    auto c = buf->current();
                    assert(false);
                }

            }

        }
    }

    void Object::serialize(Buffer* buf)
    {
        buf->write("{");
        auto it = data_.begin();
        if (it != data_.end())
        {
            buf->write("\"");
            buf->write(it->first);
            buf->write("\":");
            it->second->serialize(buf);
        }
        for (; it != data_.end(); ++it)
        {
            buf->write(",\"");
            buf->write(it->first);
            buf->write("\":");
            it->second->serialize(buf);
        }
        buf->write("}");
    }

    Node* Array::operator[](size_t index)
    {
        if (index >= 0 && index < data_.size())
            return data_[index];
        else
            return nullptr;
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
        buf->write("[");
        auto it = data_.begin();
        if (it != data_.end())
        {
            (*it)->serialize(buf);
        }
        for (; it != data_.end(); ++it)
        {
            buf->write(",");
            (*it)->serialize(buf);
        }
        buf->write("]");
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
#ifdef UNIQUE_KEY
        obj->data_[key.data_] = node;
#else
        obj->data_.push_back(std::make_pair(key.data_, node));
#endif
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
            case 'n':
            {
                Value* v = new Value;
                v->type_ = Value::E_NULL;
                v->parse(buf);
                node = v;
            }
                break;
            case 't':
            {
                Value* v = new Value;
                v->type_ = Value::E_BOOLEAN;
                v->parse(buf);
                node = v;
            }
                break;
            case 'f':
            {
                Value* v = new Value;
                v->type_ = Value::E_BOOLEAN;
                v->parse(buf);
                node = v;
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