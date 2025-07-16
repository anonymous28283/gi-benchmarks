#!/bin/bash

# 检查输入参数的数量
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <prefix>"
    exit 1
fi

# 获取输入参数
prefix=$1
root_dir="$prefix"
uname_str=$(uname)

if [[ "$uname_str" == "Darwin" ]]; then
    parse_script="./$prefix/parse_${prefix}_darwin"
elif [[ "$uname_str" == "Linux" ]]; then
    parse_script="./$prefix/parse_${prefix}_linux"
else
    echo "Unsupported OS: $uname_str"
    exit 1
fi

# 确保输入的目录和脚本存在
if [ ! -d "$root_dir" ]; then
    echo "Root directory does not exist: $root_dir"
    exit 1
fi

if [ ! -f "$parse_script" ]; then
    echo "Parse script does not exist: $parse_script"
    exit 1
fi

# 遍历所有以 $prefix 开头的子目录
for subdir in "$root_dir"/"$prefix"-t*/; do
    if [ -d "$subdir" ]; then
        # 遍历每个子目录下的文件
        for file in "$subdir"*; do
            if [ -f "$file" ]; then
                echo "Processing file: $file"
                "$parse_script" "$file"
                exit_code=$?
                if [ $exit_code -ne 0 ]; then
                    echo "Error occurred while processing $file. Exit code: $exit_code"
                    exit 1
                fi
            fi
        done
    fi
done

echo "All files processed successfully."