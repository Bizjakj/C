#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<time.h>

#include "CuTest.h"

struct edge {
    int weight;
    struct vertex* beg; 
    struct vertex* end;
};

struct vertex {
    int edgeCount, edgeCap, ind;
    struct edge* edgeArray;
};

struct graph {
    int vertexNum, vertexCap;
    struct vertex* vertexArray;
};

void addVertex(struct graph* g) {
    if(g->vertexNum == g->vertexCap) {
        g->vertexCap = g->vertexCap*2;
        if(g->vertexCap == 0) {
            g->vertexCap = 1;
        }
        int a = g->vertexCap;
        struct vertex* temp = (struct vertex*) calloc(a+1,sizeof(struct vertex));
        int i;
        for(i=0; i<g->vertexNum; i++) {
            temp[i].edgeCount = g->vertexArray[i].edgeCount;
            temp[i].edgeCap = g->vertexArray[i].edgeCap;
            temp[i].edgeArray = g->vertexArray[i].edgeArray;
            temp[i].ind = i;
        }
        if(g->vertexArray != NULL) {
            free(g->vertexArray);
        }
        g->vertexArray = temp;
    }
    g->vertexArray[g->vertexNum].edgeCount = 0;
    g->vertexArray[g->vertexNum].edgeCap = 0;
    g->vertexArray[g->vertexNum].edgeArray = NULL;
    
    
    g->vertexArray[g->vertexNum].ind = g->vertexNum;
    g->vertexNum++;

}

struct graph createGraph(int V) {
    struct graph g;
    g.vertexNum = 0;
    g.vertexCap = 0;
    g.vertexArray = NULL;
    int i;
    for(i=0;i<V;i++) {
        addVertex(&g);
    }
    return g;
}

int graphHasVertex(struct graph* g, struct vertex* end) {
    int i;
    for(i=0; i<g->vertexNum; i++) {
        if(&g->vertexArray[i] == end) 
            return 1;
    }
    return 0;
}

int graphHasEdge(struct vertex* start, struct vertex* end) {
    int i;
    for(i=0; i<start->edgeCount; i++) {
        if(start->edgeArray[i].end == end) 
            return 1;
    }
    return 0;
}

void addEdge(struct graph* g, struct vertex* start, struct vertex* end, int weight) {
    int i;
    if(!graphHasVertex(g, end) || graphHasEdge(start, end)) {
        return;
    }
    if(start->edgeCount == start->edgeCap) {
        start->edgeCap = start->edgeCap*2;
        if(start->edgeCap == 0) {
            start->edgeCap = 1;
        }
        struct edge* temp = (struct edge*) calloc(start->edgeCap+1,sizeof(struct edge));
        for(i=0; i<start->edgeCount; i++) {
            temp[i].weight = start->edgeArray[i].weight;
            temp[i].beg = start->edgeArray[i].beg;
            temp[i].end = start->edgeArray[i].end;
        }
        free(start->edgeArray);
        start->edgeArray = temp;
    }
    start->edgeCount++;
    start->edgeArray[i].weight = weight;
    start->edgeArray[i].beg = start;
    start->edgeArray[i].end = end;  
}

void removeEdge(struct edge* e) {
    int i,j=0; 
    for(i=0; i<e->beg->edgeCount; i++) {
        if(j) {
            e->beg->edgeArray[i-1].weight = e->beg->edgeArray[i].weight;
            e->beg->edgeArray[i-1].beg = e->beg->edgeArray[i].beg;
            e->beg->edgeArray[i-1].end = e->beg->edgeArray[i].end;
        }
        if(&(e->beg->edgeArray[i]) == e) {
            j = 1;
        }
    }
    e->beg->edgeCount--;
    e->beg->edgeArray[e->beg->edgeCount].weight = 0;
    e->beg->edgeArray[e->beg->edgeCount].beg = NULL;
    e->beg->edgeArray[e->beg->edgeCount].end = NULL;
}

void copyVertex(struct vertex* dest, struct vertex* orig) {
    dest->edgeCount = orig->edgeCount;
    dest->edgeCap = orig->edgeCap;
    dest->ind = orig->ind;
    int i;
    dest->edgeArray = (struct edge*) calloc(dest->edgeCap+1,sizeof(struct edge));
    for(i=0; i<orig->edgeCount; i++) {
        dest->edgeArray[i] = orig->edgeArray[i];
    }
}

void removeVertex(struct graph* g, struct vertex* v) {
    if(!graphHasVertex(g,v)) {
        return;
    }
    int i,j,c,k=0;
    for(i=0; i<g->vertexNum; i++) {
        if(&(g->vertexArray[i]) != v) {
            for(j=0; j<g->vertexArray[i].edgeCount; j++) {
                if(g->vertexArray[i].edgeArray[j].end == v) {
                    
                    removeEdge(&(g->vertexArray[i].edgeArray[j]));
                    j--;
                }
            }
            if(k) {
                copyVertex(&(g->vertexArray[i-1]), &(g->vertexArray[i]));
                g->vertexArray[i-1].ind--;
            }
        }
        else {
            k = 1;
            free(v->edgeArray);
        }
    }
    g->vertexNum--;
}

void wipeGraph(struct graph* g) {
    int i, j;
    for(i=0; i<g->vertexNum; i++) {
        if(g->vertexArray[i].edgeArray != NULL) {
            free(g->vertexArray[i].edgeArray);
        }
    }
    if(g->vertexArray != NULL) {
        free(g->vertexArray);   
    }
    g->vertexNum = 0;
    g->vertexCap = 0;
    g->vertexArray = NULL;
}

void TestCreateEmptyGraph(CuTest* tc) {
    struct graph g = createGraph(0);
    CuAssertIntEquals(tc, 0, g.vertexNum);
    CuAssertIntEquals(tc, 0, g.vertexCap);
    CuAssertPtrEquals(tc, NULL, g.vertexArray);
}

void TestCreateGraph(CuTest* tc) {
    struct graph g = createGraph(1);
    CuAssertIntEquals(tc, 1, g.vertexNum);
    CuAssertIntEquals(tc, 1, g.vertexCap);
    CuAssertPtrNotNull(tc, g.vertexArray);
    
    struct graph g2 = createGraph(2);
    CuAssertIntEquals(tc, 2, g2.vertexNum);
    CuAssertIntEquals(tc, 2, g2.vertexCap);
    CuAssertPtrNotNull(tc, g2.vertexArray);

    
    struct graph g3 = createGraph(3);
    CuAssertIntEquals(tc, 3, g3.vertexNum);
    CuAssertIntEquals(tc, 4, g3.vertexCap);
    CuAssertPtrNotNull(tc, g3.vertexArray);
    

    struct graph g4 = createGraph(17);
    CuAssertIntEquals(tc, 17, g4.vertexNum);
    CuAssertIntEquals(tc, 32, g4.vertexCap);
    CuAssertPtrNotNull(tc, g4.vertexArray);
    int i;
    for(i=0; i<17; i++) {
        CuAssertIntEquals(tc, i, g4.vertexArray[i].ind);
        CuAssertIntEquals(tc, 0, g4.vertexArray[i].edgeCount);
        CuAssertIntEquals(tc, 0, g4.vertexArray[i].edgeCap);
        CuAssertPtrEquals(tc, NULL, g4.vertexArray[i].edgeArray);
    }
}

void TestRemoveVertex(CuTest* tc) {
    struct graph g = createGraph(16);
    CuAssertIntEquals(tc, 16, g.vertexNum);
    CuAssertIntEquals(tc, 16, g.vertexCap);
    removeVertex(&g, &g.vertexArray[3]);
    CuAssertIntEquals(tc, 15, g.vertexNum);
    CuAssertIntEquals(tc, 16, g.vertexCap);
}

void TestAddEdges(CuTest* tc) {
    struct graph g = createGraph(5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[1], 5);
    CuAssertIntEquals(tc, 1, g.vertexArray[0].edgeCount);
    CuAssertIntEquals(tc, 1, g.vertexArray[0].edgeCap);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[2], 15);
    CuAssertIntEquals(tc, 2, g.vertexArray[0].edgeCount);
    CuAssertIntEquals(tc, 2, g.vertexArray[0].edgeCap);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[3], 25);
    CuAssertIntEquals(tc, 3, g.vertexArray[0].edgeCount);
    CuAssertIntEquals(tc, 4, g.vertexArray[0].edgeCap);
    CuAssertIntEquals(tc, 5, g.vertexArray[0].edgeArray[0].weight);
    CuAssertIntEquals(tc, 15, g.vertexArray[0].edgeArray[1].weight);
    CuAssertIntEquals(tc, 25, g.vertexArray[0].edgeArray[2].weight);
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[0].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[1], g.vertexArray[0].edgeArray[0].end);
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[1].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[2], g.vertexArray[0].edgeArray[1].end); 
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[2].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[3], g.vertexArray[0].edgeArray[2].end);     
}

void TestRemoveEdges(CuTest* tc) {
    struct graph g = createGraph(5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[1], 5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[2], 15);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[3], 25);
    removeEdge(&g.vertexArray[0].edgeArray[1]);
    CuAssertIntEquals(tc, 5, g.vertexArray[0].edgeArray[0].weight);
    CuAssertIntEquals(tc, 25, g.vertexArray[0].edgeArray[1].weight);
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[0].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[1], g.vertexArray[0].edgeArray[0].end);
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[1].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[3], g.vertexArray[0].edgeArray[1].end);
}

void TestRemoveVertexComplex(CuTest* tc) {
    struct graph g = createGraph(5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[1], 5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[2], 15);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[3], 25); 
    removeVertex(&g, &g.vertexArray[1]);
    CuAssertIntEquals(tc, 4, g.vertexNum);
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[0].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[2], g.vertexArray[0].edgeArray[0].end);
    CuAssertPtrEquals(tc, &g.vertexArray[0], g.vertexArray[0].edgeArray[1].beg);
    CuAssertPtrEquals(tc, &g.vertexArray[3], g.vertexArray[0].edgeArray[1].end);

}

void TestWipeGraph(CuTest* tc) {
    struct graph g = createGraph(5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[1], 5);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[2], 15);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[3], 25); 
    wipeGraph(&g);
    CuAssertIntEquals(tc, 0, g.vertexNum);
    CuAssertIntEquals(tc, 0, g.vertexCap);
    CuAssertPtrEquals(tc, NULL, g.vertexArray);

}

CuSuite* GraphsSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestCreateGraph);
    SUITE_ADD_TEST(suite, TestCreateEmptyGraph);
    SUITE_ADD_TEST(suite, TestRemoveVertex);
    SUITE_ADD_TEST(suite, TestAddEdges);
    SUITE_ADD_TEST(suite, TestRemoveEdges);
    SUITE_ADD_TEST(suite, TestWipeGraph);
    SUITE_ADD_TEST(suite, TestRemoveVertexComplex);
    return suite;
}


/*
int main() {
    struct graph g = createGraph(3);
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[2], 12);
    printf("koc\n");
    addEdge(&g, &g.vertexArray[0], &g.vertexArray[1], 2);
    printf("%d %d %d\n", g.vertexNum, g.vertexArray[0].edgeArray[0].weight, g.vertexArray[0].edgeCount);
    removeEdge(&g.vertexArray[0].edgeArray[0]);
    printf("%d %d %d\n", g.vertexNum, g.vertexArray[0].edgeArray[0].weight, g.vertexArray[0].edgeCount);
}
*/