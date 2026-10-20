struct Blossom {
    int n;
    vector<vector<int>> g;
    vector<int> match, p, base;
    vector<bool> used, blossom;
    queue<int> q;

    Blossom(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        g.assign(n, {});
        match.assign(n, -1);
        p.resize(n);
        base.resize(n);
        used.resize(n);
        blossom.resize(n);
    }

    void addEdge(int node, int next) {
        g[node].push_back(next);
        g[next].push_back(node);
    }

    int lca(int a, int b) {
        vector<bool> seen(n);

        while (true) {
            a = base[a];
            seen[a] = true;

            if (match[a] == -1) {
                break;
            }

            a = p[match[a]];
        }

        while (true) {
            b = base[b];

            if (seen[b]) {
                return b;
            }

            b = p[match[b]];
        }
    }

    void markPath(int node, int b, int child) {
        while (base[node] != b) {
            blossom[base[node]] = true;
            blossom[base[match[node]]] = true;
            p[node] = child;
            child = match[node];
            node = p[match[node]];
        }
    }

    bool findPath(int root) {
        fill(used.begin(), used.end(), false);
        fill(p.begin(), p.end(), -1);
        iota(base.begin(), base.end(), 0);

        while (!q.empty()) {
            q.pop();
        }

        q.push(root);
        used[root] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int next : g[node]) {
                if (base[node] == base[next] || match[node] == next) {
                    continue;
                }

                if (next == root || (match[next] != -1 && p[match[next]] != -1)) {
                    int b = lca(node, next);
                    fill(blossom.begin(), blossom.end(), false);

                    markPath(node, b, next);
                    markPath(next, b, node);

                    for (int i = 0; i < n; i++) {
                        if (blossom[base[i]]) {
                            base[i] = b;

                            if (!used[i]) {
                                used[i] = true;
                                q.push(i);
                            }
                        }
                    }
                } else if (p[next] == -1) {
                    p[next] = node;

                    if (match[next] == -1) {
                        int cur = next;

                        while (cur != -1) {
                            int prev = p[cur];
                            int nextMatch = (prev == -1 ? -1 : match[prev]);

                            match[cur] = prev;

                            if (prev != -1) {
                                match[prev] = cur;
                            }

                            cur = nextMatch;
                        }

                        return true;
                    }

                    used[match[next]] = true;
                    q.push(match[next]);
                }
            }
        }

        return false;
    }

    int solve() {
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (match[i] == -1 && findPath(i)) {
                ans++;
            }
        }

        return ans;
    }
};