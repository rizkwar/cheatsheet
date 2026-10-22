struct Hungarian {
    int n;
    vector<vector<int>> a;
    vector<int> node, next, p, way;

    Hungarian(const vector<vector<int>>& a) : a(a) {
        n = (int)a.size() - 1;
        node.assign(n + 1, 0);
        next.assign(n + 1, 0);
        p.assign(n + 1, 0);
        way.assign(n + 1, 0);
    }

    pair<int, vector<int>> solve() {
        const int INF = 1e9;

        for (int i = 1; i <= n; i++) {
            p[0] = i;

            int j0 = 0;
            vector<int> minv(n + 1, INF);
            vector<bool> used(n + 1, false);

            do {
                used[j0] = true;
                int i0 = p[j0];
                int delta = INF, j1 = 0;

                for (int j = 1; j <= n; j++) {
                    if (used[j]) continue;

                    int cur = a[i0][j] - node[i0] - next[j];

                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }

                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }

                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        node[p[j]] += delta;
                        next[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }

                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0 != 0);
        }

        vector<int> match(n + 1);
        for (int j = 1; j <= n; j++)
            match[p[j]] = j;

        return {-next[0], match};
    }
};

// Does: Finds a minimum-cost one-to-one assignment in a square matrix.
// Example: Hungarian h({{0,0,0}, {0,1,5}, {0,4,2}}); // 1-based costs
// auto [cost, match] = h.solve(); // cost == 3; match[1]=1, match[2]=2
