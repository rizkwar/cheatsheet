int st[40 * maxn], L[40 * maxn], R[40 * maxn];
int a[maxn], root[maxn];
int ptr = 0;

int build(int l, int r) {
    int node = ++ptr;

    if (l == r) {
        st[node] = a[l];
        return node;
    }

    int mid = (l + r) >> 1;
    L[node] = build(l, mid);
    R[node] = build(mid + 1, r);
    st[node] = st[L[node]] + st[R[node]];

    return node;
}

int qry(int node, int l, int r, int x, int y) {
    if (l > y || r < x) {
        return 0;
    }

    if (l >= x && r <= y) {
        return st[node];
    }

    int mid = (l + r) >> 1;
    return qry(L[node], l, mid, x, y)
         + qry(R[node], mid + 1, r, x, y);
}

int upd(int prev, int l, int r, int pos, int val) {
    int node = ++ptr;

    st[node] = st[prev];
    L[node] = L[prev];
    R[node] = R[prev];

    if (l == r) {
        st[node] = val;
        return node;
    }

    int mid = (l + r) >> 1;

    if (pos <= mid) {
        L[node] = upd(L[prev], l, mid, pos, val);
    } else {
        R[node] = upd(R[prev], mid + 1, r, pos, val);
    }

    st[node] = st[L[node]] + st[R[node]];
    return node;
}

void solve() {
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    root[1] = build(1, n);

    vector<int> v(q + 3);
    v[1] = 1;

    int idx = 1, cur = 1;

    for (int i = 1; i <= q; i++) {
        int mode, k;
        cin >> mode >> k;

        if (mode == 1) {
            int pos, val;
            cin >> pos >> val;

            root[++idx] = upd(root[v[k]], 1, n, pos, val);
            v[k] = idx;
        } else if (mode == 2) {
            int l, r;
            cin >> l >> r;

            cout << qry(root[v[k]], 1, n, l, r) << '\n';
        } else {
            root[++idx] = root[v[k]];
            cur++;
            v[cur] = idx;
        }
    }
}

// Does: Keeps array versions with point assignments and range sums.
// Example: root[1] = build(1, n); // initialize a[1..n] first; n >= 2
// root[2] = upd(root[1], 1, n, 2, 7); // qry(root[2], 1, n, 2, 2) == 7
