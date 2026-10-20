struct Edge {
    int to, rev, cap, cost, orig;
};

struct MinCostFlow {
    int n;
    vector<vector<Edge>> g;
    vector<int> pi, dist, pv_node, pv_edge;

    MinCostFlow(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        g.assign(n, {});
        pi.assign(n, 0);
        dist.resize(n);
        pv_node.resize(n);
        pv_edge.resize(n);
    }

    void addEdge(int node, int next, int cap, int cost) {
        g[node].push_back({next, (int)g[next].size(), cap, cost, cap});
        g[next].push_back({node, (int)g[node].size() - 1, 0, -cost, 0});
    }

    bool sp(int s, int t) {
        const int INF = 1e9;
        priority_queue<pair<int,int>, vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        fill(dist.begin(), dist.end(), INF);
        fill(pv_node.begin(), pv_node.end(), -1);
        fill(pv_edge.begin(), pv_edge.end(), -1);

        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            if (d != dist[node]) {
                continue;
            }

            for (int i = 0; i < (int)g[node].size(); i++) {
                auto &e = g[node][i];
                if (e.cap == 0) {
                    continue;
                }

                int next = e.to;
                int nd = d + e.cost + pi[node] - pi[next];

                if (nd < dist[next]) {
                    dist[next] = nd;
                    pv_node[next] = node;
                    pv_edge[next] = i;
                    pq.push({nd, next});
                }
            }
        }

        return dist[t] != INF;
    }

    pair<int,int> flow(int s, int t, int need) {
        int f = 0, cost = 0;
        const int INF = 1e9;

        while (f < need && sp(s, t)) {
            for (int i = 0; i < n; i++) {
                if (dist[i] < INF) {
                    pi[i] += dist[i];
                }
            }

            int add = need - f;

            for (int next = t; next != s; next = pv_node[next]) {
                add = min(add, g[pv_node[next]][pv_edge[next]].cap);
            }

            int pathCost = pi[t] - pi[s];

            for (int next = t; next != s; next = pv_node[next]) {
                int node = pv_node[next], i = pv_edge[next];
                auto &e = g[node][i];

                e.cap -= add;
                g[next][e.rev].cap += add;
            }

            f += add;
            cost += add * pathCost;
        }

        return {f, cost};
    }
};

// kalo mau diubah jadi maximual yang diubah cost nya jadi -cost
// -> return {f, -cost}
// trus pas add edge weight nya juga dibikin -weight