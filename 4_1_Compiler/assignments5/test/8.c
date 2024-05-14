struct Point {
    int x;
    int y;
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