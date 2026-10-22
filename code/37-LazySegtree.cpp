struct Segtree {
    int n;
    vector<int> st, lazy;

    void init(int n) {
        this->n = n;
        st.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    void build(int l, int r, const vector<int>& val, int idx) {
        if (l == r) {
            st[idx] = val[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(l, mid, val, idx * 2);
        build(mid + 1, r, val, idx * 2 + 1);
        st[idx] = st[idx * 2] + st[idx * 2 + 1];
    }

    void check(int l, int r, int idx) {
        if (l == r || lazy[idx] == 0) {
            return;
        }

        int mid = (l + r) >> 1;
        lazy[idx * 2] += lazy[idx];
        lazy[idx * 2 + 1] += lazy[idx];
        st[idx * 2] += (mid - l + 1) * lazy[idx];
        st[idx * 2 + 1] += (r - mid) * lazy[idx];
        lazy[idx] = 0;
    }

    int qry(int l, int r, int x, int y, int idx) {
        if (l > y || r < x) {
            return 0;
        }
        if (l >= x && r <= y) {
            return st[idx];
        }

        check(l, r, idx);
        int mid = (l + r) >> 1;
        return qry(l, mid, x, y, idx * 2)
             + qry(mid + 1, r, x, y, idx * 2 + 1);
    }

    void upd(int l, int r, int x, int y, int val, int idx) {
        if (l > y || r < x) {
            return;
        }
        if (l >= x && r <= y) {
            st[idx] += (r - l + 1) * val;
            lazy[idx] += val;
            return;
        }

        check(l, r, idx);
        int mid = (l + r) >> 1;
        upd(l, mid, x, y, val, idx * 2);
        upd(mid + 1, r, x, y, val, idx * 2 + 1);
        st[idx] = st[idx * 2] + st[idx * 2 + 1];
    }
};

// Does: Supports range additions and range sums with lazy propagation.
// Example: Segtree t; t.init(3); t.build(1, 3, vector<int>{0,1,2,3}, 1);
// t.upd(1, 3, 1, 2, 5, 1); // t.qry(1, 3, 1, 3, 1) == 16
