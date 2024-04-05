int f(int x, int y){
    return x + y;
}

int main(){
    int (*fp)(int, int);
    fp = f;
    printf("%d\n", fp(1, 2));
    return 0;
}