#include <stdio.h>
#include <malloc.h>
#include <time.h>


const unsigned short MAX_SIZE = 2; // фиксированная длинна очереди


typedef struct node { /*Создаем свой тип данных узел кототорый содердит значение узла и ссылку на следующий узел*/
    unsigned int val;
    struct node* next;
} node_t;
 
typedef struct {  /*Создаем тип очередь с ссылкой на первый и последний узел*/
    node_t* head;
    node_t* tail;
    size_t size;
} queue_t;

//инициализация
void queue_init(queue_t* q){
    q->head = q->tail = NULL;
    q->size = 0;
}

//добавить в очередь
int queue_push(queue_t* q, unsigned int val){
    if (q->size < MAX_SIZE){
        node_t* p = (node_t*)malloc(sizeof(node_t));
        if(p != NULL){
            p->val  = val;
            p->next = NULL;
            if(q->head == NULL)
                q->head = q->tail = p;
            else {
                q->tail->next = p;
                q->tail = p;
            }
            q->size += 1;
        }
        return 1;
    }
   return 0;
}

size_t queue_size (queue_t* q){

    if (q != NULL){
      return q->size; 
    }
    return 0;
}

//чтение из очереди
int queue_read (queue_t* q, unsigned int index,  unsigned int *val){

   if (queue_size(q) > index){
        *val = (q->head + index)->val;
        return 1;
   }

   return 0;
}
 
 
int queue_empty(queue_t* q){
    return (q->head == NULL);
}


static void read_two_queue (queue_t* q1, queue_t* q2){
    unsigned int val;
    unsigned int index;
    printf("Enter index: \n");
    scanf("%u", &index);
    if (!queue_empty(q1) && queue_empty(q2)){
        if (!queue_read(q1, index, &val)){
            puts("index exceeds queue size");
        }
        else{
            printf("%d", val);
        }
    }
    else if (queue_empty(q1) && queue_empty(q2)){
        puts("queue is empty ");
    }
    else if (queue_empty(q1) && !queue_empty(q2)){

        if (!queue_read(q2, index, &val)){
            puts("index exceeds queue size ");
        }
        else{
            printf("%d", val);
        }
    }
    else if (!queue_empty(q1) && !queue_empty(q2)){

        if (queue_size(q1) + queue_size(q2) > index){

           if (queue_size(q1) > index){
               queue_read(q1, index, &val);
               printf("%d", val);
           }
           else if (queue_size(q2) > index - queue_size(q1)){
               queue_read(q1, index - queue_size(q1), &val);
               printf("%d", val);
           }
           else{

                 puts("index exceeds queue size ");
           }
       }
   }
}

static void content(queue_t* q){
    node_t* p = q->head;
    if (!queue_empty(q)){
        while (p != NULL){
        
            printf("%u ", p->val);
            p = p->next;
        }
            printf("\n");
       }
    else{
    puts("queue is empty ");
   }
}

int queue_union(queue_t* q3, queue_t* q1, queue_t* q2){
    node_t* p1, *p2, *eq, **pq;
    p1 = q1->head;
    p2 = q2->head;
    pq = &q3->head;
    eq = q3->head;

    if((q1->head == NULL) || (q2->head == NULL)){
        printf("one of the queues is empty \n");
        return 0;
    }
    while ((p1 != NULL) && (p2 != NULL))
    {
      *pq = p1;
      eq = *pq;
      pq  = &(*pq)->next;
      *pq = p2;
      eq = *pq;
      pq  = &(*pq)->next; 
      p1  = p1->next;
      p2  = p2->next;
    }
    while(p1 != NULL){
        *pq = p1;
        p1  = p1->next;
        eq  = *pq;
        pq  = &(*pq)->next;
    }
 
    while(p2 != NULL){
        *pq = p2;
        p2  = p2->next;
        eq  = *pq;
        pq  = &(*pq)->next;
    }
    q3->tail = eq;
    return 1;
}


int timeout ( int seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}

    return  1;
}

static void get_queue (queue_t* q1, queue_t* q2, queue_t* q3){

    puts("Enter number queue: ");
    unsigned int val = 0;
    scanf("%u", &val);
    if (val == 1){
        content(q1);
    }
    else if (val == 2){

        content(q2);
    }
    else if (val == 3){

        content(q3);
    }
    else{

        fprintf(stderr, "Incorrect queue number entered \n");
    }
}

static void get_size (queue_t* q1, queue_t* q2, queue_t* q3){

    unsigned int size = 0;
    puts("Enter number queue: ");
    unsigned int val = 0;
    scanf("%u", &val);
    if (val == 1){
        size = (unsigned int)queue_size(q1);
        printf ("size = %u \n", size);
    }
    else if (val == 2){

        size = (unsigned int)queue_size(q1);
        printf ("size = %u \n", size);
    }
    else if (val == 3){

        size = (unsigned int)queue_size(q1);
        printf ("size = %u \n", size);
    }
    else{

        fprintf(stderr, "Incorrect queue number entered \n");
    }

}


void queue_pop(queue_t* q){
    node_t* t = q->head;
    if(t != NULL){
        q->head = q->head->next;
        free(t);
    }
    if(q->head == NULL)
        q->tail = NULL;
}

int main (void){

   char command;
   unsigned int val = 0;
   queue_t q1, q2, q3;
   queue_init(&q1);
   queue_init(&q2);
   queue_init(&q3);

   for (;;){
        puts("Enter command :");
        command = getchar();
        if (command!= '\n' && command != EOF){
            if (command == 'r'){ // Чтение из очереди + дополнительный параметр индекс 
                read_two_queue(&q1, &q2);
            }
            else if (command == 'w'){  // Добавления значения в очередь дополнительный пармаметр число которое надо добавить в очередь
                puts("Enter number: ");
                scanf("%u", &val);
                if (!queue_push(&q1, val)){
                   if (!queue_push(&q2, val)){
                      printf("size larger %u \n", MAX_SIZE);
                   }
                }
            }
            else if (command == 's'){ // размер очереди плюс содержимое всей очереди
                get_size(&q1, &q2, &q3);
                get_queue(&q1, &q2, &q3);
            }
            else if (command ==  'c'){ // содержимое очереди
                get_queue(&q1, &q2, &q3);
            }
            else if (command ==  'u'){// сличяние очереди в шахматном порядке
                queue_union (&q3, &q1, &q2);
            }
            else if (command ==  'q'){
                break;
            }
            else{
                puts("Unknown commands");
            }
        }
        getchar();
   }
   queue_pop(&q1);
   queue_pop(&q2);
   queue_pop(&q3);
   return 0;
}