vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

vector<int> search(const string& text, const string& pattern) {
    string s = pattern + '#' + text;
    vector<int> z = zFunction(s);
    vector<int> pos;

    int m = pattern.size();

    for (int i = m + 1; i < (int)s.size(); i++) {
        if (z[i] == m) {
            pos.push_back(i - m - 1);
        }
    }

    return pos;
}

// Does: Computes prefix-match lengths and finds pattern positions.
// Example: auto pos = search("ababa", "aba"); // {0, 2}, 0-based
