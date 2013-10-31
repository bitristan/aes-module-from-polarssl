#include "aes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  unsigned int i;
  unsigned char key[AES_BLOCK_SIZE];

  if (argc != 2 && argc != 3) {
    printf("Usage: aes content key\n");
    exit(-1);
  }

  for (i = 0; i < AES_BLOCK_SIZE; i++) {
    key[i] = 32 + i;
  }

  if (argc == 3) {
    if (strlen(argv[2]) >= 16) {
      argv[2][15] = '\0';
    }
    sprintf(key, "%s", argv[2]);
  }
  printf("key is %s\n", key);

  printf("\noriginal string is: %s\n", argv[1]);
  unsigned char *encrypt_string = aes_encrypt_cbc_str(key, argv[1]);
  printf("\nencrypt string is: %s\n", encrypt_string);
  unsigned char *decrypt_string = aes_decrypt_cbc_str(key, encrypt_string);
  printf("\ndecrypt string is: %s\n", decrypt_string);

  return 0;
}
