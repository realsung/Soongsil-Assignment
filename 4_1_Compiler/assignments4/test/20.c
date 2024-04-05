union {
    int i;
    char x[2];
} a;
int main(){
    a.i = 512;
    a.x[0] = 1;
    a.x[1] = 2;
    printf("%d\n", a.i);
    return 0;
}