struct CentroidDecomposition {
  int n;
  vector<vector<int>> g;
  vector<int> sz;
  vector<bool> dead;

  CentroidDecomposition(int n) : n(n) {
    g.resize(n + 1);
    sz.resize(n + 1);
    dead.assign(n + 1, false);
  }

  void add_edge(int node, int next) {
    g[node].push_back(next);
    g[next].push_back(node);
  }

  int get_size(int node, int p) {
    sz[node] = 1;

    for (int next : g[node]) {
      if (next == p || dead[next]) continue;
      sz[node] += get_size(next, node);
    }

    return sz[node];
  }

  int get_centroid(int node, int p, int tot) {
    for (int next : g[node]) {
      if (next == p || dead[next]) continue;

      if (sz[next] > tot / 2)
        return get_centroid(next, node, tot);
    }

    return node;
  }

  int get_centroid(int start) {
    int tot = get_size(start, -1);
    return get_centroid(start, -1, tot);
  }

  void collect(int node, int p, int dist, vector<int>& nodes) {
    nodes.push_back(dist);

    for (int next : g[node]) {
      if (next == p || dead[next]) continue;
      collect(next, node, dist + 1, nodes);
    }
  }

  void decompose(int node) {
    int c = get_centroid(node);

    dead[c] = true;

    // PROCESS CENTROID c HERE

    for (int next : g[c]) {
      if (dead[next]) continue;
      decompose(next);
    }
  }
};

// Does: Recursively splits a tree at centroids for custom path queries.
// Example: CentroidDecomposition cd(n); // add tree edges with add_edge
// cd.decompose(1); // add your query logic at PROCESS CENTROID
