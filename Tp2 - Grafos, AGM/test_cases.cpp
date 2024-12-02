#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>

#define ll long
#define oo 1000000007
#define pi acos(-1.0)
#define MAXN 100005

using namespace std;

struct node {
    int x, y, l, id, next;
    bool operator <(const node& a) const {
        return l < a.l;
    }
} line[2 * MAXN], Dline[MAXN];

int n, m;
int _next[MAXN], father[MAXN], ans[MAXN], dfn[MAXN], low[MAXN];
int _DfsIndex;

void addline(int x, int y, int l, int id, int m) {
    line[m].next = _next[x];
    _next[x] = m;
    line[m].x = x;
    line[m].y = y;
    line[m].l = l;
    line[m].id = id;
}

int getfather(int x) {
    if (father[x] == x) return x;
    return father[x] = getfather(father[x]);
}

void tarjan(int x, int f) {
    int k, y;
    dfn[x] = low[x] = ++_DfsIndex;

    for (k = _next[x]; k; k = line[k].next) {
        if (line[k].id != f) { // no volver a la arista de origen
            y = line[k].y;
            if (!dfn[y]) {
                tarjan(y, line[k].id);
                low[x] = min(low[x], low[y]);
                if (low[y] > dfn[x]) ans[line[k].id] = 2; // Es un puente
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }
}

void Kruskal() {
    int x = 1;
    _DfsIndex = 0;
    sort(Dline + 1, Dline + 1 + m); // ordenar aristas por longitud

    memset(dfn, 0, sizeof(dfn));
    memset(ans, 0, sizeof(ans));
    memset(_next, 0, sizeof(_next));
    
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }

    while (x <= m) {
        int s = x, e;
        for (e = s; e <= m && Dline[e].l == Dline[s].l; ++e); // encontrar grupo de aristas con la misma longitud
        e--;

        // Añadir aristas que están en el MST potencial
        for (int i = s; i <= e; ++i) {
            int fx = getfather(Dline[i].x);
            int fy = getfather(Dline[i].y);
            if (fx != fy) {
                ans[Dline[i].id] = 1;
                addline(fx, fy, Dline[i].l, Dline[i].id, ++x);
                addline(fy, fx, Dline[i].l, Dline[i].id, ++x);
            }
        }

        // Ejecutar tarjan para detectar puentes y realizar unión de conjuntos
        for (int i = s; i <= e; ++i) {
            int fx = getfather(Dline[i].x);
            int fy = getfather(Dline[i].y);
            if (fx != fy) {
                tarjan(fx, 0);
                father[fx] = fy;
            }
        }

        // Limpiar estructuras temporales
        for (int i = s; i <= e; ++i) {
            int fx = getfather(Dline[i].x);
            int fy = getfather(Dline[i].y);
            dfn[fx] = dfn[fy] = _next[fx] = _next[fy] = 0;
        }
        
        x = e + 1;
    }
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 1; i <= m; ++i) {
            int x, y, l;
            scanf("%d %d %d", &x, &y, &l);
            Dline[i].x = x;
            Dline[i].y = y;
            Dline[i].l = l;
            Dline[i].id = i;
        }

        Kruskal();

        for (int i = 1; i <= m; ++i) {
            if (ans[i] == 0) printf("none\n");
            else if (ans[i] == 1) printf("at least one\n");
            else printf("any\n");
        }
    }

    return 0;
}
