
// CIRCLE
struct Circle {
    P c; ld r;
    Circle(P c,ld r): c(c),r(r) {}
};

// point–circle relation: -1 inside, 0 on, +1 outside
int ptCircle(P p,Circle C) { return sign(dist(p,C.c)-C.r); }

// tangent lines from external point p to circle C
// returns 0 (inside), 1 (tangent), or 2 points of tangency
int tangentPoints(P p,Circle C,P& t1,P& t2) {
    ld d2=dist2(p,C.c),r2=sq(C.r);
    if (sign(d2-r2)<0) return 0;
    if (sign(d2-r2)==0) { t1=t2=Line(p,C.c).foot(p); return 1; }
    ld a=acosl(C.r/sqrtl(d2));
    P u=(C.c-p).unit();
    t1=p+u.rot(a)*sqrtl(d2-r2);
    t2=p+u.rot(-a)*sqrtl(d2-r2);
    return 2;
}

// LINE–CIRCLE intersections (0, 1, or 2 points)
int lineCircle(Line l,Circle C,P& p1,P& p2) {
    P f=l.foot(C.c);
    ld d2=dist2(f,C.c),r2=sq(C.r);
    int s=sign(d2-r2);
    if (s>0) return 0;
    if (s==0) { p1=p2=f; return 1; }
    ld dt=sqrtl(r2-d2)/l.d.abs();
    p1=f+l.d*dt;
    p2=f-l.d*dt;
    return 2;
}

// CIRCLE–CIRCLE intersections (0,1,2 points; also handles containment)
int circleCircle(Circle A,Circle B,P& p1,P& p2) {
    ld d=dist(A.c,B.c);
    if (sign(d-(A.r+B.r))>0) return 0;
    if (sign(d-fabsl(A.r-B.r))<0) return 0;
    if (sign(d)==0) return 0;

    ld cos_a=(sq(d)+sq(A.r)-sq(B.r))/(2*d*A.r);
    cos_a=max((ld)-1,min((ld)1,cos_a));
    ld a=acosl(cos_a);
    P u=(B.c-A.c).unit();

    p1=A.c+u.rot(a)*A.r;
    p2=A.c+u.rot(-a)*A.r;
    return sign(a)==0?1:2;
}

// CIRCLE–CIRCLE common tangent lines (0..4)
// external: 2 lines, internal: 2 lines (cross), total depends on config
vector<Line> commonTangents(Circle A,Circle B) {
    vector<Line> res;
    ld d=dist(A.c,B.c);

    for (int s:{-1,1}) {
        ld rr=A.r-s*B.r;
        if (sq(rr)>sq(d)+EPS) continue;

        ld a=(sq(d)>sq(rr))?acosl(-rr/d):0;
        P u=(B.c-A.c).unit();

        for (int t:{-1,1}) {
            P n=u.rot(t*a);
            P p=A.c+n*A.r;
            P q=B.c+n*(s*B.r);
            res.emplace_back(p,q);
        }
    }
    return res;
}

// Arc length, sector area, segment area
ld arcLen(Circle C,ld angle) { return C.r*fabsl(angle); }
ld sectorArea(Circle C,ld angle) { return .5L*sq(C.r)*fabsl(angle); }

ld segArea(Circle C,ld angle) {
    angle=fabsl(angle);
    return .5L*sq(C.r)*(angle-sinl(angle));
}

// Area of intersection of two circles
ld circleIntersectArea(Circle A,Circle B) {
    ld d=dist(A.c,B.c);
    if (sign(d-(A.r+B.r))>=0) return 0;

    if (sign(d-fabsl(A.r-B.r))<=0) {
        ld r=min(A.r,B.r);
        return PI*sq(r);
    }

    auto ang=[&](ld r,ld other,ld dd) {
        return 2*acosl((sq(dd)+sq(r)-sq(other))/(2*r*dd));
    };

    ld a1=ang(A.r,B.r,d),a2=ang(B.r,A.r,d);
    return segArea(A,a1)+segArea(B,a2);
}

vector<P> lineCircleIntersect(Circle c,Line l) {
    P v=c.c-l.p;
    ld t=v.dot(l.d)/l.d.norm();
    P foot=l.p+l.d*t;
    ld h2=dist2(foot,c.c),r2=sq(c.r);

    if (sign(h2-r2)>0) return {};
    if (sign(h2-r2)==0) return {foot};

    ld h_dist=sqrtl(r2-h2);
    P offset=l.d.unit()*h_dist;
    return {foot-offset,foot+offset};
}

ld PtoAngle(Circle c,P p) {
    ld angle=atan2l(p.y-c.c.y,p.x-c.c.x);
    if (angle<0) angle+=2*PI;
    return angle;
}

ld segArea(Circle c,P p1,P p2) {
    ld a1=PtoAngle(c,p1),a2=PtoAngle(c,p2);
    ld theta=fabsl(a1-a2);
    if (theta>PI) theta=2*PI-theta;
    return .5L*sq(c.r)*(theta-sinl(theta));
}
