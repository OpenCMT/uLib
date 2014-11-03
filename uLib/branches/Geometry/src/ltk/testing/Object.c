#include "testing-prototype.h"
#include "../Object.h"


int main() {
    BEGIN_TESTING(Object);

    struct _Object *ob = Object_new(ObjectClass);

    END_TESTING;
}
