#include<iostream>
#include<cmath>
#include <chrono>
using namespace std;
#define SIZE 4          //本程序按照4*4大小的拼图来写
typedef struct node {
    int key;            //记录拼图块上显示的数字
}Puzzle_node;
typedef struct puzzle{
    Puzzle_node *node;  //记录节点
    int size=SIZE;      //拼图的大小
    int Blank_position; //记录空位的位置
}Puzzle;
//拼图关卡(有解)
int info[6][16]={{1,2,3,4,5,6,7,8,9,10,11,12,13,14,-1,15},
                 {5,12,6,4,10,9,-1,1,13,3,14,8,15,11,2,7},
                 {10,13,5,7,3,2,6,11,15,14,1,12,8,4,9,-1},
                 {1,5,14,6,3,-1,2,4,12,13,8,11,7,15,9,10},
                 {-1,4,8,6,3,5,9,2,1,10,12,15,7,13,14,11},
                 {8,10,7,13,5,9,11,12,2,1,15,4,-1,3,6,14}};

//初始化拼图
Puzzle InitPuzzle(Puzzle *P,int grade){
    Puzzle_node *node;      
    node=(Puzzle_node *)malloc(SIZE*SIZE*sizeof(Puzzle_node));
    for (int i = 0; i < 16; i++){
        node[i].key = info[grade][i];
        if (info[grade][i] == -1){
            P->Blank_position = i+1;
        }
    }
    P->node=node;
}
//打印拼图
void PrintPuzzle(Puzzle *P,int grade){
    system("cls");
    int n=P->size;
    cout<<"第"<<grade<<"关"<<endl;
    printf("———————————\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (P->node[i*n+j].key == -1){
                printf("|    ");
            }else if (P->node[i*n+j].key<10){
                printf("| %d  ",P->node[i*n+j].key);
            }else{
                printf("| %d ",P->node[i*n+j].key);
            }
        }
        printf("|\n———————————\n");
    }
}
//移动方块，当且仅当四周有空格时移动才能完成
void MoveNode(Puzzle *P,int i,int j){
    int blank= P->Blank_position;
    int n= P->size;
    int tmp;
    if (i>4 || i<1 || j>4 || j<1){
        printf("\n#error,this block can't move.#\n");
        system("pause");
    }else{
        if ((abs((i-1)*n+j-blank) == n) || (j>1 && (i-1)*n+j-blank==1) || (j<4 && blank-(i-1)*n-j==1)){
            tmp = P->node[blank-1].key;
            P->node[blank-1].key=P->node[(i-1)*n+j-1].key;
            P->node[(i-1)*n+j-1].key=tmp;
            P->Blank_position=(i-1)*n+j;
        }else{
            printf("error,this block can't move.\n");
        }
    }
}
//判断是否已经完成拼图
int Judge(Puzzle *P){
    int n = P->size;
    for (int i = 0; i < n*n-1; i++){
        if (P->node[i].key != i+1){
            return i+1;
        }
    }
    return 0;
}
//主程序
int main(){
    Puzzle P;
    int line,col,grade;
    cout<< "请选择关卡(0~5):\n"<<endl;
    cin>>grade;
    InitPuzzle(&P,grade);
    PrintPuzzle(&P,grade);
    auto start = chrono::steady_clock::now();
    while(Judge(&P)){
        printf("Which block do you want to move?\nInput line(i) and col(j):");
        scanf("%d %d",&line,&col);
        MoveNode(&P,line,col);
        PrintPuzzle(&P,grade);
    }
    auto end = chrono::steady_clock::now();
    printf("Good job!\nYou win the game!\n");
    chrono::duration<double> elapsed_seconds = chrono::duration<double>(end-start);
    cout << "所用时间: " << elapsed_seconds.count() << "s\n";
    system("pause");
    return 0;
}