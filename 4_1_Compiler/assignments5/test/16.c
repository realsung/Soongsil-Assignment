int main(int argc, char*argv[], char**envp){
    if(argc < 2){
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    printf("Hello, %s\n", argv[1]);
}