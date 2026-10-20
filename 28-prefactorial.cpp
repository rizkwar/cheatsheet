int fac[maxn + 5], ifac[maxn + 5];

int C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    return 1LL * fac[n] * ifac[k] % modn * ifac[n - k] % modn;
}

void pre() {
    fac[0] = 1;

    for (int i = 1; i <= maxn; i++) {
        fac[i] = 1LL * fac[i - 1] * i % modn;
    }

    ifac[maxn] = binpow(fac[maxn], modn - 2);

    for (int i = maxn; i >= 1; i--) {
        ifac[i - 1] = 1LL * ifac[i] * i % modn;
    }
}