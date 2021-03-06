#include "hash.h"

/*
 * 哈希函数：H(Key)=Sum_i(Key[keysize-1-i])*32^i;
 */
extern unsigned int hash(const char *str,int table_size)
{
    unsigned int hash_val=0;
    while(*str!='\0'){
        hash_val=(hash_val<<5)+ *str++;
    }
    return hash_val%table_size;
}
extern struct hash_map * init_hash(int table_size)
{
    struct hash_map * H;
    if(table_size<MIN_SIZE){
        printf("table size too small(<29)\n");
        exit(EXIT_FAILURE);
    }
    H=(struct hash_map *)malloc(sizeof(struct hash_map));
    if(H==NULL){
        printf("Out of space!\n");
        exit(EXIT_FAILURE);
    }
    H->table_size=next_prime(table_size);
    H->list=
        (struct node**)malloc(sizeof(struct node*)*H->table_size);
    if(H->list==NULL){
        printf("Out of space");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<H->table_size;i++){
        H->list[i]=(struct node*)malloc(sizeof(struct node));
        if(H->list[i]==NULL){
            printf("Out of space!\n");
            exit(EXIT_FAILURE);
        }else{
            H->list[i]->next=NULL;
        }
    }
    return H;
}
extern void destory_hash(struct hash_map *h)
{
    for(int i=0;i<h->table_size;i++){
        free(h->list[i]);
    }
    free(h);
}
extern struct node *contain(data_t key,struct hash_map *h)
{
    struct node *pos;
    struct node *head;
    head=h->list[hash(key,h->table_size)];
    pos=head->next;
    while(pos!=NULL&&strcmp(key,pos->data)!=0){
        pos=pos->next;
    }
    return pos;
}
extern void put(data_t key,struct hash_map *h)
{
    struct node *pos;
    struct node *new_node;
    struct node *head;

    pos=contain(key,h);
    /*不在散列表中*/
    if(pos==NULL){
        new_node=(struct node *)malloc(sizeof(struct node));
        if(new_node==NULL){
            printf("Out of space!\n");
            exit(EXIT_FAILURE);
        }else{
            head=h->list[hash(key,h->table_size)];
            new_node->data=key;
            new_node->next=head->next;
            head->next=new_node;
        }
    }
}
extern int next_prime(int n)
{
    int prime=0;
    for(int i=n;;i++){
        if(is_prime(i)){
            prime=i;
            break;
        }
    }
    return prime;
}
extern int is_prime(int n)
{
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}