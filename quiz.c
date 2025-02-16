#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#endif


void clearScreen();
void printCentered(const char* text);
void printBox(const char* text);
void printProgressBar(int current, int total);
void setConsoleColor(int color);
void resetColor();

typedef struct {
    char question[256];
    char options[4][64];
    int correct_answer;
} Question;

int main() {
    #ifdef _WIN32
    system("color 0F");
    #endif

    Question questions[] = {
        {
            "What is the capital of France?",
            {"London", "Berlin", "Paris", "Madrid"},
            2
        },
        {
            "Which programming language is this quiz written in?",
            {"Python", "Java", "C", "JavaScript"},
            2
        },
        {
            "What is 2 + 2?",
            {"3", "4", "5", "6"},
            1
        },
        {
            "Which planet is known as the Red Planet?",
            {"Venus", "Jupiter", "Mars", "Saturn"},
            2
        }
    };

    int total_questions = sizeof(questions) / sizeof(questions[0]);
    int score = 0;
    char choice;

    clearScreen();
    setConsoleColor(6);
    printBox("Welcome to the Modern Quiz Application!");
    resetColor();
    printf("\n\nPress Enter to start...");
    getchar();

    for (int i = 0; i < total_questions; i++) {
        clearScreen();
        
        setConsoleColor(3);
        printf("\nQuestion %d/%d\n", i + 1, total_questions);
        printProgressBar(i + 1, total_questions);
        resetColor();
        
        printf("\n\n");
        setConsoleColor(7);
        printBox(questions[i].question);
        resetColor();
        
        printf("\n");
        for (int j = 0; j < 4; j++) {
            setConsoleColor(2);
            printf("    %c) ", 'A' + j);
            resetColor();
            printf("%s\n", questions[i].options[j]);
        }

        printf("\nYour answer (A/B/C/D): ");
        do {
            choice = toupper(getchar());
            while (getchar() != '\n');
        } while (choice < 'A' || choice > 'D');

        if ((choice - 'A') == questions[i].correct_answer) {
            score++;
            setConsoleColor(10);
            printCentered("✓ Correct!");
        } else {
            setConsoleColor(12);
            printCentered("✗ Incorrect!");
            printf("\nThe correct answer was: %c\n", 'A' + questions[i].correct_answer);
        }
        resetColor();
        
        printf("\nPress Enter to continue...");
        getchar();
    }

    clearScreen();
    setConsoleColor(6);
    printBox("Quiz Complete!");
    printf("\n\n");
    
    setConsoleColor(7);
    char score_text[64];
    sprintf(score_text, "Your Score: %d/%d (%.1f%%)", 
            score, total_questions, (float)score/total_questions * 100);
    printCentered(score_text);
    
    printf("\n\n");
    if (score == total_questions) {
        setConsoleColor(10);
        printCentered("Perfect Score! Excellent work!");
    } else if (score >= total_questions * 0.7) {
        setConsoleColor(11);
        printCentered("Great job! Well done!");
    } else if (score >= total_questions * 0.5) {
        setConsoleColor(14);
        printCentered("Good effort! Keep practicing!");
    } else {
        setConsoleColor(12);
        printCentered("Keep studying! You can do better!");
    }
    resetColor();

    printf("\n\nPress Enter to exit...");
    getchar();
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printCentered(const char* text) {
    int padding = (80 - strlen(text)) / 2;
    printf("%*s%s\n", padding, "", text);
}

void printBox(const char* text) {
    int len = strlen(text);
    printf("\n    ╔");
    for (int i = 0; i < len + 2; i++) printf("═");
    printf("╗\n");
    printf("    ║ %s ║\n", text);
    printf("    ╚");
    for (int i = 0; i < len + 2; i++) printf("═");
    printf("╝\n");
}

void printProgressBar(int current, int total) {
    const int bar_width = 40;
    int progress = (int)((float)current/total * bar_width);
    
    printf("    [");
    for (int i = 0; i < bar_width; i++) {
        if (i < progress) printf("■");
        else printf("□");
    }
    printf("] %d%%", (int)((float)current/total * 100));
}

void setConsoleColor(int color) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    #else
        switch(color) {
            case 2: printf("\033[32m"); break;
            case 3: printf("\033[36m"); break;
            case 6: printf("\033[33m"); break;
            case 7: printf("\033[37m"); break;
            case 10: printf("\033[92m"); break;
            case 11: printf("\033[96m"); break;
            case 12: printf("\033[91m"); break;
            case 14: printf("\033[93m"); break;
        }
    #endif
}

void resetColor() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
    #else
        printf("\033[0m");
    #endif
}
