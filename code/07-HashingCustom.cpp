#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
#define nel cout<<"\n"
#define f first
#define s second
#define int long long
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

// --- compact custom hash (splitmix64) ---
struct custom_hash {
    using ull = unsigned long long;
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(unsigned long long x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + FIXED_RANDOM);
    }
};

// --- usage ---
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<long long,int,custom_hash> mp;
    mp.reserve(1024);               // reserve before heavy inserts
    mp.max_load_factor(0.25f);      // reduce collisions / rehashing pressure

    mp[1] = 10;
    if (mp.find(1) != mp.end()) cout << mp[1] << '\n';
}

// Does: Randomizes integer hashes to reduce adversarial collisions.
// Example: unordered_map<long long,int,custom_hash> mp; mp[42] = 7;
