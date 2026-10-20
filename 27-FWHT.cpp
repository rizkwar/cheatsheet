struct FWHT {
    int mod;

    FWHT(int mod) : mod(mod) {}

    void transform(vector<int>& a) {
        int n = a.size();

        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += len << 1) {
                for (int j = 0; j < len; j++) {
                    int u = a[i + j];
                    int v = a[i + j + len];

                    a[i + j] = (u + v) % mod;
                    a[i + j + len] = (u - v + mod) % mod;
                }
            }
        }
    }

    void inverse(vector<int>& a) {
        transform(a);

        int inv_n = modpow(a.size(), mod - 2);
        for (int& x : a)
            x = 1LL * x * inv_n % mod;
    }

    int modpow(int a, int e) {
        int res = 1;

        while (e) {
            if (e & 1)
                res = 1LL * res * a % mod;
            a = 1LL * a * a % mod;
            e >>= 1;
        }

        return res;
    }
};