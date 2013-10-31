/*
 * Compile: gcc -o decrypt_file aes.c decrypt_file.c
 * Usage: decrypt_file src_file dst_file -k key
 */

#include "aes.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int isDir(unsigned char* filePath) {
  struct stat statbuf;
  stat(filePath, &statbuf);
  return S_ISDIR(statbuf.st_mode);
}

int isFile(unsigned char* filePath) {
  struct stat statbuf;
  stat(filePath, &statbuf);
  return S_ISREG(statbuf.st_mode);
}

unsigned char* readFileContent(unsigned char *filePath) {
  FILE *fp = fopen(filePath, "r");
  if (!fp) {
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  long length = ftell(fp);
  unsigned char *fileContent = (unsigned char *) malloc (length + 1);
  fseek(fp, 0, SEEK_SET);
  fread(fileContent, length, 1, fp);
  fileContent[length] = '\0';
  fclose(fp);

  return fileContent;
}

int writeContentToFile(unsigned char *content, unsigned char *filePath) {
  if (!content || !filePath) {
    return 0;
  }

  FILE *fp = fopen(filePath, "w");
  if (!fp) {
    return 0;
  }

  fwrite(content, strlen(content), 1, fp);
  fclose(fp);

  return 1;
}

int main(int argc, char *argv[]) {
  unsigned char *sourceFile;
  unsigned char *dstFile;
  unsigned char key[AES_BLOCK_SIZE];
  unsigned int i;

  // check command args
  if (argc != 3 && argc != 5) {
    printf("decrypt_dir src_file dst_file -k key\n");
    return -1;
  }

  sourceFile = argv[1];
  dstFile = argv[2];

  for (i = 0; i < AES_BLOCK_SIZE; i++) {
    key[i] = 32 + i;
  }

  if (argc == 5) {
    if (strlen(argv[4]) >= 16) {
      argv[4][15] = '\0';
    }
    sprintf(key, "%s", argv[4]);
  }

  unsigned char *content = readFileContent(sourceFile);
  unsigned char *decryptContent = aes_decrypt_cbc_str(key, content);
  writeContentToFile(decryptContent, dstFile);

  free(content);
  free(decryptContent);

  return 0;
}
