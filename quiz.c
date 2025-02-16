#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #include <unistd.h>
    #define CLEAR "clear"
#endif

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

#define TOP_LEFT     "╔"
#define TOP_RIGHT    "╗"
#define BOTTOM_LEFT  "╚"
#define BOTTOM_RIGHT "╝"
#define HORIZONTAL   "═"
#define VERTICAL     "║"

typedef struct {
    char question[200];
    char options[4][50];
    int correct_answer;
} Question;

typedef struct {
    int score;
    int total_questions;
    int current_question;
    time_t start_time;
} QuizState;

Question questions[] = {
    {
        "What is the capital of France?",
        {"London", "Berlin", "Paris", "Madrid"},
        2
    },
    {
        "Which planet is known as the Red Planet?",
        {"Venus", "Mars", "Jupiter", "Saturn"},
        1
    },
    {
        "What is the largest mammal in the world?",
        {"African Elephant", "Blue Whale", "Giraffe", "Polar Bear"},
        1
    },
    {
        "Who painted the Mona Lisa?",
        {"Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Michelangelo"},
        2
    },
    {
        "What is the chemical symbol for gold?",
        {"Ag", "Fe", "Au", "Cu"},
        2
    }
};

void center_text(const char* text) {
    int padding = (80 - strlen(text)) / 2;
    printf("%*s%s\n", padding, "", text);
}

void draw_box(int width, int height) {
    printf("%s", TOP_LEFT);
    for (int i = 0; i < width - 2; i++) printf("%s", HORIZONTAL);
    printf("%s\n", TOP_RIGHT);

    for (int i = 0; i < height; i++) {
        printf("%s", VERTICAL);
        for (int j = 0; j < width - 2; j++) printf(" ");
        printf("%s\n", VERTICAL);
    }

    printf("%s", BOTTOM_LEFT);
    for (int i = 0; i < width - 2; i++) printf("%s", HORIZONTAL);
    printf("%s\n", BOTTOM_RIGHT);
}

void display_progress_bar(QuizState state) {
    int barWidth = 40;
    int progress = (state.current_question * barWidth) / state.total_questions;
    
    printf("\nProgress: [");
    for (int i = 0; i < barWidth; i++) {
        if (i < progress) printf("%s■%s", GREEN, RESET);
        else printf("□");
    }
    printf("] %d/%d\n", state.current_question, state.total_questions);
}

void display_welcome_screen() {
    system(CLEAR);
    printf("\n\n");
    center_text("╔══════════════════════════════════════╗");
    center_text("║        Modern Quiz Application        ║");
    center_text("╚══════════════════════════════════════╝");
    printf("\n\n");
    center_text("Press ENTER to start the quiz...");
    getchar();
}

void display_question(Question q, QuizState state) {
    system(CLEAR);
    printf("\n%s%s=== Question %d of %d ===%s\n\n", BOLD, CYAN, 
           state.current_question + 1, state.total_questions, RESET);
    
    display_progress_bar(state);
    
    printf("\n%s%s%s\n\n", YELLOW, q.question, RESET);
    
    for (int i = 0; i < 4; i++) {
        printf("%s%c) %s%s\n", CYAN, 'A' + i, RESET, q.options[i]);
    }
    printf("\nYour answer (A/B/C/D): ");
}

void display_result(QuizState state) {
    system(CLEAR);
    printf("\n\n");
    center_text("╔══════════════════════════════════════╗");
    center_text("║             Quiz Results             ║");
    center_text("╚══════════════════════════════════════╝");
    printf("\n\n");
    
    float percentage = (float)state.score / state.total_questions * 100;
    printf("%sFinal Score: %d/%d (%.1f%%)%s\n", BOLD, state.score, 
           state.total_questions, percentage, RESET);
    
    time_t end_time = time(NULL);
    int duration = end_time - state.start_time;
    printf("Time taken: %d minutes %d seconds\n", duration / 60, duration % 60);
    
    printf("\nPerformance: ");
    if (percentage >= 80) printf("%sExcellent!%s", GREEN, RESET);
    else if (percentage >= 60) printf("%sGood!%s", YELLOW, RESET);
    else printf("%sNeeds Improvement%s", RED, RESET);
    
    printf("\n\nPress ENTER to exit...");
    getchar();
}

void initialize_quiz(QuizState *state) {
    state->score = 0;
    state->current_question = 0;
    state->total_questions = sizeof(questions) / sizeof(questions[0]);
    state->start_time = time(NULL);
}

int main() {
    QuizState state;
    char answer;
    
    initialize_quiz(&state);
    display_welcome_screen();
    
    while (state.current_question < state.total_questions) {
        display_question(questions[state.current_question], state);
        scanf(" %c", &answer);
        getchar();
        
        int user_answer = toupper(answer) - 'A';
        
        if (user_answer == questions[state.current_question].correct_answer) {
            printf("\n%sCorrect!%s\n", GREEN, RESET);
            state.score++;
        } else {
            printf("\n%sIncorrect! The correct answer was %c.%s\n", 
                   RED, 'A' + questions[state.current_question].correct_answer, RESET);
        }
        
        printf("\nPress ENTER to continue...");
        getchar();
        state.current_question++;
    }
    
    display_result(state);
    return 0;
}
