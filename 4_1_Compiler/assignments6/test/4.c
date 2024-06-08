int main(){
    float a;
    switch(a){
        case 1:
            break;
    }
}
/*
~/Soongsil-Assignment/4_1_Compiler/assignments6 (main*) # gcc -fsyntax-only test/4.c                                       root@vultr
test/4.c: In function ‘main’:
test/4.c:4:12: error: switch quantity not an integer
    4 |     switch(a){
      |            ^
----------------------------
*/