struct TwoSat {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp, order;
    vector<bool> vis;

    TwoSat(int n) {
        this->n = n;
        g.assign(2 * n, {});
        rg.assign(2 * n, {});
        comp.assign(2 * n, -1);
        vis.assign(2 * n, false);
    }

    // i = true: 2*i, i = false: 2*i+1
    // negation: x ^ 1

    // clause (a OR b)
    void add(int a, int b) {
        g[a ^ 1].push_back(b);
        g[b ^ 1].push_back(a);
        rg[b].push_back(a ^ 1);
        rg[a].push_back(b ^ 1);
    }

    void dfs1(int node) {
        vis[node] = true;

        for (int next : g[node]) {
            if (!vis[next]) {
                dfs1(next);
            }
        }

        order.push_back(node);
    }

    void dfs2(int node, int c) {
        comp[node] = c;

        for (int next : rg[node]) {
            if (comp[next] == -1) {
                dfs2(next, c);
            }
        }
    }

    bool solve(vector<int>& ans) {
        for (int i = 0; i < 2 * n; i++) {
            if (!vis[i]) {
                dfs1(i);
            }
        }

        reverse(order.begin(), order.end());

        int c = 0;
        for (int node : order) {
            if (comp[node] == -1) {
                dfs2(node, c++);
            }
        }

        ans.resize(n);

        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) {
                return false;
            }
            ans[i] = comp[2 * i] > comp[2 * i + 1];
        }

        return true;
    }
};