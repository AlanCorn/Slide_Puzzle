#include<iostream>
#include<cmath>
#include <chrono>
using namespace std;
#define SIZE 4          //��������4*4��С��ƴͼ��д
typedef struct node {
    int key;            //��¼ƴͼ������ʾ������
}Puzzle_node;
typedef struct puzzle{
    Puzzle_node *node;  //��¼�ڵ�
    int size=SIZE;      //ƴͼ�Ĵ�С
    int Blank_position; //��¼��λ��λ��
}Puzzle;
//ƴͼ�ؿ�(�н�)
int info[6][16]={{1,2,3,4,5,6,7,8,9,10,11,12,13,14,-1,15},
                 {5,12,6,4,10,9,-1,1,13,3,14,8,15,11,2,7},
                 {10,13,5,7,3,2,6,11,15,14,1,12,8,4,9,-1},
                 {1,5,14,6,3,-1,2,4,12,13,8,11,7,15,9,10},
                 {-1,4,8,6,3,5,9,2,1,10,12,15,7,13,14,11},
                 {8,10,7,13,5,9,11,12,2,1,15,4,-1,3,6,14}};

//��ʼ��ƴͼ
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
//��ӡƴͼ
void PrintPuzzle(Puzzle *P,int grade){
    system("cls");
    int n=P->size;
    cout<<"��"<<grade<<"��"<<endl;
    printf("����������������������\n");
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
        printf("|\n����������������������\n");
    }
}
//�ƶ����飬���ҽ��������пո�ʱ�ƶ��������
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
//�ж��Ƿ��Ѿ����ƴͼ
int Judge(Puzzle *P){
    int n = P->size;
    for (int i = 0; i < n*n-1; i++){
        if (P->node[i].key != i+1){
            return i+1;
        }
    }
    return 0;
}
//������
int main(){
    Puzzle P;
    int line,col,grade;
    cout<< "��ѡ��ؿ�(0~5):\n"<<endl;
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
    cout << "����ʱ��: " << elapsed_seconds.count() << "s\n";
    system("pause");
    return 0;
}