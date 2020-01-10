#ifndef GEFRAN_H
#define GEFRAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#define BORDER_NULL 32767
#define BORDER_MAX 65535

static struct can_frame gefran_can_frame;
static  uint8_t status;

/**
 * Структура для хранения сообщении о положении инклинометра
 * byte1 - принимает объединенные первый и второй байт
 * byte2 - принимает объединенные третий и четвертый байт
 * X_hex_result - содержит результат положения X
 * Y_hex_result - содержит результат положения Y
 */
typedef struct _position_hex{
  __u16 byte1;
  __u16 byte2;
  int16_t X_hex_result;
  int16_t Y_hex_result;
} position_hex;

/**
 * Открывай CAN интерфейс 
 * Возвращает true или false
 */
 bool open_interfeice(char** can);

/**
 * Функция получает CAN сообщение и преобразует в градусы
 * Возращает структуру положения X и Y
 */
position_hex* give_value_position(position_hex *gefran_hex_result);

/**
 * Функция для освобождения памяти после получения данных
 */
void free_value_position(position_hex *gefran_hex_result);

#endif
