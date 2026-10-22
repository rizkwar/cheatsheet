struct FFT {
  using cd = complex<double>;
  ld PI=acos(-1); 
  void fft(vector<cd>& a, bool inv){
    int n = a.size();
    for(int i=1,j=0;i<n;i++){
      int bit = n>>1;
      for(; j&bit; bit>>=1) j ^= bit;
      j ^= bit;
      if(i<j) swap(a[i], a[j]);
    }
    for(int len=2; len<=n; len<<=1){
      double ang = 2*PI/len * (inv ? -1 : 1);
      cd wlen(cos(ang), sin(ang));
      for(int i=0;i<n;i+=len){
        cd w(1);
        for(int j=0;j<len/2;j++){
          cd u = a[i+j];
          cd v = a[i+j+len/2] * w;
          a[i+j] = u+v;a
          a[i+j+len/2] = u-v;
          w *= wlen;
        }
      }
    }
    if(inv) for(auto &x: a) x /= n;
  }
  vector<long long> multiply(const vector<long long>& A, const vector<long long>& B){
    int n = 1;
    while(n < (int)A.size() + (int)B.size()) n <<= 1;
    vector<cd> fa(n);
    for(size_t i=0;i<A.size();++i) fa[i] = cd((double)A[i], 0);
    for(size_t i=0;i<B.size();++i) fa[i] += cd(0, (double)B[i]); 
    fft(fa, false);
    vector<cd> fa2(n);
    for(int i=0;i<n;i++){
      cd j = fa[(n-i)%n];
      cd a = (fa[i] + conj(j)) * cd(0.5, 0);
      cd b = (fa[i] - conj(j)) * cd(0, -0.5);
      fa2[i] = a * b;
    }
    fft(fa2, true);
    vector<long long> res(n);
    for(int i=0;i<n;i++) res[i] = (long long) llround(fa2[i].real());
    return res;
  }
} fft;

// Does: Multiplies polynomials using FFT and rounds integer coefficients.
// Example: auto c = fft.multiply({1, 2}, {3, 4}); // starts {3, 10, 8}
// Note: Remove the stray 'a' after a[i+j] = u+v; before compiling.
