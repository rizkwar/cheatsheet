struct Sparse {
    int n, LOG;
    vector<vector<int>> st;
    vector<int> lg;

    void init(int n) {
        this->n = n;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        LOG = lg[n] + 1;
        st.assign(n + 1, vector<int>(LOG));
    }

    void build(const vector<int>& val) {
        for (int i = 1; i <= n; i++) {
            st[i][0] = val[i];
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 1; i + (1 << k) - 1 <= n; i++) {
                st[i][k] = gcd(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    int qry(int l, int r) {
        int k = lg[r - l + 1];
        return gcd(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

// Does: Answers static range GCD queries in O(1) after O(n log n) setup.
// Example: Sparse t; t.init(3); t.build(vector<int>{0, 6, 9, 15});
// int result = t.qry(1, 3); // 3; positions are 1-based, inclusive
