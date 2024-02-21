#include <stdio.h>
#include <string.h>

// 定义基数和模数
#define BASE 256
#define MOD 101 // 这里使用一个简单的模数，实际使用中应根据需求选择合适的模数

// 计算字符串的滚动哈希值
unsigned int rollingHash(const char *str, int len) {
    unsigned int hash = 0;
    for (int i = 0; i < len; i++) {
        hash = (hash * BASE + str[i]) % MOD;
    }
    return hash;
}

// 更新滚动哈希值
unsigned int updateRollingHash(unsigned int hash, char prevChar, char nextChar, int len) {
    // 先减去滑出窗口的字符的贡献
    hash = (hash + MOD - (prevChar * (unsigned int)pow(BASE, len - 1)) % MOD) % MOD;
    // 再加上滑入窗口的字符的贡献
    hash = (hash * BASE + nextChar) % MOD;
    return hash;
}

int main() {
    char str[] = "abcabcabcd"; // 输入的字符串
    int len = strlen(str); // 字符串长度

    int windowSize = 3; // 窗口大小
    unsigned int hash = rollingHash(str, windowSize); // 计算初始哈希值

    printf("Hash of \"%.*s\": %u\n", windowSize, str, hash);

    for (int i = 1; i <= len - windowSize; i++) {
        // 更新滚动哈希值
        hash = updateRollingHash(hash, str[i - 1], str[i + windowSize - 1], windowSize);
        printf("Hash of \"%.*s\": %u\n", windowSize, str + i, hash);
    }

    return 0;
}
