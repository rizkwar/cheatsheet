struct LiChao {
  struct line {
    int m, b;
    int eval(int x) const { return m * x + b; }
  };
  int L, R;
  const int NEG_INF = -4e18; 
  vector<line> seg; 
  vector<int> lc;   
  vector<int> rc;    
  int nodes;         
  void init(int _L, int _R){
    L = _L; R = _R;
    nodes = 1;
    seg.assign(1, {0, NEG_INF});
    lc.assign(1, -1);
    rc.assign(1, -1);
  }
  int new_node(){
    seg.push_back({0, NEG_INF});
    lc.push_back(-1);
    rc.push_back(-1);
    return nodes++;
  }
  void add_line(int nm, int nb){ add_line_rec(0, L, R, {nm, nb}); }
  void add_line_rec(int idx, int l, int r, line nw){
    if(seg[idx].b == NEG_INF){
      seg[idx] = nw;
      return;
    }
    int mid = (l + r) >> 1;
    bool left = nw.eval(l) >= seg[idx].eval(l);
    bool mpos = nw.eval(mid) >= seg[idx].eval(mid);
    if(mpos){
      swap(seg[idx], nw); 
    }
    if(l == r) return;
    if(left != mpos){
      if(lc[idx] == -1){
        int t = new_node();
        lc[idx] = t;
      }
      add_line_rec(lc[idx], l, mid, nw);
    } else {
      if(rc[idx] == -1){
        int t = new_node();
        rc[idx] = t;
      }
      add_line_rec(rc[idx], mid+1, r, nw);
    }
  }
  int query(int x){ return query_rec(0, L, R, x); }
  int query_rec(int idx, int l, int r, int x){
    if(idx == -1) return NEG_INF;
    int cur = seg[idx].eval(x);
    if(l == r) return cur;
    int mid = (l + r) >> 1;
    int oth = NEG_INF;
    if(x <= mid){
      if(lc[idx] != -1) oth = query_rec(lc[idx], l, mid, x);
    } else {
      if(rc[idx] != -1) oth = query_rec(rc[idx], mid+1, r, x);
    }
    return max(cur, oth);
  }
};

// Does: Inserts lines y=m*x+b and queries the maximum at an integer x.
// Example: LiChao t; t.init(0, 10); t.add_line(2, 3); // t.query(4) == 11
// Note: Use 64-bit int for the -4e18 sentinel and line arithmetic.
