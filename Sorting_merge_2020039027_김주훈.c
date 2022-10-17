#include <stdio.h> 
#include <stdlib.h>

typedef struct Node { //���Ḯ��Ʈ�� ��� ����ü
    double data; //���ڸ� �Է¹޴� ����
    struct Node* link; //���� ��� ��ũ
} listNode;

void arrayPrint(listNode** head); //���Ḯ��Ʈ�� ����ϴ� �Լ�
void sort(listNode** node, int count); //���Ḯ��Ʈ�� �����ϴ� �Լ�(merge Sort)
void readFile(listNode** head); //Sample Data.txt ���Ͽ��� ���ڸ� �о ���Ḯ��Ʈ�� �Է��ϴ� �Լ�
void partition(listNode** list1, listNode** list2, listNode* list, int count); 
//merge Sort �Լ����� �迭�� �����ϴ� �Լ�
int count(listNode** head); //���Ḯ��Ʈ�� ��� ������ ��� �����ϴ� �Լ�
listNode* merge(listNode* list1, listNode* list2); //merge Sort �Լ����� merge(����)�ϴ� �Լ�

int main() {
    //printf("2020039027 ������\n"); //�й� �̸�
    listNode* h = (listNode*)malloc(sizeof(listNode)); //ù ��带 ����ų ����� ����
    h->link = NULL; //ù ��� NULL�� �ʱ�ȭ
    readFile(&h); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ����
    //arrayPrint(&h); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ���
    listNode* node = h->link;
    sort(&node, count(&h)); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ����
    //arrayPrint(&node); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ���
    listNode* tmp1 = h->link; //���Ḯ��Ʈ�� �޸� free�ϱ� ���� ��� �̵��� �� ����� ��� 
	listNode* tmp2 = tmp1; //���Ḯ��Ʈ�� �޸� free�ϱ� ���� ��� �̵��� �� ����� ���
    while(tmp1 != NULL) { //���Ḯ��Ʈ�� ������ ���鼭 free
        tmp1 = tmp1->link;
        free(tmp2);
        tmp2 = tmp1;
    }
    free(h); //head��� free
    free(tmp1); //tmp1 free
    free(tmp2); //tmp2 free
}

void readFile(listNode** head) { //������� �ּҸ� �޾Ƽ� ������ ���ڷ� ���Ḯ��Ʈ�� ����� �Լ�
    printf("\n���� �б� ����\n\n...");
    FILE *fp = fopen("Sample Data.txt", "r"); //fopen���� ������ ����
    if(fp == NULL) { //������ �ȿ����� ��
        printf("File error\n");
    }
    else {
        char c; //"," �� ������ ����
        listNode* tmp = (listNode*)malloc(sizeof(listNode)); //��� �̵��� �ʿ��� ���
        while(!(feof(fp))) { //������ ���� �� ���� �ݺ�
            listNode* newnode = (listNode*)malloc(sizeof(listNode)); //���ο� ��� ����
            newnode->link = NULL; //��ũ�� NULL�� �ʱ�ȭ
            fscanf(fp, "%lf", &(newnode->data)); //���ο� ��忡 ���� �Է�
            fscanf(fp, "%c", &c); //"," �� ����
            if((*head)->link == NULL) { //ù ��° ��尡 ���� ��
                (*head)->link = newnode; //ù ��° ��� ����
            }
            else { //ù ��° ��尡 ���� ��
                tmp = (*head)->link; //tmp�� ù ��° ��� �Է�
                while(tmp->link != NULL) { //��ũ�� ���� ������ �ݺ�
                    tmp = tmp->link; //���� ���� �̵�
                }
                tmp->link = newnode; //���� �� ��忡 ���ο� ��带 ��ũ��Ŵ
            }
        }
    }
    printf("\n\n���� �б� ��\n");

}

void arrayPrint(listNode** head) { //������� �ּҸ� �޾Ƽ� ���Ḯ��Ʈ�� ����ϴ� �Լ�
    printf("\n�迭 ���\n\n");
    listNode* tmp = (listNode*)malloc(sizeof(listNode)); //��� �̵��� �ʿ��� ��� ����
    tmp = (*head)->link; //tmp�� ù ��° ��� �Է�
    while(tmp != NULL) { //tmp�� NULL�� �� ������ �ݺ�
        printf("%.0lf ", tmp->data); //���� ���
        tmp = tmp->link; //���� ���� �̵�
    }
    printf("\n\n");
}

int count(listNode** head) { //���Ḯ��Ʈ�� �޾Ƽ� ���̸� �����ϴ� �Լ�
    listNode* tmp = (listNode*)malloc(sizeof(listNode)); //��� �̵��� �� �ʿ��� ��� ����
    tmp = (*head)->link; //��� ��� ����
    int count = 0; //count 0���� �ʱ�ȭ
    while(tmp != NULL) { //���Ḯ��Ʈ ���� ������ �ݺ�
        tmp = tmp->link; //���� ���� �̵�
        count++; //count 1 ����
    }
    free(tmp); //tmp free
    return count; //count return
}

listNode* merge(listNode* list1, listNode* list2) { //���ҵ� ���Ḯ��Ʈ���� �����ϴ� �Լ�
    listNode* tmp = NULL;  //
    if(list1 == NULL) return list2;
    else if(list2 == NULL) return list1;

    if(list1->data < list2->data) { //list1�� ó�� ��尡 �� ������
        tmp = list1; //list1 ����
        tmp->link = merge(list1->link, list2); //���� �迭�� ��ĭ ������ �̵� �� ���ȣ��
    }
    else {
        tmp = list2; //list2 ����
        tmp->link = merge(list1, list2->link); //���� �迭�� ��ĭ ������ �̵� �� ���ȣ��
    }
    return tmp; //������ ����Ʈ�� ����
}

void partition(listNode** list1, listNode** list2, listNode* list, int count) {
    //���Ḯ��Ʈ�� �����ϴ� �Լ�
    listNode* tmp = list; //������ ����Ʈ�� ����
    (*list1) = list; //���� ��带 ����
    int i = 0; //�ݺ����� ����� ����
    for(i=0; i<((count)/2)-1; i++) { //�߰����� �̵�
        tmp = tmp->link; //��� �̵�
    }
    (*list2) = tmp->link; //�߰� ��� ����
    tmp->link = NULL; //NULL�� �ʱ�ȭ
}

void sort(listNode** node, int count) { //merge sort(���� ����)�ϴ� �Լ�
    listNode* list1, * list2, * list = (*node);
    //�� ���� �κ� �迭�� ������ ���� ���� �迭 list1, ���� �迭 list2�� ����
    //list���� �Ű������� ���� node�� ���� 
    if(count<=1) return; //���̰� 1�� ���ϰ� �Ǹ� ���ư���

    partition(&list1, &list2, list, count); 
    //���� �迭, ���� �迭, head ���, ���Ḯ��Ʈ�� ���̸� �Ű������� �ؼ� �����ϴ� �Լ��� ���ؼ� �����Ѵ�.
    if(count%2 == 0) { //���̰� ¦���� ��
        sort(&list1, count/2); //���ݾ� ����(��� ȣ��)
        sort(&list2, count/2);
    }
    else { //���̰� Ȧ���� ��
        sort(&list1, count/2); //���� �迭�� ���� ������ �Ҽ����� ����
        sort(&list2, count/2 + 1); //���� �迭�� ���� ������ �Ҽ��� ���� �� 1 ���� 
    }
    (*node) = merge(list1, list2); //merge(����)�ؼ� ���Ḯ��Ʈ�� ����
}

