vector<ll>adj[maxn],flat(2*maxn);
ll st[maxn], en[maxn];

ll t;
void dfs(ll node, ll par) {
    flat[++t] = node;
    st[node] = t;
    for (auto next : adj[node]) if (next != par) {
        dfs(next,node);
    }
    flat[++t] = node;
    en[node] = t;
}