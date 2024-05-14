struct Point {
    int x;
    int y;
    float z; // 타입 오류, z를 삭제하지 않으면 오류 발생
};

union Data {
    int i;
    float f;
    char str[20];
};

enum Color {
    RED, GREEN, BLUE
};

typedef struct Point point;
typedef union Data data;
typedef enum Color color;

point p;
p.x = 10;
p.z = 5.0; // z는 없는 필드