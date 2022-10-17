#include <stdio.h> 
#include <stdlib.h>

typedef struct Node { //���Ḯ��Ʈ�� ��� ����ü
    double data; //���ڸ� �Է¹޴� ����
    struct Node* link; //���� ��� ��ũ
} listNode;

typedef struct Head { //��� ��� ����ü
    struct Node* first; //ù ��° ��带 ����Ű�� ��ũ
} headNode;

void arrayPrint(headNode** head); //���Ḯ��Ʈ�� ����ϴ� �Լ�
void sort(headNode** head); //���Ḯ��Ʈ�� �����ϴ� �Լ�
void readFile(headNode** head); //Sample Data.txt ���Ͽ��� ���ڸ� �о ���Ḯ��Ʈ�� �Է��ϴ� �Լ�

int main() {
    //printf("2020039027 ������\n"); //�й� �̸�
    headNode* h = (headNode*)malloc(sizeof(headNode)); //ù ��带 ����ų ����� ����
    h->first = NULL; //ù ��� NULL�� �ʱ�ȭ
    readFile(&h); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ����
    //arrayPrint(&h); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ���
    sort(&h); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ����
    //arrayPrint(&h); //�Լ��� ������� �ּҸ� �Է��ؼ� ���� ���� ���Ḯ��Ʈ�� ���
    listNode* tmp1 = h->first; //free 
    listNode* tmp2 = tmp1;
    while(tmp1 != NULL) {
        tmp1 = tmp1->link;
        free(tmp2);
        tmp2 = tmp1;
    }
    free(h);
}

void readFile(headNode** head) { //������� �ּҸ� �޾Ƽ� ������ ���ڷ� ���Ḯ��Ʈ�� ����� �Լ�
    //printf("\n���� �б� ����\n\n...");
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
            if((*head)->first == NULL) { //ù ��° ��尡 ���� ��
                (*head)->first = newnode; //ù ��° ��� ����
            }
            else { //ù ��° ��尡 ���� ��
                tmp = (*head)->first; //tmp�� ù ��° ��� �Է�
                while(tmp->link != NULL) { //��ũ�� ���� ������ �ݺ�
                    tmp = tmp->link; //���� ���� �̵�
                }
                tmp->link = newnode; //���� �� ��忡 ���ο� ��带 ��ũ��Ŵ
            }
        }
    }
    //printf("\n\n���� �б� ��\n");

}

void arrayPrint(headNode** head) { //������� �ּҸ� �޾Ƽ� ���Ḯ��Ʈ�� ����ϴ� �Լ�
    printf("\n�迭 ���\n\n");
    listNode* tmp = (listNode*)malloc(sizeof(listNode)); //��� �̵��� �ʿ��� ��� ����
    tmp = (*head)->first; //tmp�� ù ��° ��� �Է�
    while(tmp != NULL) { //tmp�� NULL�� �� ������ �ݺ�
        printf("%.0lf ", tmp->data); //���� ���
        tmp = tmp->link; //���� ���� �̵�
    }
    printf("\n\n");
}

void sort(headNode** head) { //������� �ּҸ� �޾� ������������ ���������ϴ� �Լ� 
    //printf("\n���� ����\n\n...");
    listNode* tmp1, * tmp2; //��� �̵��� �� ����� ��� 
    double num; //���� �ٲ� �� ����� ���� 
    for(tmp1=(*head)->first; tmp1!=NULL; tmp1=tmp1->link) { //tmp1�� ����  �������� �̵� 
        for(tmp2=tmp1; tmp2!=NULL; tmp2=tmp2->link) { //tmp2�� �ڵ��� 
            if(tmp2->data < tmp1->data) { //tmp2�� ���� tmp1�� ������ ������  
                num = tmp1->data; //���� �ٲ��ش�. 
                tmp1->data = tmp2->data;
                tmp2->data = num;
            }
        }
    }
    //printf("\n\n���� ��\n");
}
