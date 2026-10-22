struct HLD {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> par, dep, sz, head, pos;

    HLD(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        timer = 0;
        adj.assign(n + 1, {});
        par.resize(n + 1);
        dep.resize(n + 1);
        sz.resize(n + 1);
        head.resize(n + 1);
        pos.resize(n + 1);
    }

    void addEdge(int node, int next) {
        adj[node].push_back(next);
        adj[next].push_back(node);
    }

    void dfs(int node, int p) {
        par[node] = p;
        sz[node] = 1;

        for (int next : adj[node]) {
            if (next == p) continue;

            dep[next] = dep[node] + 1;
            dfs(next, node);
            sz[node] += sz[next];
        }
    }

    void decompose(int node) {
        pos[node] = ++timer;

        int heavy = -1;
        for (int next : adj[node]) {
            if (next == par[node]) continue;

            if (heavy == -1 || sz[next] > sz[heavy])
                heavy = next;
        }

        if (heavy == -1) return;

        head[heavy] = head[node];
        decompose(heavy);

        for (int next : adj[node]) {
            if (next == par[node] || next == heavy) continue;

            head[next] = next;
            decompose(next);
        }
    }

    void build(int root = 1) {
        dep[root] = 0;
        dfs(root, 0);

        timer = 0;
        head[root] = root;
        decompose(root);
    }

    int lca(int node, int next) {
        while (head[node] != head[next]) {
            if (dep[head[node]] > dep[head[next]])
                node = par[head[node]];
            else
                next = par[head[next]];
        }

        return dep[node] < dep[next] ? node : next;
    }
};

// Does: Splits a tree into heavy chains and supports LCA queries.
// Example: HLD h(3); h.addEdge(1, 2); h.addEdge(1, 3); h.build();
// int ancestor = h.lca(2, 3); // 1
