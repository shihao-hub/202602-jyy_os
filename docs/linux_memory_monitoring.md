# Linux 服务内存状态查看方法

## 基本命令

```bash
# 1. top - 实时查看所有进程内存
top

# 2. htop - 更友好的交互式界面（需要安装）
htop

# 3. ps - 查看特定进程
ps aux | grep <服务名>
ps -o pid,ppid,cmd,%mem,%mem -C <进程名>

# 4. 直接查看 /proc 文件系统
cat /proc/<pid>/status
cat /proc/<pid>/statm

# 5. pmap - 查看进程内存映射
pmap <pid>

# 6. 查看系统整体内存
free -h
cat /proc/meminfo
```

## 常用组合示例

```bash
# 查看 nginx 服务内存
ps aux | grep nginx | awk '{print $2, $4, $11}'

# 按内存排序显示前10个进程
ps aux --sort=-%mem | head -10

# 实时监控特定进程
top -p <pid>

# 查看详细内存信息（含 VmRSS, VmSize 等）
cat /proc/$(pidof <服务名>)/status | grep -i vm
```

## 关键指标说明

| 指标 | 说明 |
|------|------|
| **VSZ/VmSize** | 虚拟内存大小（包含共享库、未使用的内存） |
| **RSS/VmRSS** | 实际物理内存使用（常驻内存） |
| **%MEM** | 占总内存的百分比 |
| **SHR** | 共享内存大小 |

## 推荐工具

- 日常监控：`htop` 或 `ps aux --sort=-%mem`
- 详细分析：`/proc/<pid>/status` 或 `pmap`
- 快速查看：`free -h`
