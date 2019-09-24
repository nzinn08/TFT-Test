#ifndef TFT_BOARD_SPECIFIC_H_
#define TFT_BOARD_SPECIFIC_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This function resets the TFT board and starts it back up again
 */
void resetTftBoard(void);

#ifdef __cplusplus
}
#endif //End C Interface

#endif
