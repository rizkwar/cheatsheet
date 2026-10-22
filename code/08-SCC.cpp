struct SCC {
    int n, cnt;
    vector<vector<int>> g, rg;
    vector<int> comp, order, deg;
    vector<bool> vis;

    SCC(int n) {
        this->n = n;
        cnt = 0;
        g.assign(n + 1, {});
        rg.assign(n + 1, {});
        comp.assign(n + 1, -1);
        vis.assign(n + 1, false);
    }

    void addEdge(int node, int next) {
        g[node].push_back(next);
        rg[next].push_back(node);
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

    void run() {
        for (int node = 1; node <= n; node++) {
            if (!vis[node]) {
                dfs1(node);
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            if (comp[order[i]] == -1) {
                dfs2(order[i], cnt);
                cnt++;
            }
        }
    }

    vector<vector<int>> buildDAG() {
        vector<vector<int>> dag(cnt);
        vector<set<int>> seen(cnt);
        deg.assign(cnt, 0);

        for (int node = 1; node <= n; node++) {
            for (int next : g[node]) {
                int a = comp[node];
                int b = comp[next];

                if (a != b && !seen[a].count(b)) {
                    seen[a].insert(b);
                    dag[a].push_back(b);
                    deg[b]++;
                }
            }
        }

        return dag;
    }
};

// Does: Groups mutually reachable vertices and builds their condensed DAG.
// Example: SCC s(2); s.addEdge(1, 2); s.run(); // s.cnt == 2
// auto dag = s.buildDAG(); // vertices are 1-based; components are 0-based
