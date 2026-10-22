for (int i = 1; i <= q; i++) {
    cin >> b[i].first >> b[i].second;
    lo[i] = 1;
    hi[i] = m;
    ans[i] = -1;
}

while (true) {
    bool done = true;
    vector<vector<int>> at(m + 1);

    for (int i = 1; i <= q; i++) {
        if (lo[i] <= hi[i]) {
            done = false;
            int mid = (lo[i] + hi[i]) >> 1;
            at[mid].push_back(i);
        }
    }

    if (done) {
        break;
    }

    iota(par + 1, par + n + 1, 1);
    for (int i = 1; i <= m; i++) {
        merge(a[i].first, a[i].second);
        for (int id : at[i]) {
            if (same(b[id].first, b[id].second)) {
                ans[id] = i;
                hi[id] = i - 1;
            } else {
                lo[id] = i + 1;
            }
        }
    }
}

for (int i = 1; i <= q; i++) {
    if (b[i].first == b[i].second) {
        ans[i] = 0;
    }
    cout << ans[i] << '\n';
}

// Does: Finds the first added edge connecting each queried vertex pair.
// Example: Edges (1,2), (2,3); query (1,3) -> 2; never connected -> -1.
// Use 1-based edges in a, query pairs in b, and DSU merge/same helpers.
