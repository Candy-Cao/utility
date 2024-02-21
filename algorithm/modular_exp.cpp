
int modular_exp(int b, int n, int m) {
    long long x = 1;
    long long power = b % m;
    int bitSize = n > 0 ? 32 - __builtin_clz(n) : 0;
    for (int i = 0; i < bitSize; i++) {
        if (n & 1 << i) {
            x = (x * power) % m;
        }
        power = (power * power) % m;
    }
    return x;
}