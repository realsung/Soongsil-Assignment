
struct Person {
    int id;
    char name[20];
};

typedef struct Person Person;

int main() {
    struct Person p;
    p.id = 1;
    strcpy(p.name, "John Doe");
    printf("Person id: %d\n", p.id);
    printf("Person name: %s\n", p.name);
    return 0;
}