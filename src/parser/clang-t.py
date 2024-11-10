import subprocess

# 定义 clang 命令和参数
filename = R"C:\Users\lanxi\Documents\lanxing\codes\ErJiu\staywalk\src\parser\test.cpp"
clang_cmd = [R'C:\Users\lanxi\Documents\lanxing\tools\clang+llvm-19.1.3-x86_64-pc-windows-msvc\bin\clang.exe', '-Xclang', '-ast-dump', '-fsyntax-only', filename]

# 执行命令并捕获输出
try:
    result = subprocess.run(clang_cmd, capture_output=True, text=True, check=True)
    print("AST Dump:\n", result.stdout)
except subprocess.CalledProcessError as e:
    print("Error occurred:", e.stderr)
