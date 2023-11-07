#include <iostream>



#define FILE_NAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
//debug print with args
#define DEBUGPRINT(...) printf("[DEBUG] %s : ", FILE_NAME); printf(__VA_ARGS__); printf("\n");
