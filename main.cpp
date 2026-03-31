#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

// Segment Tree with Lazy Propagation for Range Update and Range Minimum Query
class SegmentTree {
private:
    int tree[MAXN * 4];
    int lazy[MAXN * 4];
    int n;

    void build(int node, int start, int end, int k) {
        lazy[node] = 0;
        if (start == end) {
            tree[node] = k;
        } else {
            int mid = (start + end) / 2;
            build(node * 2, start, mid, k);
            build(node * 2 + 1, mid + 1, end, k);
            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    void push(int node) {
        if (lazy[node] != 0) {
            tree[node * 2] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, int val) {
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            tree[node] += val;
            lazy[node] += val;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, val);
        update(node * 2 + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 2000000000; // Return a large value
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        push(node);
        int mid = (start + end) / 2;
        int p1 = query(node * 2, start, mid, l, r);
        int p2 = query(node * 2 + 1, mid + 1, end, l, r);
        return min(p1, p2);
    }

public:
    void init(int size, int k) {
        n = size;
        build(1, 1, n, k);
    }

    void update(int l, int r, int val) {
        update(1, 1, n, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

SegmentTree segTree;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);

    // Initialize segment tree with k seats for each segment
    segTree.init(x - 1, k);

    // Process each order
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);

        // Find minimum available seats in range [u, v-1]
        int min_seats = segTree.query(u, v - 1);

        // Check if order can be fulfilled
        if (min_seats >= n) {
            // Fulfill the order - range update
            segTree.update(u, v - 1, -n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}
