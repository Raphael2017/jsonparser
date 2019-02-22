#include <iostream>
#include <time.h>
#include <string>
#include <assert.h>
#include <map>
#include "json.h"
#include <string.h>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

#include "cookie.h"
#include <math.h>
#include <stack>

#define LEFT(N) (2*(N)+1)
#define RIGHT(N) (2*(N)+2)

using namespace rapidjson;


std::string readFileContents(const std::string& file_path)
{
    std::ifstream t(file_path);
    std::string text((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return text;
}


const wchar_t* src = L"Driver=ODBC Driver 13 for SQL Server;Server=tcp:bard-dbc-executer.qapf1.qalab01.nextlabs.com,1433;Uid=sa;PWD=123blue!;Database=test01";
const char* src1 = "Driver=ODBC Driver 13 for SQL Server;Server=tcp:bard-dbc-executer.qapf1.qalab01.nextlabs.com,1433;Uid=sa;PWD=123blue!;Database=test01";

size_t size(const char* str) { return strlen(str); }
size_t size(const wchar_t* str) { return wcslen(str); }

template <typename T>
bool parse(const T* src)
{
    std::map<std::string, std::string> data{};
    int i = 0;
    std::string key = "";
    std::string value = "";
    int tks = 0;
    while (i < size(src))
    {
        if (src[i] == ';' || 0 == i)
        {
            // eat a key
            if (src[i] == ';')
            {
                ++i;
                if (i >= size(src)) break;
            }
            int pos1 = i;
            while (i < size(src) && (src[i] != '='))
                ++i;
            key = std::string(src + pos1, src + i);
            tks++;
        }
        else if (src[i] == '=')
        {
            // eat a value
            ++i;
            if (i >= size(src)) break;
            int pos1 = i;
            while (i < size(src) && src[i] != ';')
                ++i;
            value = std::string(src + pos1, src + i);
            if (tks != 1)
                return false;
            else
            {
                tks = 0;
                data[key] = value;
            }
        }
    }
    return 0 == tks;
}

int main1()
{
    parse(src1);
    parse(src);
    return 0;
}

int main2() {
    std::string sss = "{\n"
                      "   \"book\": [\n"
                      "\n"
                      "      {\n"
                      "         \"id\": \"01\",\n"
                      "         \"language\": \"Java\",\n"
                      "         \"edition\": \"third\",\n"
                      "         \"author\": \"Herbert Schildt\"\n"
                      "      },\n"
                      "\n"
                      "      {\n"
                      "         \"id\": \"07\",\n"
                      "         \"language\": \"C++\",\n"
                      "         \"edition\": \"second\",\n"
                      "         \"author\": \"E.Balagurusamy\"\n"
                      "      }\n"
                      "\n"
                      "   ]\n"
                      "}";

    sss = "{\"book\":[\"abc\",[1,2],3,{\"a\":[],\"b\":12,\"c\":[]}]}";
    sss = "{\n"
          "    \"Request\": {\n"
          "        \"Category\": [\n"
          "            {\n"
          "                \"Attribute\": [\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:host:inet_address\",\n"
          "                        \"DataType\": \"urn:oasis:names:tc:xacml:2.0:data-type:ipAddress\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"10.23.60.231\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:host:name\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"HostName\"\n"
          "                        ]\n"
          "                    }\n"
          "                ],\n"
          "                \"CategoryId\": \"urn:nextlabs:names:evalsvc:1.0:attribute-category:host\"\n"
          "            },\n"
          "            {\n"
          "                \"Attribute\": [\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:oasis:names:tc:xacml:1.0:subject:subject-id\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"S-1-5-21-310440588-250036847-580389505-500\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:oasis:names:tc:xacml:1.0:subject:name\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"nxl2rls@domain.com\"\n"
          "                        ]\n"
          "                    }\n"
          "                ],\n"
          "                \"CategoryId\": \"urn:oasis:names:tc:xacml:1.0:subject-category:access-subject\"\n"
          "            },\n"
          "            {\n"
          "                \"Attribute\": [\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:oasis:names:tc:xacml:1.0:resource:resource-id\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#anyURI\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"C:\\/Temp\\/SQLProxy.txt\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:resource:resource-type\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#anyURI\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"fso\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:resource:resource-dimension\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#anyURI\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"from\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:resource:sqlserver\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"sqltest002.database.windows.net\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:resource:database\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"CDCDB\"\n"
          "                        ]\n"
          "                    },\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:resource:table\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"Account02\"\n"
          "                        ]\n"
          "                    }\n"
          "                ],\n"
          "                \"CategoryId\": \"urn:oasis:names:tc:xacml:3.0:attribute-category:resource\"\n"
          "            },\n"
          "            {\n"
          "                \"Attribute\": [\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:oasis:names:tc:xacml:1.0:action:action-id\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"VIEW\"\n"
          "                        ]\n"
          "                    }\n"
          "                ],\n"
          "                \"CategoryId\": \"urn:oasis:names:tc:xacml:3.0:attribute-category:action\"\n"
          "            },\n"
          "            {\n"
          "                \"Attribute\": [\n"
          "                    {\n"
          "                        \"AttributeId\": \"urn:nextlabs:names:evalsvc:1.0:application:application-id\",\n"
          "                        \"DataType\": \"http:\\/\\/www.w3.org\\/2001\\/XMLSchema#string\",\n"
          "                        \"IncludeInResult\": \"false\",\n"
          "                        \"Value\": [\n"
          "                            \"SQLProxy\"\n"
          "                        ]\n"
          "                    }\n"
          "                ],\n"
          "                \"CategoryId\": \"urn:nextlabs:names:evalsvc:1.0:attribute-category:application\"\n"
          "            }\n"
          "        ],\n"
          "        \"ReturnPolicyIdList\": true\n"
          "    }\n"
          "}";

    sss = "{\n"
          "    \"name\": \"BeJson\",\n"
          "    \"url\": \"http://www.bejson.com\",\n"
          "    \"page\": 88,\n"
          "    \"isNonProfit\": true,\n"
          "    \"address\": {\n"
          "        \"street\": \"科技园路.\",\n"
          "        \"city\": \"江苏苏州\",\n"
          "        \"country\": \"中国\"\n"
          "    },\n"
          "    \"links\": [\n"
          "        {\n"
          "            \"name\": \"Google\",\n"
          "            \"url\": \"http://www.google.com\"\n"
          "        },\n"
          "        {\n"
          "            \"name\": \"Baidu\",\n"
          "            \"url\": \"http://www.baidu.com\"\n"
          "        },\n"
          "        {\n"
          "            \"name\": \"SoSo\",\n"
          "            \"url\": \"http://www.SoSo.com\"\n"
          "        }\n"
          "    ]\n"
          "}";

    json::Object obj;
    json::Buffer buffer;
    buffer.src_ = sss;
    obj.parse(&buffer);
    auto t = obj["Request"]->as_object()["Category"]->as_array()[2]->as_object()["Attribute"]->as_array()[0]->as_object()["Value"];
    return 0;
}

int main3()
{
    auto src = readFileContents("test.json");
    auto c = src.size();
    json::Object obj;
    json::Buffer buffer;
    buffer.src_ = src;
    obj.parse(&buffer);

    {
        json::Buffer w_buffer;
        json::Object obj1;
        obj.serialize(&w_buffer);
        printf("%s\n", w_buffer.src_.c_str());
        //obj1.parse(&w_buffer);

        int a = 1;
    }

    clock_t start, finish;
    double duration;
    {
        start = clock();
        size_t NN = 100;
        for (size_t i = 0; i < NN; ++i)
        {
            if (false)
            {
                json::Object obj;
                json::Buffer buffer;
                buffer.src_ = src;
                obj.parse(&buffer);
                buffer.src_ = "";
                //obj.serialize(&buffer);
            }
            else
            {
                Document d;
                d.Parse(src.c_str());
                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);
                std::cout << buffer.GetString() << std::endl;
            }

        }
        finish = clock();
        duration = (double)(finish - start) / 1000;
        printf( "JSON PARSE: %f ms\n", duration / NN );
    }

    return 0;
}

int main4()
{
    std::string src = "LSID=DQAAEaem_vYg; Path=/accounts; Expires=Wed, 13 Jan 2021 22:23:01 GMT; Secure; HttpOnly";
    cookie::Buffer buf;
    cookie::Cookie ck;
    buf.src_ = src;
    ck.parse(&buf);
    return 0;
}

void heap_adjust(int* src, size_t length, size_t root);

void heap_build(int* src, size_t length)
{
    for (int i = length / 2; i >= 0; --i)
    {
        heap_adjust(src, length, i);
    }
}

void heap_adjust(int* src, size_t length, size_t root)
{
    size_t cur = root;
    while (1)
    {
        size_t l = LEFT(cur);
        size_t r = RIGHT(cur);
        size_t largest = cur;
        if (l < length && src[l] > src[cur])
            largest = l;
        else
            largest = cur;
        if (r < length && src[r] > src[largest])
            largest = r;
        if (cur == largest)
            break;
        int tmp = src[cur];
        src[cur] = src[largest];
        src[largest] = tmp;
        cur = largest;
    }
}

void heap_sort(int* src, size_t length)
{
    heap_build(src, length);
    size_t heap_size = length;
    while (heap_size > 1)
    {
        heap_adjust(src, heap_size, 0);
        int tmp = src[0];
        src[0] = src[heap_size - 1];
        src[heap_size - 1] = tmp;
        heap_size--;
    }
}

int main32()
{
    int src[]{12,2,5,5,13,8,7,6,11};
    heap_sort(src, 9);
    heap_sort(src, 9);

    double f = 0.625;
    double ff = f;
    std::vector<int> ss;
    int CNT = 50;
    int i = 0;
    while (i < CNT)
    {
        f = f * 2;
        if (f >= 1)
        {
            ss.push_back(1);
            f = f - 1;
        }
        else
            ss.push_back(0);
        ++i;
    }

    double f1 = 0.0;
    for (size_t i = 0; i < ss.size(); ++i)
    {
        if (ss[i] > 0)
            f1 += 1.0 / (pow(2.0, i+1));
    }

    return 0;
}

struct Node
{
    bool is_number_;
    int data_;
};
float eval(const std::vector<Node*>& exp)
{
    assert(exp.size() == 7);
    std::stack<float> stack;
    for (size_t i = 0; i < exp.size(); ++i)
    {
        if (exp[i]->is_number_)
            stack.push(exp[i]->data_);
        else
        {
            auto n2 = stack.top();stack.pop();
            auto n1 = stack.top();stack.pop();
            switch (exp[i]->data_)
            {
                case 1:
                {
                    stack.push(n1+n2);
                }
                    break;
                case 2:
                {
                    stack.push(n1-n2);
                }
                    break;
                case 3:
                {
                    stack.push(n1*n2);
                }
                    break;
                case 4:
                {
                    stack.push(n1/n2);
                }
                    break;
                default:
                    assert(false);  /* unreachable */
            }
        }
    }
    assert(stack.size() == 1);
    return  stack.top();
}

void pp(const std::vector<Node*>& exp)
{
    for (auto it : exp)
    {
        if (it->is_number_)
            std::cout << it->data_;
        else
        {
            switch (it->data_)
            {
                case 1:
                {
                    std::cout << "+";
                }
                    break;
                case 2:
                {
                    std::cout << "-";
                }
                    break;
                case 3:
                {
                    std::cout << "*";
                }
                    break;
                case 4:
                {
                    std::cout << "/";
                }
                    break;
                default:
                    assert(false);  /* unreachable */
            }
        }
    }
    std::cout << std::endl;
}

int game(int* src, size_t len = 4)
{
    /* +-/* */
    std::vector<std::vector<int>> ss{
            {4,3,2,1},
            {4,3,1,2},
            {4,2,3,1},
            {4,2,1,3},
            {4,1,2,3},
            {4,1,3,2},

            {3,4,2,1},
            {2,4,1,2},
            {2,4,3,1},
            {2,4,1,3},
            {1,4,2,3},
            {1,4,3,2},

            {2,3,4,1},
            {1,3,4,2},
            {3,2,4,1},
            {1,2,4,3},
            {2,1,4,3},
            {3,1,4,2},

            {1,3,2,4},
            {2,3,1,4},
            {1,2,3,4},
            {3,2,1,4},
            {3,1,2,4},
            {2,1,3,4}
    };
    std::vector<std::vector<int>> oo{};
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
        {
            for (int k = 1; k <= 4; ++k)
            {
                oo.push_back({i,j,k});
            }
        }
    }

    int ret = 0;
    for (auto it1 : ss)
    {
        for (auto it2 : oo)
        {
            for (int i = 0; i < 5; ++i)
            {
                std::vector<Node*> exp;
                switch (i)
                {
                    case 0:
                    {
                        exp = {new Node{true, src[it1[0] - 1]},
                               new Node{true, src[it1[1] - 1]},
                               new Node{false, it2[0]},
                               new Node{true, src[it1[2] - 1]},
                               new Node{false, it2[1]},
                               new Node{true, src[it1[3] - 1]},
                               new Node{false, it2[2]}
                               };
                    }
                        break;
                    case 1:
                    {
                        exp = {new Node{true, src[it1[0] - 1]},
                               new Node{true, src[it1[1] - 1]},
                               new Node{false, it2[0]},
                               new Node{true, src[it1[2] - 1]},
                               new Node{true, src[it1[3] - 1]},
                               new Node{false, it2[1]},
                               new Node{false, it2[2]}
                              };
                    }
                        break;
                    case 2:
                    {
                        exp = {new Node{true, src[it1[0] - 1]},
                               new Node{true, src[it1[1] - 1]},
                               new Node{true, src[it1[2] - 1]},
                               new Node{false, it2[0]},
                               new Node{true, src[it1[3] - 1]},
                               new Node{false, it2[1]},
                               new Node{false, it2[2]}
                              };
                    }
                        break;
                    case 3:
                    {
                        exp = {new Node{true, src[it1[0] - 1]},
                               new Node{true, src[it1[1] - 1]},
                               new Node{true, src[it1[2] - 1]},
                               new Node{false, it2[0]},
                               new Node{false, it2[1]},
                               new Node{true, src[it1[3] - 1]},
                               new Node{false, it2[2]}
                        };
                    }
                        break;
                    case 4:
                    {
                        exp = {new Node{true, src[it1[0] - 1]},
                               new Node{true, src[it1[1] - 1]},
                               new Node{true, src[it1[2] - 1]},
                               new Node{true, src[it1[3] - 1]},
                               new Node{false, it2[0]},
                               new Node{false, it2[1]},
                               new Node{false, it2[2]}
                        };
                    }
                        break;
                    default:
                        assert(false);
                }
                if (eval(exp) == 24)
                {
                    pp(exp);
                    ret++;
                }
            }
        }
    }
    return ret;
}

int main()
{
    clock_t start = clock(), finish;
    int src[]{12,12,13,13};
    int ret = game(src);
    eval(std::vector<Node*>{new Node{true, 2},
                            new Node{true, 1},
                            new Node{false, 4},
                            new Node{true, 3},
                            new Node{false, 4},
                            new Node{true, 4},
                            new Node{false, 3}
    });
    std::cout << "total: " << ret << std::endl;
    finish = clock();
    auto duration = (double)(finish - start) / 1000;
    printf( "haha: %f ms\n", duration );
    return 0;
}