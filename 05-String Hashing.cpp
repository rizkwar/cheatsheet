struct Hash {
    using ull = unsigned long long;

    const ull B1 = 911382323, B2 = 972663749;
    const ull M1 = 1000000007, M2 = 1000000009;

    string s;
    int n;
    vector<ull> h1, h2, p1, p2;

    Hash(string s) {
        this->s = s;
        n = s.size();

        h1.resize(n + 1);
        h2.resize(n + 1);
        p1.resize(n + 1);
        p2.resize(n + 1);

        p1[0] = p2[0] = 1;

        for (int i = 0; i < n; i++) {
            int x = s[i] - 'a' + 1;

            h1[i + 1] = (h1[i] * B1 + x) % M1;
            h2[i + 1] = (h2[i] * B2 + x) % M2;

            p1[i + 1] = p1[i] * B1 % M1;
            p2[i + 1] = p2[i] * B2 % M2;
        }
    }

    pair<ull, ull> get(int l, int r) {
        ull x1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % M1 + M1) % M1;
        ull x2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % M2 + M2) % M2;
        return {x1, x2};
    }

    bool equal(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }
};