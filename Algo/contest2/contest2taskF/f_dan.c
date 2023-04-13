#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#define _NUMBER_ 1000000000

#define INF 9223372036854775806L

typedef long long ll;

struct _Node {
    ll key;
    ll priority;
    ll count;
    struct _Node * l;
    struct _Node * r;
    //node(int k) { key = k; left = right = 0; height = 1; } 
};

typedef struct _Node node;

ll getCount(node * t) {
    return t ? t -> count : 0;
}

void updateCount(node * t) {
    if (t)
        t -> count = getCount(t -> l) + getCount(t -> r) + t -> key;
}

ll prev(node * t, ll k) {
    node * now = NULL;
    while (t != NULL) {
        if (t -> key < k) {
            now = t;
            t = t -> r;
        } else {
            t = t -> l;
        }
    }
    if (now == NULL) {
        return INF;
    }
    return now -> key;
}

ll next(node * t, ll k) {
    node * now = NULL;
    while (t != NULL) {
        if (t -> key > k) {
            now = t;
            t = t -> l;
        } else {
            t = t -> r;
        }
    }
    if (now == NULL) {
        return INF;
    }
    return now -> key;
}

void split(node * t, ll key, node ** l, node ** r) {
    if (!t) {
        * l = * r = NULL;
        return;
    } else if (t -> key > key) {
        split(t -> l, key, l, & (t -> l));
        * r = t;
    } else {
        split(t -> r, key, & (t -> r), r);
        * l = t;
    }
    updateCount(t);
}

void insert(node ** t, node * it) {
    if (! * t)
        *
        t = it;
    else if (it -> priority > ( ** t).priority) {
        split( * t, it -> key, & (it -> l), & (it -> r));
        * t = it;
    } else {
        insert(it -> key < ( ** t).key ? & (( ** t).l) : & (( ** t).r), it);
    }
    updateCount( * t);
}

void merge(node ** t, node * l, node * r) {
    if (!l || !r)
        *
        t = l ? l : r;
    else if (l -> priority > r -> priority) {
        merge( & (l -> r), l -> r, r);
        * t = l;
    } else {
        merge( & (r -> l), l, r -> l);
        * t = r;
    }
    updateCount( * t);
}

void erase(node ** t, ll key) {
    if (( ** t).key == key)
        merge(t, (( ** t).l), ( ** t).r);
    else
        erase(key < ( ** t).key ? & (( ** t).l) : & (( ** t).r), key);
    updateCount( * t);
}

ll getStatistic(node * t, ll k) {
    if (!t)
        return INF;
    else if (getCount(t -> r) == k - 1)
        return t -> key;
    else if (getCount(t -> r) >= k)
        return getStatistic(t -> r, k);
    else
        return getStatistic(t -> l, k - getCount(t -> r) - 1);
}

int find(node * p, ll k) {
    int b = 1;
    if (!p) return 0;
    if (k == p -> key) {
        return 1;
    }
    if (k < p -> key)
        b = find(p -> l, k);
    else if (k > p -> key)
        b = find(p -> r, k);
    return b;
}

ll sum(node * p, ll l, ll r) {
    node * less;
    node * greater;
    node * equal;
    less = NULL;
    equal = NULL;
    greater = NULL;
    split(p, l - 1, & less, & greater);
    split(greater, r, & equal, & greater);
    ll res = getCount(equal);
    node * sd = NULL;
    merge( & sd, less, equal);
    merge( & p, sd, greater);
    return res;
}

int main() {
    ll n;
    if (scanf("%lld", & n) == 1) {

    }
    ll flag = 0;
    ll y = 0;
    node * p = NULL;
    for (int i = 0; i < n; i++) {
        char requests[256];
        if (scanf("%s", requests) == 1) {

        }
        if (!strcmp(requests, "+")) {

            ll m;
            if (scanf("%lld", & m)) {

            }
            if (find(p, m) == 1 && flag == 0) {
                flag = 0;
                continue;
            }
            if (flag == 1) {
                ll asdas = (m + y) % _NUMBER_;
                if (find(p, asdas) == 1) {
                    flag = 0;
                    continue;
                }
                node * sad = malloc(sizeof(node));
                sad -> count = asdas;
                sad -> key = asdas;
                sad -> l = NULL;
                sad -> r = NULL;
                sad -> priority = rand() % 1000000;
                insert( & p, sad);
            } else {
                node * sad = malloc(sizeof(node));
                sad -> count = m;
                sad -> key = m;
                sad -> l = NULL;
                sad -> r = NULL;
                sad -> priority = rand() % 1000000;
                insert( & p, sad);
            }
            flag = 0;
        }
        if (!strcmp(requests, "?")) {
            flag = 1;
            ll l;
            ll r;
            if (scanf("%lld%lld", & l, & r)) {

            }
            y = sum(p, l, r);
            printf("%lld\n", y);
        }
    }
}