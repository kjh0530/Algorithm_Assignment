#include <stdio.h> 
#include <stdlib.h>

typedef struct Node { //연결리스트의 노드 구조체
    double data; //숫자를 입력받는 변수
    struct Node* link; //다음 노드 링크
} listNode;

void arrayPrint(listNode** head); //연결리스트를 출력하는 함수
void sort(listNode** node, int count); //연결리스트를 정렬하는 함수(merge Sort)
void readFile(listNode** head); //Sample Data.txt 파일에서 숫자만 읽어서 연결리스트에 입력하는 함수
void partition(listNode** list1, listNode** list2, listNode* list, int count); 
//merge Sort 함수에서 배열을 분할하는 함수
int count(listNode** head); //연결리스트의 노드 개수를 세어서 리턴하는 함수
listNode* merge(listNode* list1, listNode* list2); //merge Sort 함수에서 merge(병합)하는 함수

int main() {
    //printf("2020039027 김주훈\n"); //학번 이름
    listNode* h = (listNode*)malloc(sizeof(listNode)); //첫 노드를 가리킬 헤드노드 생성
    h->link = NULL; //첫 노드 NULL로 초기화
    readFile(&h); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 생성
    //arrayPrint(&h); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 출력
    listNode* node = h->link;
    sort(&node, count(&h)); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 정렬
    //arrayPrint(&node); //함수에 헤드노드의 주소를 입력해서 리턴 없이 연결리스트를 출력
    listNode* tmp1 = h->link; //연결리스트를 메모리 free하기 위해 노드 이동할 때 사용할 노드 
	listNode* tmp2 = tmp1; //연결리스트를 메모리 free하기 위해 노드 이동할 때 사용할 노드
    while(tmp1 != NULL) { //연결리스트의 끝까지 가면서 free
        tmp1 = tmp1->link;
        free(tmp2);
        tmp2 = tmp1;
    }
    free(h); //head노드 free
    free(tmp1); //tmp1 free
    free(tmp2); //tmp2 free
}

void readFile(listNode** head) { //헤드노드의 주소를 받아서 파일의 숫자로 연결리스트를 만드는 함수
    printf("\n파일 읽기 시작\n\n...");
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
            if((*head)->link == NULL) { //첫 번째 노드가 없을 때
                (*head)->link = newnode; //첫 번째 노드 삽입
            }
            else { //첫 번째 노드가 있을 때
                tmp = (*head)->link; //tmp에 첫 번째 노드 입력
                while(tmp->link != NULL) { //링크가 없을 때까지 반복
                    tmp = tmp->link; //다음 노드로 이동
                }
                tmp->link = newnode; //가장 끝 노드에 새로운 노드를 링크시킴
            }
        }
    }
    printf("\n\n파일 읽기 끝\n");

}

void arrayPrint(listNode** head) { //헤드노드의 주소를 받아서 연결리스트를 출력하는 함수
    printf("\n배열 출력\n\n");
    listNode* tmp = (listNode*)malloc(sizeof(listNode)); //노드 이동에 필요한 노드 생성
    tmp = (*head)->link; //tmp에 첫 번째 노드 입력
    while(tmp != NULL) { //tmp가 NULL이 될 때까지 반복
        printf("%.0lf ", tmp->data); //숫자 출력
        tmp = tmp->link; //다음 노드로 이동
    }
    printf("\n\n");
}

int count(listNode** head) { //연결리스트를 받아서 길이를 리턴하는 함수
    listNode* tmp = (listNode*)malloc(sizeof(listNode)); //노드 이동할 때 필요한 노드 생성
    tmp = (*head)->link; //헤드 노드 저장
    int count = 0; //count 0으로 초기화
    while(tmp != NULL) { //연결리스트 끝날 때까지 반복
        tmp = tmp->link; //다음 노드로 이동
        count++; //count 1 증가
    }
    free(tmp); //tmp free
    return count; //count return
}

listNode* merge(listNode* list1, listNode* list2) { //분할된 연결리스트들을 병합하는 함수
    listNode* tmp = NULL;  //
    if(list1 == NULL) return list2;
    else if(list2 == NULL) return list1;

    if(list1->data < list2->data) { //list1의 처음 노드가 더 작으면
        tmp = list1; //list1 저장
        tmp->link = merge(list1->link, list2); //앞의 배열을 한칸 앞으로 이동 후 재귀호출
    }
    else {
        tmp = list2; //list2 저장
        tmp->link = merge(list1, list2->link); //뒤의 배열을 한칸 앞으로 이동 후 재귀호출
    }
    return tmp; //병합한 리스트를 리턴
}

void partition(listNode** list1, listNode** list2, listNode* list, int count) {
    //연결리스트를 분할하는 함수
    listNode* tmp = list; //분할할 리스트를 저장
    (*list1) = list; //시작 노드를 저장
    int i = 0; //반복문에 사용할 변수
    for(i=0; i<((count)/2)-1; i++) { //중간까지 이동
        tmp = tmp->link; //노드 이동
    }
    (*list2) = tmp->link; //중간 노드 저장
    tmp->link = NULL; //NULL로 초기화
}

void sort(listNode** node, int count) { //merge sort(병합 정렬)하는 함수
    listNode* list1, * list2, * list = (*node);
    //두 개의 부분 배열로 나누기 위해 앞의 배열 list1, 뒤의 배열 list2를 선언
    //list에는 매개변수로 받은 node를 저장 
    if(count<=1) return; //길이가 1개 이하가 되면 돌아간다

    partition(&list1, &list2, list, count); 
    //앞의 배열, 뒤의 배열, head 노드, 연결리스트의 길이를 매개변수로 해서 분할하는 함수를 통해서 분할한다.
    if(count%2 == 0) { //길이가 짝수일 때
        sort(&list1, count/2); //절반씩 나눔(재귀 호출)
        sort(&list2, count/2);
    }
    else { //길이가 홀수일 때
        sort(&list1, count/2); //앞의 배열은 절반 나눠서 소수점은 내림
        sort(&list2, count/2 + 1); //뒤의 배열은 절반 나눠서 소수점 내린 후 1 더함 
    }
    (*node) = merge(list1, list2); //merge(병합)해서 연결리스트에 저장
}

