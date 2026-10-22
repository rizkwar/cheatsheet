#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;

const ld EPS = 1e-9L;
const ld PI = acosl(-1.0L);
const ld INF = 1e18L;

inline int sign(ld x) { return (x > EPS) - (x < -EPS); }
inline bool eq(ld a, ld b) { return sign(a - b) == 0; }
inline ld sq(ld x) { return x * x; }

// 2D POINT / VECTOR

struct P {
    ld x, y;
    P(ld x=0, ld y=0): x(x), y(y) {}

    P operator+(const P& o) const { return {x+o.x,y+o.y}; }
    P operator-(const P& o) const { return {x-o.x,y-o.y}; }
    P operator*(ld t) const { return {x*t,y*t}; }
    P operator/(ld t) const { return {x/t,y/t}; }
    bool operator==(const P& o) const { return eq(x,o.x)&&eq(y,o.y); }

    bool operator<(const P& o) const {
        if (!eq(x,o.x)) return x<o.x;
        return y<o.y;
    }

    ld dot(const P& o) const { return x*o.x+y*o.y; }
    ld cross(const P& o) const { return x*o.y-y*o.x; }
    ld norm() const { return dot(*this); }
    ld abs() const { return sqrtl(norm()); }
    ld arg() const { return atan2l(y,x); }

    P unit() const { return *this/abs(); }
    P perp() const { return {-y,x}; }
    P rot(ld a) const { return {x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)}; }
    P conj() const { return {x,-y}; }

    friend ostream& operator<<(ostream& os,const P& p) {
        return os<<"("<<p.x<<", "<<p.y<<")";
    }
};

ld dist(P a,P b) { return (a-b).abs(); }
ld dist2(P a,P b) { return (a-b).norm(); }

// polar-angle sort around origin (uses atan2, O(n log n))
bool polarCmp(const P& a,const P& b) {
    int ha=(a.y<-EPS||(sign(a.y)==0&&a.x<-EPS));
    int hb=(b.y<-EPS||(sign(b.y)==0&&b.x<-EPS));
    if (ha!=hb) return ha<hb;
    ld cr=a.cross(b);
    if (sign(cr)!=0) return cr>0;
    return a.norm()<b.norm();
}

// Does: Provides 2D point/vector arithmetic, distances, dot and cross products.
// Example: P p(3, 4); ld length = p.abs(); // 5
