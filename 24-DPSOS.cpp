// Sum over submasks:  dp[S] = Σ f[T], T ⊆ S
for (int bit = 0; bit < K; bit++)
    for (int mask = 0; mask < (1 << K); mask++)
        if (mask & (1 << bit))
            dp[mask] += dp[mask ^ (1 << bit)];

// Sum over supermasks: dp[S] = Σ f[T], T ⊇ S
for (int bit = 0; bit < K; bit++)
    for (int mask = 0; mask < (1 << K); mask++)
        if (mask & (1 << bit))
            dp[mask ^ (1 << bit)] += dp[mask];

// Recursive: enumerate all submasks
void add(int mask, int bit) {
    if (dp[mask] >= 2) return;
    if (bit < 0) return void(dp[mask]++);
    add(mask, bit - 1);
    if (mask & (1 << bit))
        add(mask ^ (1 << bit), bit - 1);
}