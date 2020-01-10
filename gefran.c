#include "gefran.h"

bool open_interfeice(char** can)
{
  struct ifreq ifr;
  struct sockaddr_can gefran_socket;
  
  status = socket(PF_CAN, SOCK_RAW, CAN_RAW);

  if (status < 0)
    {
      perror("Error while opening socket");
      exit(EXIT_FAILURE);
    }
  strcpy(ifr.ifr_name, can);
  ioctl(status, SIOCGIFINDEX, &ifr);

  gefran_socket.can_family = AF_CAN;
  gefran_socket.can_ifindex = ifr.ifr_ifindex;

  if (bind(status, (struct sockaddr *)&gefran_socket, sizeof(gefran_socket))<0)
    {
      perror("Error socket bind");
      exit(EXIT_FAILURE);
    }

   return EXIT_SUCCESS;
}

position_hex* give_value_position(position_hex *gefran_hex_result)
{
  gefran_hex_result = (position_hex*)malloc(sizeof(position_hex));
 
  if (!gefran_hex_result){
    perror("Error create memmory\n");
    return -1;
  }
  
  uint8_t status_read = read(status, &gefran_can_frame, sizeof(struct can_frame));
  if (status_read == -1){
    perror("Error read CAN message\n");
    return -1;
  }
  //Принимаю байты, объединяю и записываю
  gefran_hex_result->byte1 = (gefran_can_frame.data[1]<<8)+gefran_can_frame.data[0];
  gefran_hex_result->byte2 = (gefran_can_frame.data[3]<<8)+gefran_can_frame.data[2];

  //Преобразую в градусы
  //Если значение больше 32767, то вычитаю от 65535, значение получаетсся со знаком минус
  if (gefran_hex_result->byte1 > BORDER_NULL){
    gefran_hex_result->X_hex_result = gefran_hex_result->byte1 - BORDER_MAX;
    printf ("Position: %d\t", gefran_hex_result->X_hex_result);
  }
  else{
    gefran_hex_result->X_hex_result = gefran_hex_result->byte1;
    printf ("Position: %d\t", gefran_hex_result->X_hex_result);
  }
  
  if (gefran_hex_result->byte2 > BORDER_NULL){
    gefran_hex_result->Y_hex_result = gefran_hex_result->byte2 - BORDER_MAX;
    printf ("Position: %d\n", gefran_hex_result->Y_hex_result);
  }
  else{
    gefran_hex_result->Y_hex_result = gefran_hex_result->byte2;
    printf ("Position: %d\n", gefran_hex_result->Y_hex_result);
  }  
  return gefran_hex_result;
}

void free_value_position(position_hex *gefran_hex_result){
  free(gefran_hex_result);
}
