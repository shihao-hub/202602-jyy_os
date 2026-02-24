// RapidJSON 示例 - 高性能的 C++ JSON 库
// 优点: 内存占用小，解析速度快，支持原位解析

#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "fstream"

using namespace rapidjson;

int main() {
    // 1. 创建 JSON 文档
    Document d;
    d.SetObject();

    // 2. 添加数据 - 使用 Allocator
    Document::AllocatorType& allocator = d.GetAllocator();

    d.AddMember("name", "rapidjson_demo", allocator);
    d.AddMember("version", "1.0.0", allocator);
    d.AddMember("speed", "ultra fast", allocator);

    // 3. 添加数组
    Value features(kArrayType);
    features.PushBack("high_performance", allocator);
    features.PushBack("low_memory", allocator);
    features.PushBack("in_situ_parsing", allocator);
    d.AddMember("features", features, allocator);

    // 4. 添加嵌套对象
    Value settings(kObjectType);
    settings.AddMember("optimize", "speed", allocator);
    settings.AddMember("inline", true, allocator);
    d.AddMember("settings", settings, allocator);

    // 5. 序列化为字符串 (格式化输出)
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    d.Accept(writer);

    std::cout << "=== 序列化结果 ===" << std::endl;
    std::cout << buffer.GetString() << std::endl;

    // 6. 写入文件
    std::ofstream out("build/rapid_config.json");
    out << buffer.GetString();
    out.close();
    std::cout << "\n已写入 build/rapid_config.json" << std::endl;

    // 7. 解析 JSON 字符串
    const char* json_str = R"({"user": "bob", "level": 42, "active": true})";

    Document parsed;
    parsed.Parse(json_str);

    if (parsed.HasParseError()) {
        std::cerr << "解析错误!" << std::endl;
        return 1;
    }

    std::cout << "\n=== 解析结果 ===" << std::endl;

    // 8. 访问数据 - 支持多种方式
    if (parsed.IsObject()) {
        // 方法1: 使用 operator[]
        std::cout << "User: " << parsed["user"].GetString() << std::endl;
        std::cout << "Level: " << parsed["level"].GetInt() << std::endl;
        std::cout << "Active: " << (parsed["active"].GetBool() ? "true" : "false") << std::endl;

        // 方法2: 使用 FindMember() 更安全
        auto member = parsed.FindMember("user");
        if (member != parsed.MemberEnd()) {
            std::cout << "Found user: " << member->value.GetString() << std::endl;
        }
    }

    // 9. 原位解析 (in-situ) - 更快，但会修改原字符串
    char buffer2[256];
    strcpy(buffer2, R"({"score": 100, "combo": 5})");
    Document inSituDoc;
    inSituDoc.ParseInsitu(buffer2);

    std::cout << "\n=== 原位解析结果 ===" << std::endl;
    std::cout << "Score: " << inSituDoc["score"].GetInt() << std::endl;
    std::cout << "Combo: " << inSituDoc["combo"].GetInt() << std::endl;

    return 0;
}
