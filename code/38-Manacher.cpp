vector<int> manacher(const string &s) {
    int n = s.size();
    vector<int> p(n);

    int c = 0, r = 0;
    for(int i=0; i<n; i++) {
        if (i <= r) {
            int mirror = 2*c - i;
            p[i] = min(r-i, p[mirror]);
        }

        while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && s[i+p[i]+1] == s[i-p[i]-1]) p[i]++;

        if (i + p[i] > r) {
            r = i + p[i];
            c = i;
        }
    }

    return p;
}