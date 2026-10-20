int r, c, m, b;
cin >> r >> c >> m >> b;

if (c > 6) swap(r, c);

int n = 2 * c;
int mask = (1 << n) - 1;

vector<vector<int>> dp(1 << n, vector<int>(m + 1));
dp[0][0] = 1;

for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
        vector<vector<int>> ndp(1 << n, vector<int>(m + 1));

        for (int used = 0; used < (1 << n); used++) {
            for (int cnt = 0; cnt <= m; cnt++) {
                if (!dp[used][cnt]) continue;

                int nxt = (used << 1) & mask;

                ndp[nxt][cnt] = (ndp[nxt][cnt] + dp[used][cnt]) % modn;

                if (cnt == m) continue;

                bool ok = true;

                if (j >= 1 && (used & 1)) ok = false;
                if (j >= 2 && (used & 2)) ok = false;
                if (i >= 1 && (used & (1 << (c - 1)))) ok = false;
                if (i >= 2 && (used & (1 << (n - 1)))) ok = false;

                if (ok) {
                    ndp[nxt | 1][cnt + 1] =
                        (ndp[nxt | 1][cnt + 1] + dp[used][cnt]) % modn;
                }
            }
        }

        dp.swap(ndp);
    }
}