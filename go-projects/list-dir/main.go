package main

import (
	"flag"
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"strings"
)

func main() {
	var maxDepth int
	flag.IntVar(&maxDepth, "depth", -1, "maximum recursion depth (-1 for unlimited)")
	flag.Parse()

	if flag.NArg() < 1 {
		fmt.Println("Usage: list-dir [-depth N] <directory>")
		os.Exit(1)
	}

	dir := flag.Arg(0)
	printTree(dir, maxDepth, 0)
}

func printTree(dir string, maxDepth, currentDepth int) {
	if maxDepth >= 0 && currentDepth > maxDepth {
		return
	}

	entries, err := os.ReadDir(dir)
	if err != nil {
		fmt.Printf("%s<error: %v>\n", indent(currentDepth), err)
		return
	}

	for i, entry := range entries {
		name := entry.Name()
		fullPath := filepath.Join(dir, name)

		isLast := i == len(entries)-1
		prefix := "├── "
		if isLast {
			prefix = "└── "
		}

		info, _ := entry.Info()
		suffix := ""
		if info.IsDir() {
			suffix = "/"
		} else if info.Mode()&fs.ModeSymlink != 0 {
			suffix = "@"
		}

		fmt.Printf("%s%s%s%s\n", indent(currentDepth), prefix, name, suffix)

		if entry.IsDir() && !isHidden(name) {
			printTree(fullPath, maxDepth, currentDepth+1)
		}
	}
}

func indent(level int) string {
	return strings.Repeat("│   ", level)
}

func isHidden(name string) bool {
	return strings.HasPrefix(name, ".") && name != "." && name != ".."
}
