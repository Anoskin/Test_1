#include <stdio.h>
#include <malloc.h>



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
void queue_init(queue_t* q) {
    q->head = q->tail = NULL;
    q->size = 0;
}

//добавить в очередь
int queue_push(queue_t* q, unsigned int val) {
    if (q->size < MAX_SIZE) {
        node_t* p = (node_t*)malloc(sizeof(node_t));
        if (p != NULL) {
            p->val = val;
            p->next = NULL;
            if (q->head == NULL)
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

size_t queue_size(queue_t* q) {

    if (q != NULL) {
        return q->size;
    }
    return 0;
}

//чтение из очереди
int queue_read(queue_t* q, unsigned int index, unsigned int* val) {
    node_t* p = q->head;
    int i = 0;
    if (queue_size(q) > index) {
        for (; p != NULL; p= p->next) {
            if (i == index) {
                *val = p->val;
                return 1;
            }
            ++i;
        }
            
    }

    return 0;
}


int queue_empty(queue_t* q) {
    return (q->head == NULL);
}


static void read_two_queue(queue_t* q, int index, unsigned int val) {
    if (!queue_read(q, index, &val)) {
        puts("index exceeds queue size");
    }
    else {
        printf("%d \n", val);
    }
}

static void content(queue_t* q) {
    node_t* p = q->head;
    if (!queue_empty(q)) {
        while (p != NULL) {
            printf("%u ", p->val);
            p = p->next;
        }
        printf("\n");
    }
    else {
        puts("queue is empty ");
    }
}

int queue_union(queue_t* q3, queue_t* q1, queue_t* q2) {
    node_t* p1, * p2, * eq, ** pq;
    p1 = q1->head;
    p2 = q2->head;
    pq = &q3->head;
    eq = q3->head;

    if ((q1->head == NULL) || (q2->head == NULL)) {
        printf("one of the queues is empty \n");
        return 0;
    }
    while ((p1 != NULL) && (p2 != NULL))
    {
        *pq = p1;
        p1 = p1->next;
        eq = *pq;
        pq = &(*pq)->next;
        *pq = p2;
        p2 = p2->next;
        eq = *pq;
        pq = &(*pq)->next;
    }
    while (p1 != NULL) {
        *pq = p1;
        p1 = p1->next;
        eq = *pq;
        pq = &(*pq)->next;
    }

    while (p2 != NULL) {
        *pq = p2;
        p2 = p2->next;
        eq = *pq;
        pq = &(*pq)->next;
    }
    q3->tail = eq;
    q3->size = queue_size(q1) + queue_size(q2);
    return 1;
}


static void get_queue(queue_t* q1, queue_t* q2, queue_t* q3, unsigned int val) {


    if (val == 1) {
        content(q1);
    }
    else if (val == 2) {

        content(q2);
    }
    else if (val == 3) {

        content(q3);
    }
    else {

        fprintf(stderr, "Incorrect queue number entered \n");
    }
}

static void get_size(queue_t* q1, queue_t* q2, queue_t* q3, unsigned int val) {

    unsigned int size = 0;
    if (val == 1) {
        size = (unsigned int)queue_size(q1);
        printf("size = %u \n", size);
    }
    else if (val == 2) {

        size = (unsigned int)queue_size(q1);
        printf("size = %u \n", size);
    }
    else if (val == 3) {

        size = (unsigned int)queue_size(q1);
        printf("size = %u \n", size);
    }
    else {

        fprintf(stderr, "Incorrect queue number entered \n");
    }

}


void rewriting(queue_t* q1){
    node_t* t = q1->head;

    q1->head = q1->head->next;
    q1->size--;
    free(t);
}


void insert(queue_t* q1, queue_t* q2, unsigned int val) {

    if (!queue_push(q1, val)) {
    
        if (!queue_push(q2, q1->head->val)) {
            printf("size larger %u \n", MAX_SIZE);
        }
        else {
            rewriting(q1);
            queue_push(q1, val);
        }
    }
}

void queue_pop(queue_t* q) {
    node_t* t = q->head;
    if (t != NULL) {
        q->head = q->head->next;
        free(t);
    }
    if (q->head == NULL)
        q->tail = NULL;
}

int main(void) {

    char command;
    unsigned int val = 0;
    unsigned int index;
    queue_t q1, q2, q3;
    queue_init(&q1);
    queue_init(&q2);
    queue_init(&q3);

    for (;;) {
        puts("Enter command :");
        command = getchar();
        if (command != '\n' && command != EOF) {
            if (command == 'r') { // Чтение из очереди 
                puts("Enter number queue: ");
                scanf_s("%u", &val);
                printf("Enter index: \n");
                scanf_s("%u", &index);
                if (val == 1) {
                    read_two_queue(&q1, index, val);
                }
                else if (val == 2) {
                    read_two_queue(&q2, index, val);
                }
                else if (val == 3) {
                    read_two_queue(&q3, index, val);
                }
                else {
                    puts("there is no queue");
                }
            }
            else if (command == 'w') {  // Добавления значения в очередь 
                puts("Enter number: ");
                scanf_s("%u", &val);
                insert(&q1, &q2, val);
            }
            else if (command == 's') { // размер очереди плюс содержимое всей очереди
                puts("Enter number queue: ");
                scanf_s("%u", &val);
                get_size(&q1, &q2, &q3, val);
                get_queue(&q1, &q2, &q3, val);
            }
            else if (command == 'c') { // содержимое очереди
                puts("Enter number queue: ");
                scanf_s("%u", &val);
                get_queue(&q1, &q2, &q3, val);
            }
            else if (command == 'u') {// слияние очереди в шахматном порядке
                queue_union(&q3, &q1, &q2);
            }
            else if (command == 'q') {
                break;
            }
            else {
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
