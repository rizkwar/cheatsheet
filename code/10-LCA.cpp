const int LOG = 20;

vector<vector<int>> adj;
int up[maxn][LOG + 1], dep[maxn];

void dfs(int node, int p) {
    up[node][0] = p;

    for (int j = 1; j <= LOG; j++) {
        up[node][j] = up[up[node][j - 1]][j - 1];
    }

    for (int next : adj[node]) {
        if (next != p) {
            dep[next] = dep[node] + 1;
            dfs(next, node);
        }
    }
}

int lca(int node, int next) {
    if (dep[node] < dep[next]) {
        swap(node, next);
    }

    int diff = dep[node] - dep[next];

    for (int j = 0; j <= LOG; j++) {
        if (diff & (1 << j)) {
            node = up[node][j];
        }
    }

    if (node == next) {
        return node;
    }

    for (int j = LOG; j >= 0; j--) {
        if (up[node][j] != up[next][j]) {
            node = up[node][j];
            next = up[next][j];
        }
    }

    return up[node][0];
}

// Does: Finds the lowest common ancestor using binary lifting.
// Example: adj = {{}, {2,3}, {1}, {1}}; dfs(1, 0);
// int ancestor = lca(2, 3); // 1
