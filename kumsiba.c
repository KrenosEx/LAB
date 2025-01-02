#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int language = 1;
FILE *scoreFile;

void printmenu() {
    if (language == 1) { // Bahasa Indonesia
        printf("===========================================\n");
        printf("|         Menu Game Tebak Angka           |\n");
        printf("===========================================\n");
        printf("|1. Mainkan Game                          |\n");
        printf("|2. Kredit                                |\n");
        printf("|3. Ubah Bahasa                           |\n");
        printf("|4. Lihat Skor                            |\n");
        printf("|5. Keluar dari Game                      |\n");
        printf("|Pilih opsi (1-5):                        |\n");
        printf("===========================================\n");
    } else { // English
        printf("===========================================\n");
        printf("|       Number Guesser Game Menu          |\n");
        printf("===========================================\n");
        printf("|1. Play Game                             |\n");
        printf("|2. Credits                               |\n");
        printf("|3. Change Language                       |\n");
        printf("|4. View Scores                           |\n");
        printf("|5. Exit Game                             |\n");
        printf("|Choose an option (1-5):                  |\n");
        printf("===========================================\n");
    }
}

void printCredits() {
    if (language == 1) { // Bahasa Indonesia
        printf("Game ini dibuat oleh:\n");
        printf("Kevin Nathanael Limarga - 2802412805\n");
        printf("Muhammad Nizham Irfan - 2802525230\n");
        printf("Justin Lysander Setiawan - 2802418651\n");
        printf("Felix Christian Tedjawidjaja - 2802409035\n\n");
        printf("Tekan 'Enter' untuk melanjutkan...\n");
        scanf("[^\n]");
        getchar();
    } else { // English
        printf("This Game Was Created By:\n");
        printf("Kevin Nathanael Limarga - 2802412805\n");
        printf("Muhammad Nizham Irfan - 2802525230\n");
        printf("Justin Lysander Setiawan - 2802418651\n");
        printf("Felix Christian Tedjawidjaja - 2802409035\n\n");
        printf("Press 'Enter' to continue...\n");
        scanf("[^\n]");
        getchar();
    }
}

void changeLanguage() {
    if (language == 1) {
        printf("Bahasa diubah ke Inggris.\n\n");
        language = 2; // Ubah ke English
    } else {
        printf("Language changed to Bahasa Indonesia.\n\n");
        language = 1; // Ubah ke Bahasa Indonesia
    }
}

int isValidNumber(char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int getValidInput() {
    char input[100];
    int valid = 0;
    int value;

    while (!valid) {
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0;

        if (isValidNumber(input)) {
            valid = 1;
            value = atoi(input);
        } else {
            if (language == 1) {
                printf("Masukkan angka yang valid!\n");
            } else {
                printf("Please enter a valid number!\n");
            }
        }
    }

    return value;
}

int pick_number(int min, int max) {
    int rnum = rand();
    return min + (rnum % (max - min + 1));
}

void saveScore(int score) {
    scoreFile = fopen("scores.txt", "a");
    if (scoreFile == NULL) {
        if (language == 1) {
            printf("Gagal membuka file skor.\n");
        } else {
            printf("Failed to open score file.\n");
        }
        return;
    }

    fprintf(scoreFile, "Score: %d\n", score);
    fclose(scoreFile);
}

void viewScores() {
    char buffer[255];
    scoreFile = fopen("scores.txt", "r");
    if (scoreFile == NULL) {
        if (language == 1) {
            printf("Tidak ada skor yang disimpan.\n");
        } else {
            printf("No scores saved.\n");
        }
        return;
    }

    if (language == 1) {
        printf("Skor yang disimpan:\n");
    } else {
        printf("Saved scores:\n");
    }

    while (fgets(buffer, 255, scoreFile)) {
        printf("%s", buffer);
    }

    fclose(scoreFile);
    if (language == 1) {
        printf("Tekan 'Enter' untuk melanjutkan...\n");
    } else {
        printf("Press 'Enter' to continue...\n");
    }
    getchar();
}

void playGame() {
    srand(time(NULL));
    int num = pick_number(1, 100);
    int attempts = 0;

    if (language == 1) {
        printf("Tebak angka antara 1-100...\n");
    } else {
        printf("Guess the number between 1-100...\n");
    }

    while (1) {
        int chosen_number;
        attempts++;
        if (language == 1) {
            printf("\nMasukkan angka: ");
        } else {
            printf("\nEnter a number: ");
        }
        scanf("%d", &chosen_number);
        getchar();

        if (chosen_number > num) {
            if (language == 1) {
                printf("Angka yang dimasukkan lebih besar dari angka rahasia.\n");
            } else {
                printf("The entered number is greater than the secret number.\n");
            }
        } else if (chosen_number < num) {
            if (language == 1) {
                printf("Angka yang dimasukkan lebih kecil dari angka rahasia.\n");
            } else {
                printf("The entered number is smaller than the secret number.\n");
            }
        } else {
            if (language == 1) {
                printf("Selamat! Anda telah menebak angka dengan benar dalam %d percobaan. Silakan menekan 'Enter' untuk melanjutkan...\n\n\n", attempts);
                saveScore(attempts);
                scanf("[^\n]");
                getchar();
            } else {
                printf("Congratulations! You guessed the number correctly in %d attempts. Please press 'Enter' to continue...\n\n\n", attempts);
                saveScore(attempts);
                scanf("[^\n]");
                getchar();
            }
            break;
        }
    }
}

int main() {
    int menu = 0;

    while (menu != 5) {
        printmenu();
        menu = getValidInput();

        switch (menu) {
            case 1:
                playGame();
                break;

            case 2:
                printCredits();
                break;

            case 3:
                changeLanguage();
                break;

            case 4:
                viewScores();
                break;

            case 5:
                if (language == 1) {
                    printf("-------------------------------------\n");
                    printf("|         Sampai Jumpa Lagi.        |\n");
                    printf("-------------------------------------\n");
                } else {
                    printf("-------------------------------------\n");
                    printf("|         See You Next Time.        |\n");
                    printf("-------------------------------------\n");
                }
                break;

            default:
                if (language == 1) {
                    printf("------------------------\n");
                    printf("|Masukan Opsi 1-5 Saja.|\n");
                    printf("------------------------\n");
                } else {
                    printf("-------------------------------\n");
                    printf("|Please Enter Option 1-5 Only.|\n");
                    printf("-------------------------------\n");
                }
                break;
        }
    }

    return 0;
}
