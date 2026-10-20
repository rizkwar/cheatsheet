struct CartesianTree {
    int root;
    vector<int> l, r, par;

    CartesianTree(const vector<int>& a) {
        int n = a.size();
        l.assign(n, -1);
        r.assign(n, -1);
        par.assign(n, -1);

        vector<int> st;

        for (int i = 0; i < n; i++) {
            int last = -1;

            while (!st.empty() && a[st.back()] > a[i]) {
                last = st.back();
                st.pop_back();
            }

            if (last != -1) {
                l[i] = last;
                par[last] = i;
            }

            if (!st.empty()) {
                r[st.back()] = i;
                par[i] = st.back();
            }

            st.push_back(i);
        }

        root = st.front();
    }
};