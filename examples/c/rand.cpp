#include <cmath>
#include <cstdlib>
#include <cinttypes>
#include <ctime>

int *randBytes(int count) {

    srand(time(0));
    int *num = (int *) calloc(count, sizeof(uint8_t));

    for (int i = 0; i < count; i++) {
        num[i] = (rand() % 255) + 1;
    }

    return num;
};
int main() {
  randBytes(3);
}
