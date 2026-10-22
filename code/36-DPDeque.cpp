while (!dq.empty() && dq.front() < j - d) {
    dq.pop_front();
}

while (!dq.empty() && dp[i - 1][now] >= dp[i - 1][dq.back()]) {
    dq.pop_back();
}

dq.push_back(now);

// Does: Maintains sliding-window DP maxima in amortized O(1) per index.
// Example: Declare deque<int> dq before the loop; add valid now indices.
// After these steps, int best = dp[i - 1][dq.front()];
