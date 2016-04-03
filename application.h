#include "qpc.h"

enum ApplicationSignals {
    DUMMY_SIG = Q_USER_SIG,
    MAX_PUB_SIG,          /* the last published signal */

    TIMEOUT_SIG,
    MAX_SIG               /* the last signal */
};

typedef struct UartEventTag{
  QEvt super;
  char_t data[100];
} UartEvt;
