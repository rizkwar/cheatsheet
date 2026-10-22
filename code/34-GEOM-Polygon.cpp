// POLYGON
using Poly=vector<P>;

// Signed area (positive if CCW)
ld signedArea(const Poly& v) {
    ld res=0;
    int n=v.size();
    for (int i=0;i<n;i++) res+=v[i].cross(v[(i+1)%n]);
    return res/2;
}

ld area(const Poly& v) { return fabsl(signedArea(v)); }
bool isCCW(const Poly& v) { return signedArea(v)>EPS; }

// Centroid
P centroid(const Poly& v) {
    P res(0,0);
    ld sa=0;
    int n=v.size();

    for (int i=0;i<n;i++) {
        ld cr=v[i].cross(v[(i+1)%n]);
        sa+=cr;
        res=res+(v[i]+v[(i+1)%n])*cr;
    }
    return res/(3*sa);
}

// Point in polygon: +1 inside, 0 on boundary, -1 outside (O(n))
int pip(P q,const Poly& v) {
    int n=v.size(),wind=0;

    for (int i=0;i<n;i++) {
        P a=v[i],b=v[(i+1)%n];
        if (onSeg(q,a,b)) return 0;

        int s=sign((b-a).cross(q-a));
        if (a.y<=q.y) {
            if (b.y>q.y&&s>0) ++wind;
        } else {
            if (b.y<=q.y&&s<0) --wind;
        }
    }

    return wind?1:-1;
}

// Convex hull (Andrew's monotone chain, O(n log n))
// Returns CCW hull (without collinear points on edges by default)
Poly convexHull(vector<P> pts,bool keepCollinear=false) {
    int n=pts.size();
    sort(pts.begin(),pts.end());
    pts.erase(unique(pts.begin(),pts.end()),pts.end());
    n=pts.size();

    if (n<2) return pts;

    Poly hull;

    auto bad=[&](P a,P b,P c) {
        ld cr=(b-a).cross(c-a);
        return keepCollinear?cr<-EPS:cr<=EPS;
    };

    // lower
    for (int i=0;i<n;i++) {
        while (hull.size()>=2&&bad(hull[hull.size()-2],hull.back(),pts[i]))
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    // upper
    int lo=hull.size();
    for (int i=n-2;i>=0;i--) {
        while ((int)hull.size()>lo&&bad(hull[hull.size()-2],hull.back(),pts[i]))
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    hull.pop_back();
    return hull;
}

// Is polygon convex? (assumes CCW, no repeated points)
bool isConvex(const Poly& v) {
    int n=v.size();
    for (int i=0;i<n;i++)
        if (sign((v[(i+1)%n]-v[i]).cross(v[(i+2)%n]-v[(i+1)%n]))<0)
            return false;
    return true;
}

// Point in CONVEX polygon (O(log n), polygon must be CCW)
// returns +1 inside, 0 boundary, -1 outside
int pipConvex(P q,const Poly& v) {
    int n=v.size();

    if (n==1) return q==v[0]?0:-1;
    if (n==2) return onSeg(q,v[0],v[1])?0:-1;

    P o=v[0];

    if (sign((v[1]-o).cross(q-o))<0) return -1;
    if (sign((v[n-1]-o).cross(q-o))>0) return -1;

    int lo=1,hi=n-1;

    while (lo+1<hi) {
        int mid=(lo+hi)/2;
        if (sign((v[mid]-o).cross(q-o))>=0) lo=mid;
        else hi=mid;
    }

    ld cr=(v[lo+1]-v[lo]).cross(q-v[lo]);
    if (sign(cr)<0) return -1;

    if (sign(cr)==0||q==o||onSeg(q,o,v[1])||onSeg(q,o,v[n-1]))
        return 0;

    return 1;
}

// Polygon clipping by half-plane {left of directed line a→b} (Sutherland-Hodgman)
Poly clipPolygon(Poly poly,P a,P b) {
    Poly res;
    int n=poly.size();

    for (int i=0;i<n;i++) {
        P c=poly[i],d=poly[(i+1)%n];
        bool ic=sign((b-a).cross(c-a))>=0;
        bool id=sign((b-a).cross(d-a))>=0;

        if (ic) res.push_back(c);

        if (ic!=id) {
            P inter;
            lineIntersect(Line(a,b),Line(c,d),inter);
            res.push_back(inter);
        }
    }

    return res;
}

// Polygon–circle intersection area
ld sectorArea2(P a,P b,ld r) {
    return .5L*r*r*atan2l(a.cross(b),a.dot(b));
}

ld polyCircleArea(const Poly& poly,Circle C) {
    int n=poly.size();
    ld res=0;

    for (int i=0;i<n;i++) {
        P a=poly[i]-C.c;
        P b=poly[(i+1)%n]-C.c;
        ld r=C.r;

        P p1,p2;
        int cnt=lineCircle(Line(a,b),Circle(P(),r),p1,p2);

        vector<P> pts={a};

        if (cnt==2) {
            auto onS=[&](P x) {
                return sign((b-a).dot(x-a))>=0&&sign((b-a).dot(b-x))>=0;
            };

            if (onS(p1)) pts.push_back(p1);
            if (onS(p2)) pts.push_back(p2);

            if (pts.size()==3&&(pts[1]-a).norm()>(pts[2]-a).norm())
                swap(pts[1],pts[2]);
        }

        pts.push_back(b);

        for (int j=0;j+1<(int)pts.size();j++) {
            P u=pts[j],v=pts[j+1],mid=(u+v)/2;

            if (mid.norm()<=r*r)
                res+=u.cross(v)/2;
            else
                res+=sectorArea2(u,v,r);
        }
    }

    return fabsl(res);
}

// Diameter of convex polygon (rotating calipers, O(n))
ld convexDiameter(const Poly& h) {
    int n=h.size();
    if (n==1) return 0;
    if (n==2) return dist(h[0],h[1]);

    ld res=0;

    for (int i=0,j=1;i<n;i++) {
        while ((h[(i+1)%n]-h[i]).cross(h[(j+1)%n]-h[j])>0)
            j=(j+1)%n;

        res=max(res,max(dist(h[i],h[j]),dist(h[(i+1)%n],h[j])));
    }

    return res;
}

// Minkowski sum of two CCW convex polygons
Poly minkowski(Poly P1,Poly P2) {
    // rotate so first vertex is bottom-left
    auto reorder=[](Poly& v) {
        int idx=min_element(v.begin(),v.end())-v.begin();
        rotate(v.begin(),v.begin()+idx,v.end());
    };

    reorder(P1);
    reorder(P2);

    P1.push_back(P1[0]);
    P1.push_back(P1[1]);
    P2.push_back(P2[0]);
    P2.push_back(P2[1]);

    Poly res;
    int i=0,j=0,n=P1.size()-2,m=P2.size()-2;

    while (i<n||j<m) {
        res.push_back(P1[i]+P2[j]);

        P e1=P1[i+1]-P1[i],e2=P2[j+1]-P2[j];
        ld cr=e1.cross(e2);

        if (cr>EPS) i++;
        else if (cr<-EPS) j++;
        else { i++; j++; }
    }

    return res;
}

// Perimeter of polygon
ld perimeter(const Poly& v) {
    ld res=0;
    int n=v.size();

    for (int i=0;i<n;i++)
        res+=dist(v[i],v[(i+1)%n]);

    return res;
}

// Does: Provides polygon areas, hulls, point tests, clipping and more.
// Example: Poly p = {P(0,0), P(2,0), P(0,2)}; ld a = area(p); // 2
// Requires geometry helpers from 31-33.
