# Go Projects

This directory contains independent Go projects. Each subdirectory is a self-contained Go project with its own `go.mod` file.

## Projects

| Project | Description | Status |
|---------|-------------|--------|
| [list-dir](./list-dir) | Recursively list directory structure with depth control | Ready |

## Adding a New Project

```bash
cd /home/ubuntu/jyy_os/go-projects
mkdir my-project
cd my-project
go mod init github.com/yourname/my-project
```

## Cross-Platform Compilation

Go supports cross-platform compilation, making it convenient to develop on Windows and deploy to Linux:

```bash
# Build for Linux from Windows
set GOOS=linux
set GOARCH=amd64
go build -o output-linux main.go

# Build for Windows from Linux
GOOS=windows GOARCH=amd64 go build -o output.exe main.go
```

## Resources

- [Go Official Documentation](https://go.dev/doc/)
- [Effective Go](https://go.dev/doc/effective_go)
- [Go by Example](https://gobyexample.com/)
