struct Edge {
    int to, rev, cap;
    bool orig;
};

struct Dinic {
    int n;
    vector<vector<Edge>> g;
    vector<int> lv, ptr;

    Dinic(int n = 0) { init(n); }

    void init(int n) {
        this->n = n;
        g.assign(n, {});
        lv.resize(n);
        ptr.resize(n);
    }

    void addEdge(int node, int next, int cap) {
        g[node].push_back({next, (int)g[next].size(), cap, 1});
        g[next].push_back({node, (int)g[node].size() - 1, 0, 0});
    }

    bool bfs(int s, int t) {
        fill(lv.begin(), lv.end(), -1);
        queue<int> q;
        q.push(s);
        lv[s] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto &e : g[node]) {
                if (e.cap > 0 && lv[e.to] == -1) {
                    lv[e.to] = lv[node] + 1;
                    q.push(e.to);
                }
            }
        }
        return lv[t] != -1;
    }

    int dfs(int node, int t, int f) {
        if (node == t) { return f; }

        for (int &i = ptr[node]; i < (int)g[node].size(); i++) {
            auto &e = g[node][i];

            if (e.cap == 0 || lv[e.to] != lv[node] + 1) {
                continue;
            }

            int x = dfs(e.to, t, min(f, e.cap));

            if (x > 0) {
                e.cap -= x;
                g[e.to][e.rev].cap += x;
                return x;
            }
        }
        return 0;
    }

    int flow(int s, int t) {
        int ans = 0;

        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);

            while (true) {
                int f = dfs(s, t, 1e9);
                if (f == 0) { break; }
                ans += f;
            }
        }
        return ans;
    }

    bool recover(int node, int t, vector<int>& path, vector<bool>& vis) {
        if (node == t) { return true; }
        vis[node] = true;

        for (auto &e : g[node]) {
            if (!e.orig || vis[e.to] || g[e.to][e.rev].cap == 0) {
                continue;
            }

            g[e.to][e.rev].cap--;
            path.push_back(e.to);

            if (recover(e.to, t, path, vis)) {
                return true;
            }

            path.pop_back();
            g[e.to][e.rev].cap++;
        }

        return false;
    }
};

// Does: Computes maximum flow in a directed graph with capacities.
// Example: Dinic d(2); d.addEdge(0, 1, 5); int f = d.flow(0, 1); // 5
