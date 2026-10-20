struct KMP {
    string p;
    vector<int> pi;
    KMP(const string& p) : p(p), pi(p.size()) {
        for (int i = 1, j = 0; i < (int)p.size(); i++) {
            while (j && p[i] != p[j])
                j = pi[j - 1];

            if (p[i] == p[j])
                j++;

            pi[i] = j;
        }
    }

    int count(const string& s) {
        int ans = 0;
        for (int i = 0, j = 0; i < (int)s.size(); i++) {
            while (j && s[i] != p[j])
                j = pi[j - 1];

            if (s[i] == p[j])
                j++;

            if (j == (int)p.size()) {
                ans++;
                j = pi[j - 1];
            }
        }
        return ans;
    }
};