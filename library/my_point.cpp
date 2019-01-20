#define point complex<ll>
#define line pair<point, point>

ll cross(const point &a, const point &b) {
    return imag(conj(a) * b);
}
inline bool inside(const point &p, const line &l) {
    ll x1 = l.first.real(), x2 = l.second.real();
    ll y1 = l.first.imag(), y2 = l.second.imag();
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    return (x1 <= p.real() && p.real() <= x2 && y1 <= p.imag() && p.imag() <= y2);
}
pair<bool, point> intersect(const line &l1, const line &l2) {
    point a = l1.first, b = l1.second, p = l2.first, q = l2.second;
    ll d1 = cross(p - a, b - a);
    ll d2 = cross(q - a, b - a);
    point s = (d1 * q - d2 * p);
    if ((d1 == d2) || s.real() % abs(d1 - d2) || s.imag() % abs(d1 - d2))
        return make_pair(false, point());
    s /= (d1 - d2);
    return make_pair((inside(s, l1) && inside(s, l2)), s);
}
