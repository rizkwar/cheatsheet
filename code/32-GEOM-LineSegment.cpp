// LINES & SEGMENTS
struct Line {
    P p,d;

    // construct from two points
    Line(P a,P b): p(a),d(b-a) {}

    // construct from ax + by = c
    Line(ld a,ld b,ld c): p(b?P(0,c/b):P(c/a,0)),d(b?P(b,-a):P(0,1)) {}

    // signed distance (positive = left of directed line)
    ld sdist(P q) const { return d.cross(q-p); }

    // side: +1 left, -1 right, 0 on line
    int side(P q) const { return sign(sdist(q)); }

    // foot of perpendicular from q
    P foot(P q) const { return p+d*(d.dot(q-p)/d.norm()); }

    // reflect q over this line
    P reflect(P q) const { return q+(foot(q)-q)*2; }

    // point at parameter t
    P at(ld t) const { return p+d*t; }
};

// Distance: point to LINE
ld distPL(P q,Line l) { return fabsl(l.sdist(q))/l.d.abs(); }

// Distance: point to SEGMENT [a,b]
ld distPS(P q,P a,P b) {
    if ((b-a).dot(q-a)<=EPS) return dist(q,a);
    if ((a-b).dot(q-b)<=EPS) return dist(q,b);
    return distPL(q,Line(a,b));
}

// LINE–LINE intersection (returns false if parallel)
bool lineIntersect(Line l1,Line l2,P& out) {
    ld cr=l1.d.cross(l2.d);
    if (sign(cr)==0) return false;
    out=l1.p+l1.d*(l2.d.cross(l1.p-l2.p)/cr);
    return true;
}

// SEGMENT–SEGMENT intersection (proper = no endpoints)
bool segIntersectProper(P a,P b,P c,P d) {
    Line l1(a,b),l2(c,d);
    return l1.side(c)*l1.side(d)<0&&l2.side(a)*l2.side(b)<0;
}

// SEGMENT–SEGMENT intersection (including endpoints / collinear)
bool onSeg(P p,P a,P b) {
    return sign((p-a).cross(b-a))==0&&sign((p-a).dot(b-a))>=0&&sign((p-b).dot(a-b))>=0;
}

bool segIntersect(P a,P b,P c,P d) {
    if (segIntersectProper(a,b,c,d)) return true;
    return onSeg(c,a,b)||onSeg(d,a,b)||onSeg(a,c,d)||onSeg(b,c,d);
}