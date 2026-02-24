// nlohmann/json 示例 - 极简易用的现代 C++ JSON 库
// 优点: 语法优美，API 直观，类似 STL 风格

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

int main() {
    // 1. 创建 JSON 对象 - 超级简单
    json j = {
        {"name", "jyy_os"},
        {"version", "1.0.0"},
        {"features", {"fast", "simple", "modern"}},
        {"settings", {
            {"debug", true},
            {"port", 8080}
        }}
    };

    // 2. 添加数据
    j["author"] = "Claude";
    j["stars"] = 9999;

    // 3. 序列化为字符串
    std::string dump = j.dump(4);  // 缩进4个空格
    std::cout << "=== 序列化结果 ===" << std::endl;
    std::cout << dump << std::endl;

    // 4. 写入文件
    std::ofstream out("build/config.json");
    out << j.dump(4);
    out.close();
    std::cout << "\n已写入 build/config.json" << std::endl;

    // 5. 解析 JSON 字符串
    std::string json_str = R"({"user": "alice", "score": 100})";
    json parsed = json::parse(json_str);

    std::cout << "\n=== 解析结果 ===" << std::endl;
    std::cout << "User: " << parsed["user"] << std::endl;
    std::cout << "Score: " << parsed["score"] << std::endl;

    // 6. 类型检查
    if (parsed.contains("user") && parsed["user"].is_string()) {
        std::cout << "user 是字符串" << std::endl;
    }

    // 7. 遍历数组
    std::cout << "\n=== 遍历数组 ===" << std::endl;
    json nums = {1, 2, 3, 4, 5};
    for (auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
