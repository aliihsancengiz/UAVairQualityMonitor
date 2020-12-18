#include "TransmitInterface.h"
#include "main.h"

UART_HandleTypeDef huart2;

void Uart_Transmit(uint8_t *data,uint32_t len)
{
    HAL_UART_Transmit(&huart2,data,len,500);
}
