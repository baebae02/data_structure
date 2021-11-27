#include <bits/stdc++.h>
#ifdef TOPOLOGY
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

using namespace std;
 
template<class T, class cmp = less<T> >
class splay_tree {
public:
    class node {
    public:
        node *p, *l, *r;
        T key;
        int cnt;
 
        node() {
            p = l = r = NULL;
            key = T();
        }
 
        node(T k) {
            p = l = r = NULL;
            key = k;
        }
 
        node(T k, node *np) {
            l = r = NULL;
            p = np;
            key = k;
        }
    } *root;
 
    splay_tree() {
        root = NULL;
    }
 
    void update(node *cur) {
        cur->cnt = 1;
        if (cur->l) cur->cnt += cur->l->cnt;
        if (cur->r) cur->cnt += cur->r->cnt;
    }
    void rotate(node *cur) {
        node *p = cur->p;
        if (cur == p->l) {
            if ((p->l = cur->r)) cur->r->p = p;
            cur->r = p;
        } else {
            if ((p->r = cur->l)) cur->l->p = p;
            cur->l = p;
        }
        cur->p = p->p;
        p->p = cur;
        if (cur->p) {
            if (cur->p->l == p) cur->p->l = cur;
            else cur->p->r = cur;
        } else {
            root = cur;
        }
        update(p);
        update(cur);
    }
 
    void splay(node *cur) {
        while (cur->p) {
            node *p = cur->p;
            node *g = p->p;
            if (g) {
                if ((cur == p->l) == (p == g->l)) rotate(p);
                else rotate(cur);
            }
            rotate(cur);
        }
    }
 
    void insert(T key) {
        node *cur = root;
        if (!cur) {
            cur = new node(key);
            root = cur;
            return;
        }
        for (;;) {
            if (cmp()(key, cur->key)) {
                if (cur->l) cur = cur->l;
                else {
                    splay(cur->l = new node(key, cur));
                    return;
                }
            } else if (cmp()(cur->key, key)) {
                if (cur->r) cur = cur->r;
                else {
                    splay(cur->r = new node(key, cur));
                    return;
                }
            } else {
                return;
            }
        }
    }
 
    bool find(T key) {
        node *cur = root;
        if (!cur) return false;
        for (;;) {
            if (cmp()(key, cur->key) {
                if (cur->l) cur = cur->l;
                else break;
            } else if (cmp()(cur->key, key)){
                if (cur->r) cur = cur->r;
                else break;
            } else break;
        }
        splay(cur);
        return cur->key == key;
    }
 
    void erase(T key) {
        if (!find(key)) return;
        node *p = root;
        if (p->l) {
            if (p->r) {
                root = p->l;
                root->p = NULL;
                node *cur = root;
                while (cur->r) cur = cur->r;
                cur->r = p->r;
                p->r->p = cur;
                splay(cur);
                delete p;
            } else {
                root = p->l;
                root->p = NULL;
                delete p;
            }
        } else {
            root = p->r;
            if (root) root->p = NULL;
            delete p;
        }
    }
 
    void nth_element(int k) {
        node *cur = root;
        for (;;) {
            while (cur->l && cur->l->cnt > k) cur = cur->l;
            if (cur->l) k -= cur->l->cnt;
            if (k--) cur = cur->r;
            else break;
           
        }
        splay(cur);
    }
};
 
int main() {
    return 0;
}