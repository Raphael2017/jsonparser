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

int main()
{
    std::string src = "LSID=DQAAEaem_vYg; Path=/accounts; Expires=Wed, 13 Jan 2021 22:23:01 GMT; Secure; HttpOnly";
    cookie::Buffer buf;
    cookie::Cookie ck;
    buf.src_ = src;
    ck.parse(&buf);
    return 0;
}