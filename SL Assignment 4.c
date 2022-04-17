/* Heap Management : Allocation and De-allocation of Memory */

#include <stdio.h>
#include<stdlib.h>

int g = 0, k = 0;

struct free {
    int tag;
    int size;
    struct free* next;
}* free_head = NULL, *prev_free = NULL;

struct alloc {
    int block_id;
    int tag;
    int size;
    struct alloc* next;
}* alloc_head = NULL, *prev_alloc = NULL;

void create_free(int c)
{
    struct free* p = (struct free*)
        malloc(sizeof(struct free));
    p->size = c;
    p->tag = g;
    p->next = NULL;
    if (free_head == NULL)
        free_head = p;
    else
        prev_free->next = p;
    prev_free = p;
    g++;
}

void print_free()
{
    struct free* p = free_head;
    printf("Tag\tSize\n");
    while (p != NULL) {
        printf("%d\t",p->tag);
        printf("%d\n",p->size);
        p = p->next;
    }
}

void print_alloc()
{
    struct alloc* p = alloc_head;
    printf("Tag\tBlock ID\tSize\n");
    while (p != NULL) {
        printf("%d\t ",p->tag);
        printf("%d\t\t",p->block_id);
        printf("%d\n",p->size);
        p = p->next;
    }
}

void create_alloc(int c)
{
    
    struct alloc* q = (struct alloc*)
        malloc(sizeof(struct alloc));
    q->size = c;
    q->tag = k;
    q->next = NULL;
    struct free* p = free_head;
    
    while (p != NULL) {
        if (q->size <= p->size)
            break;
        p = p->next;
    }

    if (p != NULL) {
        
        q->block_id = p->tag;
        p->size -= q->size;
        if (alloc_head == NULL)
            alloc_head = q;
        else {
            prev_alloc = alloc_head;
            while (prev_alloc->next != NULL)
                prev_alloc = prev_alloc->next;
            prev_alloc->next = q;
        }
        k++;
    }
    else 
        printf("\nBlock of size %d can't be allocated\n",c);
}

void delete_alloc(int t)
{
   
    struct alloc *p = alloc_head, *q = NULL;
    while (p != NULL) {
        if (p->tag == t)
            break;
        q = p;
        p = p->next;
    }
    if (p == NULL)
        printf("Tag ID doesn't exist\n");
    else if (p == alloc_head)
        alloc_head = alloc_head->next;
    else
        q->next = p->next;
    struct free* temp = free_head;
    while (temp != NULL) {
        if (temp->tag == p->block_id) {
            temp->size += p->size;
            break;
        }
        temp = temp->next;
    }
}

int main()
{
    int blockSize[3], RequestSize[4], BNo, RNo,i,c;
    
    printf("Enter no. of blocks:");
    scanf("%d",&BNo);
    printf("\n Enter size of each block:");
    for(i=1;i<=BNo;i++)
    	scanf("%d",&blockSize[i]);
    
    printf("Enter no. of Requests:");
    scanf("%d",&RNo);
    printf("\n Enter size of each Request:");
    for(i=1;i<=RNo;i++)
    	scanf("%d",&RequestSize[i]);
    	
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(RequestSize) / sizeof(RequestSize[0]);

  
    for (i = 0; i < m; i++)
        create_free(blockSize[i]);

    for (i = 0; i < n; i++)
        create_alloc(RequestSize[i]);

    print_alloc();

   
    delete_alloc(0);

    create_alloc(c);
    printf("\n After deleting block with tag id 0.\n");
    print_alloc();
}

/* Garbage Collection Implimentation */


#include <stdio.h>
#include <stdlib.h>
  
typedef struct link singleLink;
 
typedef struct trashLink singleTrashLink;
 
struct link {
    int data;
    singleLink * prev;
    singleLink * next;
};
 
struct trashLink {
    int trashdata;
    singleTrashLink * prev;
    singleTrashLink * next;
};
 
typedef struct linkedList
{
    int count;
    singleLink * first;
    singleLink * last;
}
doublyLinkedList;
 
typedef struct trashList
{
    int count;
    singleTrashLink * first;
    singleTrashLink * last;
}
trashLinkedList;
 
void DISPLAY_TRASH(trashLinkedList * list, int trashdata) 
{
   singleTrashLink * trashLink;
   printf("\n");
   for (trashLink = list->first; trashLink; trashLink = trashLink->next) {
       trashdata = trashLink->trashdata;
       printf ("Trash output: \t%d\n", trashdata);
   }
}
 
void initiateList(doublyLinkedList * list)
{
   list->first = list->last = 0;
   list->count = 0;
}
 
void initiateTrashList(trashLinkedList * list) 
{
   list->first = list->last = 0;
   list->count = 0;
}
 
void SKIP_INORDER(doublyLinkedList * list, int link2Delete)
{
   int data = 0;
   singleLink * link;
   singleLink * next;
  
   for(link = list->first; link; link = next) {
          data = link->data;
       if (link2Delete == data) {
               next = link->next;
               return;
       }
   }
}
 
void addToTrash(trashLinkedList * trashList, int link2Delete) 
{
   int trashdata = 0;
   singleTrashLink * trashlink;
   singleLink * link;
   for (trashlink = trashList->first; trashlink; trashlink = trashlink->next) {
          trashdata = trashlink->trashdata;
       if (link2Delete == trashdata) {
               return;
       }
   }
   trashlink = calloc(1, sizeof (singleTrashLink)); 
   trashlink->trashdata = link2Delete;
   if(!link) { 
       printf("Memory allocation was unsuccessful.\n");
       exit(0);
   }
   if(trashList->last) {
       trashList->last->next = trashlink;
       trashlink->prev = trashList->last;
       trashList->last = trashlink;
   }
   else {
       trashList->first = trashlink;
       trashList->last = trashlink;
   }
   trashList->count++;
}
 
void FREE_INORDER(doublyLinkedList * list)
{
   singleLink * link;
   singleLink * next;
  
   for(link = list->first; link; link = next) {
       next = link->next;
       free(link);   
   }
}
 
void clearFromList(doublyLinkedList * list, int link2Delete)
{
    singleLink * prev;
    singleLink * next;
    singleLink * link;
 
    int data = 0;
 
    for(link = list->first; link; link = next) {
        data = link->data;
        if (link2Delete == data) {
                prev = link->prev;
                next = link->next;
            if (prev) {
                if (next) {
                  
                    prev->next = next;
                    next->prev = prev;
                }
                else {
                  
                    prev->next = 0;
                    list->last = prev;
                }
            }
            else {
                if (next) {
                  
                    next->prev = 0;
                    list->first = next;
                }
                else {
                   
                    list->first = 0;
                    list->last = 0;
                }
            }
            list->count--;
             
        }
    }
}
 
void addToList(doublyLinkedList * list, int data) 
{
   singleLink * link;
 
   link = calloc(1, sizeof (singleLink)); 
   link->data = data;
   if(!link) { 
       printf("Memory allocation was unsuccessful.\n");
       exit(0);
   }
   if(list->last) {
       list->last->next = link;
       link->prev = list->last;
       list->last = link;
   }
   else {
       list->first = link;
       list->last = link;
   }
   list->count++;
}
 
void DISPLAY_INORDER(doublyLinkedList * list, int data) 
{
   singleLink * link;
   printf("\n");
   for (link = list->first; link; link = link->next) {
       data = link->data;
       printf ("Left to right output: \t%d\n", data);
   }
}
 
void DISPLAY_POSTORDER(doublyLinkedList * list, int data) 
{
   singleLink * link;
   printf("\n");
   for (link = list->last; link; link = link->prev) {
       data = link->data;
       printf ("Right to left output: \t%d\n", data);
   }
}
 
int main(int argc, char *argv[])
{
 
   int data = 0;
   int trashdata = 0;
   char *end;
   int i;
   doublyLinkedList list;
   trashLinkedList trashList;
     
   initiateList(& list);
   initiateTrashList(& trashList);
    
 
    DISPLAY_INORDER(&list, 0); 
     
    DISPLAY_POSTORDER(&list, 0); 
 
     
    int link2Delete;
    int trashMaxNumber = rand() % data + 3;
    printf("\n");
    for(i = 0; i < trashMaxNumber; i++) {
       
        link2Delete = (rand() % data);
        printf("Number Trashed: %d\n", link2Delete);
        addToTrash(&trashList, link2Delete);
        clearFromList(&list, link2Delete);
    }
     
    DISPLAY_TRASH(&trashList, 0); 
    DISPLAY_INORDER(&list, 0); 
         
    FREE_INORDER(&list);
}
