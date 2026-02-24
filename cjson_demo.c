// cJSON 示例 - 轻量级 C 语言 JSON 库
// 优点: 单文件头文件，纯 C 实现，易嵌入，MIT 许可

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

int main() {
    // 1. 创建 JSON 对象
    cJSON *root = cJSON_CreateObject();

    // 2. 添加基本数据
    cJSON_AddStringToObject(root, "name", "cjson_demo");
    cJSON_AddStringToObject(root, "lang", "C");
    cJSON_AddNumberToObject(root, "version", 1.0);
    cJSON_AddBoolToObject(root, "lightweight", true);

    // 3. 添加数组
    cJSON *features = cJSON_CreateArray();
    cJSON_AddItemToArray(features, cJSON_CreateString("single_header"));
    cJSON_AddItemToArray(features, cJSON_CreateString("pure_c"));
    cJSON_AddItemToArray(features, cJSON_CreateString("easy_embed"));
    cJSON_AddItemToObject(root, "features", features);

    // 4. 添加嵌套对象
    cJSON *config = cJSON_CreateObject();
    cJSON_AddNumberToObject(config, "max_items", 100);
    cJSON_AddBoolToObject(config, "debug", false);
    cJSON_AddItemToObject(root, "config", config);

    // 5. 格式化输出 JSON
    char *json_str = cJSON_Print(root);
    printf("=== 序列化结果 ===\n%s\n", json_str);

    // 6. 写入文件
    FILE *fp = fopen("build/cjson_config.json", "w");
    if (fp) {
        fputs(json_str, fp);
        fclose(fp);
        printf("\n已写入 build/cjson_config.json\n");
    }

    free(json_str);

    // 7. 解析 JSON 字符串
    const char *parse_str = "{\"user\": \"charlie\", \"score\": 9999, \"items\": [\"sword\", \"shield\"]}";
    cJSON *parsed = cJSON_Parse(parse_str);

    if (parsed == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "解析错误: %s\n", error_ptr);
        }
        cJSON_Delete(root);
        return 1;
    }

    printf("\n=== 解析结果 ===\n");

    // 8. 获取数据
    cJSON *user = cJSON_GetObjectItem(parsed, "user");
    if (user && cJSON_IsString(user)) {
        printf("User: %s\n", user->valuestring);
    }

    cJSON *score = cJSON_GetObjectItem(parsed, "score");
    if (score && cJSON_IsNumber(score)) {
        printf("Score: %d\n", score->valueint);
    }

    // 9. 遍历数组
    cJSON *items = cJSON_GetObjectItem(parsed, "items");
    if (items && cJSON_IsArray(items)) {
        printf("Items: ");
        cJSON *item = NULL;
        cJSON_ArrayForEach(item, items) {
            printf("%s ", item->valuestring);
        }
        printf("\n");
    }

    // 10. 清理内存 - 重要！
    cJSON_Delete(parsed);
    cJSON_Delete(root);

    // 11. 实用函数演示
    printf("\n=== 实用函数 ===\n");

    // 创建嵌套结构的快捷方式
    cJSON *game = cJSON_Parse("{\"hp\": 100, \"mp\": 50}");
    int hp = cJSON_GetObjectItem(game, "hp")->valueint;
    int mp = cJSON_GetObjectItem(game, "mp")->valueint;
    printf("HP: %d, MP: %d\n", hp, mp);

    // 替换/更新值
    cJSON_ReplaceItemInObject(game, "hp", cJSON_CreateNumber(80));
    printf("After heal: HP = %d\n", cJSON_GetObjectItem(game, "hp")->valueint);

    cJSON_Delete(game);

    return 0;
}
