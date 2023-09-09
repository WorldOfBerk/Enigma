#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strupr(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = toupper(str[i]);
  }
  return str;
}

char *strlwr(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}

int main() {
  static char rotors[3][26] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO"
  };

  int rotor_positions_encryption_uppercase[3] = {0, 0, 0};

  char operation_type;
  printf("Encrypt or decrypt? (Enter 'e' to encrypt, 'd' to decrypt): ");
  scanf(" %c", &operation_type);

  char text[1000];
  printf("Enter the text: ");
  getchar();
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';

  char *uppercase_text = (char *)strupr(text);

  if (operation_type == 'e') {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < strlen(uppercase_text); j++) {
        char c = uppercase_text[j];
        if (isalpha(c)) {
          c = rotors[i][(c - 'A' + rotor_positions_encryption_uppercase[i]) % 26];
          rotor_positions_encryption_uppercase[i]++;
          uppercase_text[j] = c;
        }
      }
    }
    printf("Encrypted text: %s\n", uppercase_text);
  } else if (operation_type == 'd') {
    for (int i = 2; i >= 0; i--) {
      for (int j = 0; j < strlen(uppercase_text); j++) {
        char c = uppercase_text[j];
        if (isalpha(c)) {
          int index = strchr(rotors[i], c) - rotors[i];
          c = (index - rotor_positions_encryption_uppercase[i] + 26) % 26 + 'A';
          rotor_positions_encryption_uppercase[i]++;
          uppercase_text[j] = c;
        }
      }
    }
    printf("Decrypted text: %s\n", uppercase_text);
  } else {
    printf("Invalid operation type. Please enter 'e' or 'd'.\n");
    return 1;
  }

  return 0;
}
