#include <stdio.h> 
#include <stdlib.h>

typedef struct Node { //연결리스트의 노드 구조체
    double data; //숫자를 입력받는 변수
    struct Node* link; //다음 노드 링크
} listNode;

typedef struct Head { //헤드 노드 구조체
    struct Node* first; //첫 번째 노드를 가리키는 링크
} headNode;

void arrayPrint(headNode** head); //연결리스트를 출력하는 함수
void sort(headNode** head); //연결리스트를 정렬하는 함수
void readFile(headNode** head); //Sample Data.txt 파일에서 숫자만 읽어서 연결리스트에 입력하는 함수

int main() {
    //printf("2020039027 김주훈\n"); //학번 이름
    headNode* h = (headNode*)malloc(sizeof(headNode)); //첫 노드를 가리킬 헤드노드 생성
    h->first = NULL; //첫 노드 NULL로 초기화
    readFile(&h); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 생성
    //arrayPrint(&h); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 출력
    sort(&h); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 정렬
    //arrayPrint(&h); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 출력
    listNode* tmp1 = h->first; //free 
    listNode* tmp2 = tmp1;
    while(tmp1 != NULL) {
        tmp1 = tmp1->link;
        free(tmp2);
        tmp2 = tmp1;
    }
    free(h);
}

void readFile(headNode** head) { //헤드노드의 주소를 받아서 파일의 숫자로 연결리스트를 만드는 함수
    //printf("\n파일 읽기 시작\n\n...");
    FILE *fp = fopen("Sample Data.txt", "r"); //fopen으로 파일을 열음
    if(fp == NULL) { //파일이 안열였을 때
        printf("File error\n");
    }
    else {
        char c; //"," 를 저장할 변수
        listNode* tmp = (listNode*)malloc(sizeof(listNode)); //노드 이동에 필요한 노드
        while(!(feof(fp))) { //파일이 끝날 때 까지 반복
            listNode* newnode = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
            newnode->link = NULL; //링크는 NULL로 초기화
            fscanf(fp, "%lf", &(newnode->data)); //새로운 노드에 숫자 입력
            fscanf(fp, "%c", &c); //"," 를 빼줌
            if((*head)->first == NULL) { //첫 번째 노드가 없을 때
                (*head)->first = newnode; //첫 번째 노드 삽입
            }
            else { //첫 번째 노드가 있을 때
                tmp = (*head)->first; //tmp에 첫 번째 노드 입력
                while(tmp->link != NULL) { //링크가 없을 때까지 반복
                    tmp = tmp->link; //다음 노드로 이동
                }
                tmp->link = newnode; //가장 끝 노드에 새로운 노드를 링크시킴
            }
        }
    }
    //printf("\n\n파일 읽기 끝\n");

}

void arrayPrint(headNode** head) { //헤드노드의 주소를 받아서 연결리스트를 출력하는 함수
    printf("\n배열 출력\n\n");
    listNode* tmp = (listNode*)malloc(sizeof(listNode)); //노드 이동에 필요한 노드 생성
    tmp = (*head)->first; //tmp에 첫 번째 노드 입력
    while(tmp != NULL) { //tmp가 NULL이 될 때까지 반복
        printf("%.0lf ", tmp->data); //숫자 출력
        tmp = tmp->link; //다음 노드로 이동
    }
    printf("\n\n");
}

void sort(headNode** head) { //헤드노드의 주소를 받아 오름차순으로 버블정렬하는 함수 
    //printf("\n정렬 시작\n\n...");
    listNode* tmp1, * tmp2; //노드 이동할 때 사용할 노드 
    double num; //숫자 바꿀 때 사용할 버퍼 
    for(tmp1=(*head)->first; tmp1!=NULL; tmp1=tmp1->link) { //tmp1이 먼저  다음노드로 이동 
        for(tmp2=tmp1; tmp2!=NULL; tmp2=tmp2->link) { //tmp2가 뒤따라감 
            if(tmp2->data < tmp1->data) { //tmp2의 값이 tmp1의 값보다 작으면  
                num = tmp1->data; //값을 바꿔준다. 
                tmp1->data = tmp2->data;
                tmp2->data = num;
            }
        }
    }
    //printf("\n\n정렬 끝\n");
}
