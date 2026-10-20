struct AhoCorasick {
    static constexpr int ALP = 52;

    vector<array<int, ALP>> nxt;
    vector<int> fail;
    vector<vector<int>> ids;
    vector<int> seen;
    vector<int> order;

    AhoCorasick(int maxNodes) {
        nxt.reserve(maxNodes);
        fail.reserve(maxNodes);
        ids.reserve(maxNodes);
        seen.reserve(maxNodes);

        addNode(); // root = 0
    }

    int addNode() {
        nxt.push_back({});
        nxt.back().fill(-1);
        fail.push_back(0);
        ids.push_back({});
        seen.push_back(0);
        return (int)nxt.size() - 1;
    }

    int getChar(char c) {
        return islower(c) ? c - 'a' : c - 'A' + 26;
    }

    void addWord(const string& s, int id) {
        int u = 0;

        for (char c : s) {
            int x = getChar(c);

            if (nxt[u][x] == -1)
                nxt[u][x] = addNode();

            u = nxt[u][x];
        }

        ids[u].push_back(id);
    }

    void build() {
        queue<int> q;

        for (int c = 0; c < ALP; c++) {
            if (nxt[0][c] != -1) {
                q.push(nxt[0][c]);
            } else {
                nxt[0][c] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int c = 0; c < ALP; c++) {
                int v = nxt[u][c];

                if (v == -1) {
                    nxt[u][c] = nxt[fail[u]][c];
                } else {
                    fail[v] = nxt[fail[u]][c];
                    q.push(v);
                }
            }
        }
    }

    vector<int> solve(const string& s, int q) {
        int u = 0;

        for (char c : s) {
            u = nxt[u][getChar(c)];
            seen[u] = 1;
        }

        // Propagate occurrence information through failure links.
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            seen[fail[u]] |= seen[u];
        }

        vector<int> ans(q + 1);

        for (int u = 0; u < (int)nxt.size(); u++) {
            if (!seen[u]) continue;

            for (int id : ids[u])
                ans[id] = 1;
        }

        return ans;
    }
};

void solve() {
    string s;
    cin >> s;

    int q;
    cin >> q;

    vector<string> qry(q + 1);
    int totalLen = 0;

    for (int i = 1; i <= q; i++) {
        cin >> qry[i];
        totalLen += qry[i].size();
    }

    AhoCorasick aho(totalLen + 1);

    for (int i = 1; i <= q; i++)
        aho.addWord(qry[i], i);

    aho.build();

    auto ans = aho.solve(s, q);

    for (int i = 1; i <= q; i++)
        cout << (ans[i] ? "y\n" : "n\n");
}