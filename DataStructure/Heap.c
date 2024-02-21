//leetcode 778 水位上升的泳池中游泳
//水永远先没过最低的平台，因此可以用堆维护当前水流周围最低的平台
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 3000
#define MIN(a, b) (cmp((a), (b)) ? (a) : (b))
#define VALID(a, b) ((a) >= 0 && (a) < gridSize && (b) >= 0 && (b) < *gridColSize && !book[a][b])
int **g_pGrid;
typedef struct _Node{
    int x;
    int y;
} Node;
typedef struct _Heap{
    Node arr[MAXN];
    int size;
} Heap;
Heap *HeapCreat(int **grid){
    g_pGrid = grid;
    Heap *obj = (Heap*)malloc(sizeof(Heap));
    obj->size = 0;
    obj->arr[0].x = -1;
    return obj;
}
void swap(Node *a, Node *b){
    Node tmp = *a;
    *a = *b;
    *b = tmp;
}
bool cmp(Node a, Node b){
    if (b.x == -1){
        return false;
    }
    if (g_pGrid[a.x][a.y] < g_pGrid[b.x][b.y]){
        return true;
    }
    return false;
}
void HeapInsert(Heap *obj, Node node){
    int i;
    for (i = ++obj->size; i > 0; i /= 2){
        if (cmp(node, obj->arr[i / 2])){
            swap(&obj->arr[i], &obj->arr[i / 2]);
        }
        else{
            break;
        }
    }
    obj->arr[i] = node;
}
Node *HeapDelete(Heap *obj){
    if (obj->size == 0){
        return NULL;
    }
    int i, nextI;
    for (i = 1; 2 * i + 1 <= obj->size; i = nextI){
        if (cmp(MIN(obj->arr[2 * i], obj->arr[2 * i + 1]), obj->arr[obj->size])){
            nextI = cmp(obj->arr[2 * i], obj->arr[2 * i + 1]) ? 2 * i : 2 * i + 1;
            swap(&obj->arr[i], &obj->arr[nextI]);
        }
        else{
            break;
        }
    }
    swap(&obj->arr[i], &obj->arr[obj->size]);
    return &obj->arr[obj->size--];
}
Node *HeapGetRoot(Heap *obj){
    if (obj->size == 0){
        return NULL;
    }
    return &obj->arr[1];
}
int swimInWater(int** grid, int gridSize, int* gridColSize){
    int waterLevel = 0;         //记录当前水面高度
    Heap *obj = HeapCreat(grid);
    Node lowestLevel = {0}, tmp;
    bool **book = (bool**)malloc(sizeof(bool*) * gridSize);
    for (int i = 0; i < gridSize; i++){
        book[i] = (bool*)malloc(sizeof(bool) * (*gridColSize));
        memset(book[i], 0, sizeof(bool) *(*gridColSize));
    }
    book[0][0] = true;
    HeapInsert(obj, lowestLevel);
    while (lowestLevel.x != gridSize - 1 || lowestLevel.y != *gridColSize - 1){
        while (grid[lowestLevel.x][lowestLevel.y] <= waterLevel){   //当前最低水流边界低于水平面
            lowestLevel = *HeapDelete(obj);                //水流没过当前平台
            if (lowestLevel.x == gridSize - 1 && lowestLevel.y == *gridColSize - 1){
                free(obj); 
                for (int i = 0; i < gridSize; i++){
                    free(book[i]);
                }
                free(book);
                return waterLevel;
            }
            if (VALID(lowestLevel.x + 1, lowestLevel.y)){   //更新新的边界平台
                tmp.x = lowestLevel.x + 1; tmp.y = lowestLevel.y;
                HeapInsert(obj, tmp);
                book[tmp.x][tmp.y] = true;
            }
            if (VALID(lowestLevel.x - 1, lowestLevel.y)){   //更新新的边界平台
                tmp.x = lowestLevel.x - 1; tmp.y = lowestLevel.y;
                HeapInsert(obj, tmp);
                book[tmp.x][tmp.y] = true;
            }
            if (VALID(lowestLevel.x, lowestLevel.y + 1)){   //更新新的边界平台
                tmp.x = lowestLevel.x; tmp.y = lowestLevel.y + 1;
                HeapInsert(obj, tmp);
                book[tmp.x][tmp.y] = true;
            }
            if (VALID(lowestLevel.x, lowestLevel.y - 1)){   //更新新的边界平台
                tmp.x = lowestLevel.x; tmp.y = lowestLevel.y - 1;
                HeapInsert(obj, tmp);
                book[tmp.x][tmp.y] = true;
            }
            lowestLevel = *HeapGetRoot(obj);   //获取最新的最低边界平台
        }
        waterLevel = grid[lowestLevel.x][lowestLevel.y];  //继续下雨，增高水平面
    }
    free(obj); 
    for (int i = 0; i < gridSize; i++){
        free(book[i]);
    }
    free(book);
    return waterLevel;
}
/*
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAXN 10001
typedef struct _Heap{
    int num[MAXN];
    int size;
} Heap;
void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
Heap *HeapCreat(){
    Heap *obj = (Heap*)malloc(sizeof(Heap));
    memset(obj, 0, sizeof(Heap));
    obj->num[0] = MAXN;
    return obj;
}
void HeapInsert(Heap *obj, int val){
    for (int i = ++obj->size; i > 0; i /= 2){
        if (val > obj->num[i / 2]){
            swap(&obj->num[i], &obj->num[i / 2]);
        }
        else{
            obj->num[i] = val;
            break;
        }
    }
}
int HeapDelete(Heap *obj){
    if (obj->size == 0){
        return -1;
    }
    int i, nextI;
    for (i = 1; 2 * i + 1 <= obj->size; i = nextI){
        if (MAX(obj->num[2 * i], obj->num[2 * i + 1]) > obj->num[obj->size]){
            nextI = obj->num[2 * i] > obj->num[2 * i + 1] ? 2 * i : 2 * i + 1;
            swap(&obj->num[i], &obj->num[nextI]);
        }
        else{
            break;
        }
    }
    swap(&obj->num[obj->size], &obj->num[i]);
    return obj->num[obj->size--];
}
int HeapGetRoot(Heap *obj){
    if(obj->size == 0){
        return -1;
    }
    return obj->num[1];
}
*/
