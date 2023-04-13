#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define ll long long

typedef struct Node {

    int key;
    int y;
    struct Node * left;
    struct Node * right;
    int si_tr;
    ll int sum;

}
Node;

Node * creat_node(int key, int y) {

    Node * tr = (Node * ) malloc(sizeof(Node));
    tr -> key = key;
    tr -> y = y;
    tr -> left = NULL;
    tr -> right = NULL;
    tr -> si_tr = 1;
    tr -> sum = key;

    return tr;

}

Node * find_key(Node * tr, int x) {

    if (tr == NULL) {

        return NULL;

    }

    if (x == tr -> key) {

        return tr;

    }

    if (x < tr -> key) {

        return find_key(tr -> left, x);

    } else {

        return find_key(tr -> right, x);

    }

}

void print_key(Node * node) {

    if (node == NULL) printf("0");
    else printf("%d", node -> key);

}

int get_si_tr(Node * tr) {

    if (tr == NULL) {

        return 0;

    }

    return tr -> si_tr;

}

ll int get_sum_tr(Node * tr) {

    if (tr == NULL) {

        return 0;

    }

    return tr -> sum;

}

void upd(Node ** tr) {
    if ( * tr == NULL) {

        return;

    }

    ( * tr) -> si_tr = get_si_tr(( * tr) -> left) + get_si_tr(( * tr) -> right) + 1;
    ( * tr) -> sum = get_sum_tr(( * tr) -> left) + get_sum_tr(( * tr) -> right) + ( * tr) -> key;
}

Node * merge(Node * l, Node * r) {

    if (l == NULL) {

        return r;

    }

    if (r == NULL) {

        return l;

    }

    if (l -> y > r -> y) {

        l -> right = merge(l -> right, r);
        upd( & l);
        return l;

    } else {

        r -> left = merge(l, r -> left);
        upd( & r);
        return r;

    }

}

void split(Node * tr, int x, Node ** f, Node ** s) {

    if (tr == NULL) {

        * f = NULL;
        * s = NULL;
        upd(f);
        upd(s);
        return;

    }

    if (x < tr -> key) {

        split(tr -> left, x, f, s);
        tr -> left = * s;
        * s = tr;
        upd(f);
        upd(s);
        return;

    } else {

        split(tr -> right, x, f, s);
        tr -> right = * f;
        * f = tr;
        upd(f);
        upd(s);
        return;
    }

}

Node * insert(Node * tr, int x) {

    if (find_key(tr, x) != NULL) {

        return tr;

    }

    Node * f = NULL;
    Node * s = NULL;
    split(tr, x, & f, & s);

    Node * node_x = creat_node(x, rand() % 100000);
    tr = merge(merge(f, node_x), s);

    return tr;

}

Node * del(Node * tr, int x) {

    Node * f = NULL;
    Node * s = NULL;

    split(tr, x, & f, & s);
    Node * node_x = NULL;
    split(f, x - 1, & f, & node_x);
    tr = merge(f, s);

    return tr;

}

Node * k_stat(Node * tr, int no) {

    if (get_si_tr(tr) < no || no <= 0) {

        return NULL;

    }

    if (get_si_tr(tr -> left) + 1 == no) {

        return tr;

    }

    if (get_si_tr(tr -> left) + 1 < no) {

        return k_stat(tr -> right, no - (get_si_tr(tr -> left) + 1));

    } else {

        return k_stat(tr -> left, no);

    }

}

int k_stat_back(Node * tr, int x, int cur_stat) {
    if (tr == NULL) {

        return -1;

    }
    if (tr -> key == x) {

        return get_si_tr(tr -> left + 1);

    }

    if (x < tr -> key) {

        return k_stat_back(tr -> left, x, cur_stat);

    } else {

        return k_stat_back(tr -> right, x, cur_stat + get_si_tr(tr -> left) + 1);

    }

}

Node * next(Node * tr, int x) {

    Node * cur = tr;
    Node * suc = NULL;

    while (cur != NULL) {

        if (cur -> key > x) {

            suc = cur;
            cur = cur -> left;

        } else {

            cur = cur -> right;

        }

    }

    return suc;

}

Node * prev(Node * tr, int x) {

    Node * cur = tr;
    Node * suc = NULL;

    while (cur != NULL) {

        if (cur -> key < x) {

            suc = cur;
            cur = cur -> right;

        } else {

            cur = cur -> left;

        }

    }

    return suc;

}

int main() {

    //int a[1000000] = {0};
    //int* b = (int*) calloc(2147483648, sizeof(int));
    //int *b = (int*) calloc(1048576, sizeof(int));
    //int *b = (int*) calloc(67108864, sizeof(int));

    Node * tr = NULL;

    int n = 0;
    char c = '0';
    scanf("%d%c", & n, & c);
    ll int l = 0;
    ll int r = 0;
    int x = 0;
    char pr_c = '+';
    ll int pr_y = 0;
    for (int i = 0; i < n; i++) {

        scanf("%c", & c);
        if (c == '+') {

            scanf("%d", & x);
            if (pr_c != '+') {

                x = (int)(((ll int) x + pr_y) % (ll int) 1e9);

            }

            tr = insert(tr, x);
            //set(x, x, 0, 0,  1073741823, b);

            //set(x, x, 0, 0, 1048575, b);
            //set(x, x, 0, 0, 67108863, b);
            pr_c = '+';

        }
        if (c == '?') {

            scanf("%lld %lld", & l, & r);
            Node * f = NULL;
            Node * ml = NULL;
            Node * mr = NULL;
            Node * s = NULL;
            split(tr, l - 1, & f, & s);
            split(s, r, & ml, & mr);
            pr_y = get_sum_tr(ml);
            tr = merge(f, merge(ml, mr));
            //pr_y = sum(l, r + 1, 0, 0,  1073741823, b);
            //pr_y = sum(l, r + 1, 0, 0,  1048575, b);
            //pr_y = sum(l, r + 1, 0, 0,  67108863, b);
            printf("%lld\n", pr_y);
            pr_c = '?';

        }
        scanf("%c", & c);

    }

    //free(b);

    return 0;

}