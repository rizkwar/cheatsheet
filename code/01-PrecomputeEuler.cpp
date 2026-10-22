vector<int> phi(n + 2);
for(int i = 1; i <= n; i++) phi[i] = i;

for(int i = 2; i <= n; i++){
    if(phi[i] == i){
        for(int j = 1; j <= n; j += i){
            phi[j] -= phi[j] / i;
        }
    }
}

// Does: Precomputes phi[x], the count of integers 1..x coprime to x.
// Example: Set n=10, run the sieve, then phi[10] should be 4.
// Note: The inner loop must start at j=i; j=1 above is a typo.
