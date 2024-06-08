int f(){
    return f;
}

int main(){
    f();
}

/*
test/6.c: In function ‘f’:
test/6.c:9:12: warning: returning ‘int (*)()’ from a function with return type ‘int’ makes integer from pointer without a cast [-Wint-conversion]
    9 |     return f1;
      |            ^~
*/