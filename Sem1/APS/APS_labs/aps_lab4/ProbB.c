#include <stdio.h>
#include <malloc.h>
 
struct Node{
    int val;
    struct Node* next;
};
 
//Inserts N nodes to the linked list
void insert(struct Node** head_ref, int N){
 
    int data = 0;
    int i = 0;
    struct Node* prev = NULL;
 
    for(i = 0; i<N; i++){
        //taking user input;
        scanf("%d",&data);
 
        //Allocating memory for new node
        struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
 
        //Assigning value
        temp->val  = data;
        temp->next = NULL;
 
        if(*head_ref == NULL){
            //Setting head pointer
            *head_ref = temp;
        }
        else{
            //Settign next pointer for previous node
            prev->next = temp;
        }
        prev = temp;
    }
}
 
//prints linked list
void printList(struct Node* head){
 
    struct Node* cur = head;
    while(cur != NULL){
        printf("%d ",cur->val);
        cur = cur->next;
    }
    printf("\n");
}
 
struct Node*  revK(struct Node* head,int N,int K){
    
    if(head == NULL)
        return NULL;

    else if(N>=K){
         struct Node* temp = head;
        int i=0;
        for(i=0;i<K;i++){
            temp = temp->next;
        }


        struct Node* new_ele = revK(temp,N-K,K);

        struct Node* prev = NULL;
        struct Node* curr = NULL;
        struct Node* nxt = NULL;
//        struct Node* new_ele = NULL;
        struct Node* start = head;

        curr = nxt = head; 

        int count =0;
       // scanf("%d",&(prev->val));
        while(count != K){
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
            count++;
        }

        start->next = new_ele;
        return prev; 

    }
    else{
        struct Node* temp = head;
        struct Node* prev = NULL;
        struct Node* curr = NULL;
        struct Node* nxt = NULL;
        struct Node* new_ele = NULL;
        struct Node* start = head;

        //int i=0;
        while(temp != NULL)
            temp = temp->next;

        new_ele = temp;
        curr = nxt = head; 

        int count =0;
       // scanf("%d",&(prev->val));
        while(curr !=NULL){
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
            count++;
        }

        start->next = new_ele;
        return prev;       //this is the new head of the returned list

    }
}

 
int main(){
 
    int T = 0;  //Number of test cases
    scanf("%d",&T);
 
    int N = 0;  //Size of linked list
    int K = 0; //Size of group
 
    while(T--){
        scanf("%d %d",&N, &K);
 
        struct Node* head = NULL;
        insert(&head,N);
 
        //write your code here.
        //You can create a new functions apart from the ones provided.
        head = revK(head,N,K);
 
        printList(head);
    }
 
    return 0;
}