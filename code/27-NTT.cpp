struct NTT {
    int mod = 998244353;
    int root = 3;

    int power(int a, int e) {
        int r = 1;

        while (e) {
            if (e & 1) {
                r = 1LL * r * a % mod;
            }
            a = 1LL * a * a % mod;
            e >>= 1;
        }

        return r;
    }

    void ntt(vector<int>& a, bool inv) {
        int n = a.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;

            while (j & bit) {
                j ^= bit;
                bit >>= 1;
            }

            j ^= bit;

            if (i < j) {
                swap(a[i], a[j]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            int wlen = power(root, (mod - 1) / len);

            if (inv) {
                wlen = power(wlen, mod - 2);
            }

            for (int i = 0; i < n; i += len) {
                int w = 1;

                for (int j = 0; j < len / 2; j++) {
                    int u = a[i + j];
                    int v = 1LL * a[i + j + len / 2] * w % mod;

                    a[i + j] = u + v;
                    if (a[i + j] >= mod) {
                        a[i + j] -= mod;
                    }

                    a[i + j + len / 2] = u - v;
                    if (a[i + j + len / 2] < 0) {
                        a[i + j + len / 2] += mod;
                    }

                    w = 1LL * w * wlen % mod;
                }
            }
        }

        if (inv) {
            int inv_n = power(n, mod - 2);

            for (int &x : a) {
                x = 1LL * x * inv_n % mod;
            }
        }
    }

    vector<int> multiply(vector<int> A, vector<int> B) {
        if (A.empty() || B.empty()) {
            return {};
        }

        int sz = A.size() + B.size() - 1;
        int n = 1;

        while (n < sz) {
            n <<= 1;
        }

        A.resize(n);
        B.resize(n);

        ntt(A, false);
        ntt(B, false);

        for (int i = 0; i < n; i++) {
            A[i] = 1LL * A[i] * B[i] % mod;
        }

        ntt(A, true);
        A.resize(sz);

        return A;
    }
} ntt;

// Does: Multiplies polynomials exactly modulo 998244353 using NTT.
// Example: auto c = ntt.multiply({1, 2}, {3, 4}); // {3, 10, 8}
