struct SuffixArray {
    string s;
    int n;
    vector<int> sa, c, lcp;

    SuffixArray(string s) {
        this->s = s + "$";
        n = s.size() + 1;
        buildSA();
    }

    void buildSA() {
        sa.resize(n);
        c.resize(n);

        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {s[i], i};
        }

        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++) {
            sa[i] = a[i].second;
        }

        c[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[sa[i]] = c[sa[i - 1]] + (a[i].first != a[i - 1].first);
        }

        for (int k = 0; (1 << k) < n; k++) {
            vector<int> nsa(n), cnt(n), pos(n);

            for (int i = 0; i < n; i++) {
                nsa[i] = (sa[i] - (1 << k) + n) % n;
            }

            for (int x : nsa) {
                cnt[c[x]]++;
            }

            for (int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }

            for (int x : nsa) {
                nsa[pos[c[x]]++] = x;
            }

            sa = nsa;

            vector<int> nc(n);
            for (int i = 1; i < n; i++) {
                pair<int, int> x = {
                    c[sa[i]],
                    c[(sa[i] + (1 << k)) % n]
                };
                pair<int, int> y = {
                    c[sa[i - 1]],
                    c[(sa[i - 1] + (1 << k)) % n]
                };

                nc[sa[i]] = nc[sa[i - 1]] + (x != y);
            }

            c = nc;
        }
    }

    void buildLCP() {
        lcp.assign(n, 0);
        vector<int> rank(n);

        for (int i = 0; i < n; i++) {
            rank[sa[i]] = i;
        }

        for (int i = 0, k = 0; i < n - 1; i++) {
            int r = rank[i];

            if (r == 0) {
                continue;
            }

            int j = sa[r - 1];

            while (s[i + k] == s[j + k]) {
                k++;
            }

            lcp[r] = k;

            if (k) {
                k--;
            }
        }
    }

    bool contains(const string& t) {
        int l = 0, r = n - 1;

        while (l <= r) {
            int mid = (l + r) >> 1;
            int cmp = s.compare(sa[mid], t.size(), t);

            if (cmp == 0) {
                return true;
            }

            if (cmp < 0) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return false;
    }
};

// Does: Sorts suffixes, builds adjacent LCPs, and searches substrings.
// Example: SuffixArray sa("banana"); bool found = sa.contains("ana");
