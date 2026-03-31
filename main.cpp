#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;
int capacity[MAXN]; // capacity[i] represents available seats for segment i to i+1

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);

    // Initialize all segments with k seats
    for (int i = 1; i < x; i++) {
        capacity[i] = k;
    }

    // Process each order
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);

        // Find minimum available seats in range [u, v-1]
        int min_seats = k + 1;
        for (int j = u; j < v; j++) {
            min_seats = min(min_seats, capacity[j]);
        }

        // Check if order can be fulfilled
        if (min_seats >= n) {
            // Fulfill the order
            for (int j = u; j < v; j++) {
                capacity[j] -= n;
            }
            printf("T\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}
