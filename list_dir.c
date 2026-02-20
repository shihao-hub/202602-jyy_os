#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH 1024

// 颜色代码
#define COLOR_RESET   "\033[0m"
#define COLOR_DIR     "\033[1;34m"  // 蓝色加粗
#define COLOR_EXEC    "\033[1;32m"  // 绿色加粗
#define COLOR_LINK    "\033[1;36m"  // 青色加粗
#define COLOR_HIDDEN  "\033[1;90m"  // 灰色加粗

// 文件类型颜色
const char *get_color(mode_t mode, const char *name) {
    if (name[0] == '.') return COLOR_HIDDEN;
    if (S_ISDIR(mode)) return COLOR_DIR;
    if (S_ISLNK(mode)) return COLOR_LINK;
    if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) return COLOR_EXEC;
    return COLOR_RESET;
}

// 递归列出目录
void list_directory(const char *path, int depth, int max_depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char full_path[MAX_PATH];

    // 检查深度限制
    if (depth > max_depth) {
        return;
    }

    // 打开目录
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    // 遍历目录项
    while ((entry = readdir(dir)) != NULL) {
        // 跳过 . 和 ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // 构建完整路径
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // 获取文件状态
        if (lstat(full_path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        // 打印缩进
        for (int i = 0; i < depth; i++) {
            printf("│   ");
        }

        // 打印文件名（带颜色）
        const char *color = get_color(statbuf.st_mode, entry->d_name);
        const char *prefix = S_ISDIR(statbuf.st_mode) ? "├── " : "├── ";
        const char *type = S_ISDIR(statbuf.st_mode) ? "/" :
                          S_ISLNK(statbuf.st_mode) ? "@" : "";

        printf("%s%s%s%s%s\n", prefix, color, entry->d_name, type, COLOR_RESET);

        // 如果是目录，递归遍历
        if (S_ISDIR(statbuf.st_mode)) {
            list_directory(full_path, depth + 1, max_depth);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = ".";
    int max_depth = 2;  // 默认深度

    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("用法: %s [目录] [-d 深度]\n", argv[0]);
            printf("示例:\n");
            printf("  %s              # 列出当前目录，深度2\n", argv[0]);
            printf("  %s /tmp         # 列出 /tmp 目录\n", argv[0]);
            printf("  %s -d 3         # 深度设为3\n", argv[0]);
            printf("  %s /tmp -d 1    # 列出 /tmp，深度1\n", argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            max_depth = atoi(argv[++i]);
        } else if (argv[i][0] != '-') {
            path = argv[i];
        }
    }

    // 检查路径是否存在
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        fprintf(stderr, "错误: 无法访问 '%s': ", path);
        perror(NULL);
        return 1;
    }

    if (!S_ISDIR(statbuf.st_mode)) {
        fprintf(stderr, "错误: '%s' 不是一个目录\n", path);
        return 1;
    }

    // 打印目录结构
    printf("%s\n", path);
    list_directory(path, 0, max_depth);

    return 0;
}
