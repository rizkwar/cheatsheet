struct Mo {
    int n, q, B;
    vector<int> a, freq;
    long long cur;
    
    Mo(vector<int> a) : a(a) {
        n = a.size() - 1;
        B = sqrt(n);
        freq.assign(1000005, 0);
        cur = 0;
    }

    void add(int x) {
        cur -= 1LL * x * freq[x] * freq[x];
        freq[x]++;
        cur += 1LL * x * freq[x] * freq[x];
    }

    void remove(int x) {
        cur -= 1LL * x * freq[x] * freq[x];
        freq[x]--;
        cur += 1LL * x * freq[x] * freq[x];
    }

    vector<long long> solve(vector<pair<int,int>> qry) {
        q = qry.size();

        vector<tuple<int,int,int>> v(q);
        for (int i = 0; i < q; i++) {
            v[i] = {qry[i].first, qry[i].second, i};
        }

        sort(v.begin(), v.end(), [&](auto &x, auto &y) {
            auto [l1, r1, id1] = x;
            auto [l2, r2, id2] = y;

            int b1 = l1 / B, b2 = l2 / B;
            if (b1 != b2) {
                return b1 < b2;
            }
            return (b1 & 1) ? r1 > r2 : r1 < r2;
        });

        vector<long long> ans(q);
        int l = 1, r = 0;

        for (auto [ql, qr, id] : v) {
            while (r < qr) {
                add(a[++r]);
            }
            while (l > ql) {
                add(a[--l]);
            }
            while (r > qr) {
                remove(a[r--]);
            }
            while (l < ql) {
                remove(a[l++]);
            }

            ans[id] = cur;
        }

        return ans;
    }
};