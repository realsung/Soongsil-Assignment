struct node {
    int data;
    struct node *next;
};
int main(){
    struct node *head = malloc(sizeof(struct node));
    free(head);  
    return 0;
}