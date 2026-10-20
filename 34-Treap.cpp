struct Node {
  int key, id, sz;
  unsigned pri;
  Node *l, *r;

  Node(int key, int id = 0)
      : key(key), id(id), sz(1), pri(rng()), l(0), r(0) {}

  static unsigned rng() {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return rng();
  }
};

int sz(Node *t) {
  return t ? t->sz : 0;
}

void pull(Node *t) {
  if(t)
    t->sz = 1 + sz(t->l) + sz(t->r);
}

bool leq(Node *t, int key, int id) {
  return t->key < key || (t->key == key && t->id < id);
}

void split(Node *t, int key, int id, Node *&a, Node *&b) {
  if(!t)
    return a = b = 0, void();

  if(leq(t, key, id)) {
    split(t->r, key, id, t->r, b);
    a = t;
  } else {
    split(t->l, key, id, a, t->l);
    b = t;
  }

  pull(t);
}

Node* merge(Node *a, Node *b) {
  if(!a || !b)
    return a ? a : b;

  if(a->pri > b->pri) {
    a->r = merge(a->r, b);
    pull(a);
    return a;
  }

  b->l = merge(a, b->l);
  pull(b);
  return b;
}

void insert(Node *&t, Node *x) {
  if(!t)
    return t = x, void();

  if(x->pri > t->pri) {
    split(t, x->key, x->id, x->l, x->r);
    t = x;
  } else if(leq(x, t->key, t->id)) {
    insert(t->l, x);
  } else {
    insert(t->r, x);
  }

  pull(t);
}

void erase(Node *&t, int key, int id) {
  if(t->key == key && t->id == id) {
    t = merge(t->l, t->r);
    return;
  }

  if(leq(t, key, id))
    erase(t->r, key, id);
  else
    erase(t->l, key, id);

  pull(t);
}