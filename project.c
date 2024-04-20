#include <stdio.h>
#include <stdlib.h>
/*#include <windows.h>*/
#include <string.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#define MAX_QUESTIONS 5

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

typedef struct
{
    char question[256];
    char options[4][64];
    int correct_option;
} Question;

struct contestant
{
    char name[25];
    char username[25];
    char pwd[25];
    int age;
} d;

/*Function Declaration*/
void delay(int second);

void displayQuestion(Question q, int number, int value);

int checkAnswer(Question q, int user_answer);

void store_score(const char *player_name, int score);

const char *encryptPassword(char *password);

const char *decryptPassword(char *encryptedPassword);

void print_highest_score();

void store_username(const char *username);

int login();

void signup();

void gameplay();

void half(Question q);

void audience(Question q);

void start();

void rules();

void about();

int *generateRandomNumbers();

void playCorrectSound();

void cheque(int a);
/*End of function Declaration*/

// driver code
int main()
{
    int n = 0;
    printf("\n\t\t\t1.Login\n\t\t\t2.Sign up\n\t\tPlease enter your choice:-");
    fflush(stdin);
    scanf("%d", &n);

    switch (n)
    {
    case 1:
    {
        printf("\n\n\n\n");
        login();
        start();
        char str;
        printf("To check highest score enter h:");
        scanf("%s", str);
        if (str == 'h')
        {
            print_highest_score();
        }
        break;
    }
    case 2:
    {
        printf("\n\n\n\n");
        signup();
        start();
        char str;
        printf("To check highest score enter h:");
        scanf("%s", str);
        if (str == 'h')
        {
            print_highest_score();
        }
        break;
    }
    default:
    {
        printf("Please enter correct data.");
        system("cls");
    }
    }
    // gameplay
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void displayQuestion(Question q, int number, int value)
{
    printf("Here is question no:%d for %d.rs \n", number, value);
    printf("%s\n", q.question);
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, q.options[i]);
    }
}

// function to check the answer
int checkAnswer(Question q, int user_answer)
{
    return (user_answer == q.correct_option);
}

void store_score(const char *player_name, int score)
{
    FILE *file = fopen("scores.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s: %d\n", player_name, score);
    fclose(file);
}

// Function to print the highest score
void print_highest_score()
{
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char line[100];
    int max_score = -1;
    char max_player[50];

    // Loop through each line in the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char player[50];
        int score;
        // Parse player name and score from line
        sscanf(line, "%[^:]: %d", player, &score);
        // Check if current score is higher than max_score
        if (score > max_score)
        {
            max_score = score;
            strcpy(max_player, player);
        }
    }

    if (max_score == -1)
    {
        printf("No scores found.\n");
    }
    else
    {
        printf("Highest Score: %s: %d\n", max_player, max_score);
    }

    fclose(file);
}

// Function to store a new username in a file
void store_username(const char *username)
{
    FILE *file = fopen("usernames.txt", "a"); // Open file in append mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s\n", username); // Write the username to the file
    fclose(file);                    // Close the file
}

// Function to perform login
int login()
{
    char u[25], pw[25];
    FILE *fp;
    fp = fopen("b.txt", "rb");
    printf("\t\tUsername:-  ");
    scanf("%s", u);
    printf("\t\tPassword:-  ");
    fflush(stdin);
    scanf("%s", pw);
    while (!feof(fp))
    {
        fread(&d, sizeof(d), 1, fp);
        if ((strcmp(d.username, u) == 0) && (strcmp(decryptPassword(d.pwd), pw) == 0))
        {
            printf("You are successfully logged in.....\n");
            system("cls");
            getch();
            return 1;
        }
    }
    fclose(fp);
    printf("\n\t\tPlease enter valid username or password.");
    getch();
    system("cls");
    main();
    return 0;
}

void signup()
{
    FILE *fp, *fp1;
    fp = fopen("b.txt", "ab");
    fp1 = fopen("p.txt", "a");
    printf("Enter your name:-\t");
    scanf("%s", d.name);
    printf("Enter your username:-\t");
    fflush(stdin);
    scanf("%s", d.username);
    fprintf(fp1, "%s ", d.username);
    printf("Enter your password:-\t");
    fflush(stdin);
    scanf("%s", d.pwd);
    char str = encryptPassword(d.pwd);
    strcpy(d.pwd, encryptPassword(d.pwd));
    printf("Enter your age:-     \t");
    scanf("%d", &d.age);
    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
    fclose(fp1);
    system("cls");
}

void half(Question q)
{
    int correct_option_index = q.correct_option;
    int wrong_option_1_index = (correct_option_index + 1) % 4;
    int wrong_option_2_index = (correct_option_index + 3) % 4;

    printf("Option %d and %d are wrong", wrong_option_1_index, wrong_option_2_index);
}

void audience(Question q)
{
    int num = (rand()) % 4;
    int correct = q.correct_option;
    if (num == 0)
    {
        /*Audience Poll helps the contestant*/
        int ghh = (rand()) % 50 + 50;
        printf("%d audience believe that the ans is %d", ghh, correct);
    }
    if (num == 1)
    {
        int ghh = (rand()) % 30 + 20;
        printf("%d audience believe that the ans is %d", ghh, correct);
    }
    if (num == 2)
    {
        int ghh = (rand()) % 20 + 10;
        printf("%d audience believe that the ans is %d", ghh, correct);
    }
    if (num == 3)
    {
        int ghh = (rand()) % 20;
        printf("%d audience believe that the ans is %d", ghh, correct);
    }
}

void rules()
{
    printf("\n\t\t************Before we Start The Game**************\n\n\t\t********* Read The Following Rules And Regulations-*********\n\n");
    printf("\n\n\t\t1. Game is divided into three levels:\n\t\t1.Easy\t\t\t2.Medium\t\t\t3.Hard  \n");
    printf("\n\n\t\t2. Each level contains 5 questions which you\n\t\t have to answer one by one .\n");
    printf("\n\t\t3. Each question has a fixed prize money starting from\n\t\t Rs. 1000 to Rs. 1 Crore which will increase depending \n\t\tupon toughness of the question.\n");
    printf("\n\t\t4.Each correct answer will take you to a higher question\n\t\t and you will earn some money .\n");
    printf("\n\t\t5. If you will give a wrong answer you will fall down\n\t\t to level's starting point and loose your earned money.\n");
    printf("\n\t\t6. You may use  two Life Lines during your game:\n\t\t 1.50-50(two incorrect options will get vanished)\n\t\t 2.Expert Advice:(you can take help from the audience.)\n ");
    printf("\n\t\t7.You may quit the game anytime .");
}

void about()
{
    printf("*            P25 G1-10                                 \n*");
    printf("*            Srishant Dagumalli-2301AI25               \n*");
    printf("*            Vishwadeep Tomar-2301CB56                 \n*");
    printf("*            Ansh Gupta-2301CT25                       \n*");
    printf("*            Ashish Yadav-2301CE46                     \n*");
    printf("*            Venkata Pathi Azmeera-2301CE59            \n*");
    printf("*            Krishan Kumawat-2301CS25                  \n*");
    printf("*            Sreyas Kotha-2301CS53                     \n*");
    printf("*            Aditya Aryan-2301EE29                     \n*");
    printf("*            Vignesh Devarakonda-2301EC37              \n*");
    printf("********************************************************\n");
}

const char *encryptPassword(char *password)
{
    int key = 3; // Shift key for Caesar Cipher
    char ch;

    for (int i = 0; password[i] != '\0'; ++i)
    {
        ch = password[i];

        // Encrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;
            if (ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
            password[i] = ch;
        }
        // Encrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if (ch > 'z')
            {
                ch = ch - 'z' + 'a' - 1;
            }
            password[i] = ch;
        }
    }
    return password;
}

int *generateRandomNumbers()
{
    static int numbers[5];
    int i, j;
    srand(time(NULL)); // Seed the random number generator with current time

    // Generate 5 random numbers
    for (i = 0; i < 5; i++)
    {
        int num;
        do
        {
            num = rand() % 8 + 1; // Generate random number between 1 and 8
            // Check if the number is already present
            for (j = 0; j < i; j++)
            {
                if (numbers[j] == num)
                {
                    num = 0; // Set num to 0 to indicate it's a duplicate
                    break;
                }
            }
        } while (num == 0); // Repeat until a unique number is generated
        numbers[i] = num;   // Store the unique number
    }
    return numbers;
}

const char *decryptPassword(char *encryptedPassword)
{
    int key = 3;
    char ch;

    for (int i = 0; encryptedPassword[i] != '\0'; ++i)
    {
        ch = encryptedPassword[i];

        // Decrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
            encryptedPassword[i] = ch;
        }
        // Decrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
            encryptedPassword[i] = ch;
        }
    }
    return encryptedPassword;
}

void start()
{
    printf("\n\n\t\t\t\t\t*** MAIN MENU ***");
    printf("\n\n\t\t\t\t\t1. Start Game");
    printf("\n\t\t\t\t\t2. Rules");
    printf("\n\t\t\t\t\t3. About the Game");
    printf("\n\t\t\t\t\t4. Log out User");
    printf("\n\t\t\t\t\t5. Exit");
    int dfc;
    do
    {
        printf("\n\n\t\t\t\t\tEnter your choice >>>");
        scanf("%d", &dfc);

        if (dfc == 1)
        {
            gameplay();
        }
        if (dfc == 2)
        {
            rules();
            delay(1);
            start();
        }
        if (dfc == 3)
        {
            about();
            delay(1);
            start();
        }
        else
        {
            exit(0);
        }
        system("cls");
    } while (dfc != 5);
}

void gameplay()
{
    srand(time(NULL));


    printf(YELLOW);
    printf("******************************\n");
    printf("*                             *");
    printf("** WELCOME TO THE KBC GAME**\n*");
    printf("*         --------------    \n*");
    printf("*                           \n*");
    printf("*                           \n*");
    printf("*******************************");

    printf(RESET);

    printf(YELLOW);

    printf("\n\t\t************Before we Start The Game**************\n\n\t\t********* Read The Following Rules And Regulations-*********\n\n");
    printf("\n\n\t\t1. Game is divided into three levels:\n\t\t1.Easy\t\t\t2.Medium\t\t\t3.Hard  \n");
    printf("\n\n\t\t2. Each level contains 5 questions which you\n\t\t have to answer one by one .\n");
    printf("\n\t\t3. Each question has a fixed prize money starting from\n\t\t Rs. 1000 to Rs. 1 Crore which will increase depending \n\t\tupon toughness of the question.\n");
    printf("\n\t\t4.Each correct answer will take you to a higher question\n\t\t and you will earn some money .\n");
    printf("\n\t\t5. If you will give a wrong answer you will fall down\n\t\t to level's starting point and loose your earned money.\n");
    printf("\n\t\t6. You may use  two Life Lines during your game:\n\t\t 1.50-50(two incorrect options will get vanished)\n\t\t 2.Expert Advice:(you can take help from the audience.)\n ");
    printf("\n\t\t7.You may quit the game anytime .");

    // Question Set
    Question easy_questions[MAX_QUESTIONS] = {
        {"Which bird lays the largest egg?",
         {"Owl", "Ostrich", "Kingfisher", "Woodpecker"},
         2},
        {"How many legs does a spider have?",
         {"7", "8", "6", "5"},
         2},
        {"Where does the President of the United States "
         "live while in office?",
         {"The White House", "The Parliament",
          "House of Commons", "Washington DC"},
         1},
        {"Which state is famous for Hollywood?",
         {"Sydney", "California", "New York", "Paris"},
         2},
        {"What is a group of lions called?",
         {"Drift", "Pride", "Flock", "Drove"},
         2},
        {"What is the capital of France?",
         {"A. London", "B. Paris", "C. Rome", "D. Berlin"},
         2},
        {"What is the color of an apple?",
         {"A. Red", "B. Green", "C. Blue", "D. Yellow"},
         1},
        {"How many legs does a cat have?",
         {"A. 2", "B. 4", "C. 6", "D. 8"},
         2}};

    Question medium_questions[MAX_QUESTIONS] = {
        {"Who is often credited with creating the world’ s first car?",
         {"Karl Benz", "Henry Ford", "William C. Durant", "Rick Wagoner"},
         1},
        {"Who is the famous pop band that was called \" Kara’s Flowers \" up until 2001?",
         {"Coldplay", "Linkin Park", "Journey", "Maroon 5"},
         4},
        {"Directing Schindler’s List gave who their first Oscar for Best Picture?",
         {"Christopher Nolan", "Martin Scorsese", "Steven Spielberg", "Quentin Tarantino"},
         3},
        {"In what year were the first Air Jordan sneakers released?",
         {"1984", "1992", "1991", "2020"},
         1},
        {"Which athlete won the Tour de France every year from 1999 - 2005?",
         {"Neil Arnstrong", "Michael Jordan", "Lance Armstrong", "Tom Brady"},
         3},
        {
            "Which country is famous for the Great Wall?",
            {" China", " Japan", "India", "Egypt"},
            1 // Correct option is A
        },
        {
            "Who wrote the play 'Romeo and Juliet'?",
            {"William Shakespeare", "Jane Austen", "Charles Dickens", " Mark Twain"},
            1 // Correct option is A
        },
        {
            "Which planet is known as the 'Red Planet'?",
            {" Venus", "Mars", "Jupiter", "Mercury"},
            2 // Correct option is B
        }};

    Question hard_question[MAX_QUESTIONS] =
        {
            {"What is the rarest blood type among humans?",
             {"AB-", "AB+", "O+", "A+"},
             1},
            {"Before founding Facebook, Mark Zuckerberg created a website that allowed users to compare the attractiveness of two people side by side. What was the name of this website?",
             {"Facemash", "Monster.inc", "Harvard Connection", "Facescale"},
             1},
            {"Which African country is the world’s smallest by land area?",
             {"Vatican City", "Nigeria", "Seychelles", "Niger"},
             3},
            {"Who was the first human to journey into space?",
             {"Yuri Gagrin", "Neil Armstrong", "Kalpana Chawla", "Laika"},
             1},
            {"Barani, Rudolph, and Randolph are all techniques used in which sport?",
             {"Hula Hoop", "Trampoline", "Synchronied Swimming", "Acrobatics"},
             2},
            {"Who wrote the novel 'The Great Gatsby'?",
             {" F. Scott Fitzgerald", "Ernest Hemingway", "Mark Twain", "William Faulkner"},
             1},
            {"In which year did the movie 'Rocky' release?",
             {"1976", "1982", " 1990", " 2001"},
             1},
            {"Which team won the FIFA World Cup in 2014?",
             {" Brazil", "Argentina", "Germany", "Spain"},
             3}};

    // Array of struct data-type

    int end = 0;

    Question ez[MAX_QUESTIONS];
    memcpy(ez, easy_questions,
           sizeof(easy_questions));

    int num_questions = MAX_QUESTIONS;

    int prize_money = 0;

    int score = 0;

    int fiffif = 1;

    int exp = 1;

    int easy[5] = {1000, 2000, 3000, 5000, 100000};

    printf("Hola! Here's your Quiz Game!\n");

    int *randomNumbers = generateRandomNumbers();
    for (int i = 0; i < 5; i++)
    {
        Question current_question = ez[randomNumbers[i]];

        printf(YELLOW);

        displayQuestion(current_question, i + 1, easy[i]);

        printf(RESET);

        delay(1);

        if ((fiffif == 1) & (exp == 1))
        {
            printf("You have a fifty-fifty and audience advice \n");
            printf("To use  fifty-fifty lifeline click on f\n");
            printf("To use the exert advice lifeline click on e\n");
            printf("To continue to the question click on any other \n");
            char s;
            scanf("%s", &s);
            if (s == 'f')
            {
                half(current_question);
                fiffif -= 1;
            }
            if (s == 'e')
            {
                audience(current_question);
                exp -= 1;
            }
        }
        else if (fiffif == 1 && exp == 0)
        {
            printf("You have a fifty-fifty lifeline \n");
            printf("To use  fifty-fifty lifeline click on f\n");
            printf("To continue to the question click on any other character\n");

            char s;
            scanf("%s", &s);
            if (s == 'f')
            {
                half(current_question);
                fiffif -= 1;
            }
        }
        else if (fiffif == 0 && exp == 1)
        {
            printf("You have a audience advice lifeline \n");
            printf("To use the exert advice lifeline click on e\n");
            printf("To continue to the question click on any other character");
            char s;
            scanf("%s", &s);
            if (s == 'e')
            {
                audience(current_question);
                exp -= 1;
            }
        }
        else
        {
            printf("No lifelines are remaining\n");
        }

        delay(1);
        int user_answer;

        printf("Enter your answer (1-4) \n");
        printf("Enter option 5 to exit:");
        scanf("%d", &user_answer);

        if (user_answer >= 1 && user_answer <= 4)
        {
            if (checkAnswer(current_question,
                            user_answer))
            {
                printf("Correct!\n");
                score = easy[i];
            }
            else
            {
                printf("Incorrect. The correct answer is "
                       "%d. %s\n",
                       current_question.correct_option,
                       current_question.options
                           [current_question.correct_option - 1]);

                printf("Game is over \n");
                printf("You have earned 0 rupees.");
                score = 0;
                end = 1;
                break;
            }
        }
        else
        {
            if (user_answer == 5)
            {
                printf("Game is over \n");
                printf("You have earned %d rupees", score);
            }
            else
            {
                printf("Invalid choice. Please enter a number "
                       "between 1 and 4.\n");
                printf("Game is over \n");
                printf("You have earned 0 rupees");
                end = 1;
                break;
            }
        }
        system("cls");
    }

    if (!(end))
    {
        Question mid[MAX_QUESTIONS];
        memcpy(mid, medium_questions,
               sizeof(medium_questions));

        int med[5] = {20000, 40000, 80000, 1600000, 3200000};
        for (int i = 0; i < 5; i++)
        {
            int *randomNumbers = generateRandomNumbers();
            printf(YELLOW);

            Question current_question = mid[randomNumbers[i]];

            printf(RESET);

            displayQuestion(current_question, i + 6, med[i]);

            delay(1);

            if ((fiffif == 1) & (exp == 1))
            {
                printf("You have a fifty-fifty and audience advice \n");
                printf("To use  fifty-fifty lifeline click on f\n");
                printf("To use the exert advice lifeline click on e\n");
                printf("To continue to the question click on any other \n");
                char s;
                scanf("%s", &s);
                if (s == 'f')
                {
                    half(current_question);
                    fiffif -= 1;
                }
                if (s == 'e')
                {
                    audience(current_question);
                    exp -= 1;
                }
            }
            else if (fiffif == 1 && exp == 0)
            {
                printf("You have a fifty-fifty lifeline \n");
                printf("To use  fifty-fifty lifeline click on f\n");
                printf("To continue to the question click on any other character\n");

                char s;
                scanf("%s", &s);
                if (s == 'f')
                {
                    half(current_question);
                    fiffif -= 1;
                }
            }
            else if (fiffif == 0 && exp == 1)
            {
                printf("You have a audience advice lifeline \n");
                printf("To use the exert advice lifeline click on e\n");
                printf("To continue to the question click on any other character");
                char s;
                scanf("%s", &s);
                if (s == 'e')
                {
                    audience(current_question);
                    exp -= 1;
                }
            }
            else
            {
                printf("No lifelines are remaining\n");
            }

            delay(1);

            int user_answer;
            printf("Enter your answer (1-4) \n");
            printf("Enter 5 in order to quit the game:");
            scanf("%d", &user_answer);

            if (user_answer >= 1 && user_answer <= 4)
            {
                if (checkAnswer(current_question,
                                user_answer))
                {
                    printf("Correct!\n");
                    score = med[i];
                }
                else
                {
                    if (user_answer == 5)
                    {
                        printf("Game is over \n");
                        printf("You have earned %d rupees", score);
                        end = 1;
                        break;
                    }
                    printf("Incorrect. The correct answer is "
                           "%d. %s\n",
                           current_question.correct_option,
                           current_question.options
                               [current_question.correct_option - 1]);

                    printf("Game is over \n");
                    printf("You have earned %d rupees.", easy[4]);
                    score = easy[4];
                    end = 1;
                    break;
                }
            }
            else
            {
                if (user_answer == 5)
                {
                    printf("Game is over \n");
                    printf("You have earned %d rupees", score);
                    end = 1;
                    break;
                }
                else
                {
                    printf("Invalid choice. Please enter a number "
                           "between 1 and 4.\n");
                    printf("Game is over \n");
                    printf("You have earned %d rupees", easy[4]);
                    score = easy[4];
                    end = 1;
                    break;
                }
            }
            system("cls");
        }

        if (!(end))
        {
            int hard[5] = {625000, 1250000, 2500000, 5000000, 10000000};

            Question herd[MAX_QUESTIONS];

            memcpy(herd, hard_question,
                   sizeof(hard_question));

            int *randomNumbers = generateRandomNumbers();

            for (int i = 0; i < 5; i++)
            {
                int random_index = rand() % num_questions;

                printf(YELLOW);

                Question current_question = herd[randomNumbers[i]];

                displayQuestion(current_question, i + 11, hard[i]);

                printf(RESET);
                
                delay(1);

                if ((fiffif == 1) & (exp == 1))
                {
                    printf("You have a fifty-fifty and audience advice \n");
                    printf("To use  fifty-fifty lifeline click on f\n");
                    printf("To use the exert advice lifeline click on e\n");
                    printf("To continue to the question click on any other \n");
                    char s;
                    scanf("%s", &s);
                    if (s == 'f')
                    {
                        half(current_question);
                        fiffif -= 1;
                    }
                    if (s == 'e')
                    {
                        audience(current_question);
                        exp -= 1;
                    }
                }
                else if (fiffif == 1 && exp == 0)
                {
                    printf("You have a fifty-fifty lifeline \n");
                    printf("To use  fifty-fifty lifeline click on f\n");
                    printf("To continue to the question click on any other character\n");

                    char s;
                    scanf("%s", &s);
                    if (s == 'f')
                    {
                        half(current_question);
                        fiffif -= 1;
                    }
                }
                else if (fiffif == 0 && exp == 1)
                {
                    printf("You have a audience advice lifeline \n");
                    printf("To use the exert advice lifeline click on e\n");
                    printf("To continue to the question click on any other character");
                    char s;
                    scanf("%s", &s);
                    if (s == 'e')
                    {
                        audience(current_question);
                        exp -= 1;
                    }
                }
                else
                {
                    printf("No lifelines are remaining\n");
                }

                delay(1);
                int user_answer;
                printf("Enter your answer (1-4): ");
                scanf("%d", &user_answer);

                if (user_answer >= 1 && user_answer <= 4)
                {
                    if (checkAnswer(current_question,
                                    user_answer))
                    {
                        printf("Correct!");
                        score = hard[i];
                    }
                    else
                    {
                        printf("Incorrect. The correct answer is "
                               "%d. %s\n",
                               current_question.correct_option,
                               current_question.options
                                   [current_question.correct_option - 1]);

                        printf("Game is over \n");
                        printf("You have earned %d rupees.", med[4]);
                        score = med[4];
                        end = 1;
                        break;
                    }
                }
                else
                {
                    if (user_answer == 5)
                    {
                        printf("Game is over \n");
                        printf("You have earned %d rupees", score);
                        end = 1;
                        break;
                    }
                    else
                    {
                        printf("Invalid choice. Please enter a number "
                               "between 1 and 4.\n");
                        printf("Game is over \n");
                        printf("You have earned %d rupees", med[4]);
                        score = med[4];
                        end = 1;
                        break;
                    }
                }
            }
            system("cls");
        }
    }
    if (score > easy[4])
    {
        cheque(score);
    }
    store_score(d.username, score);
}

void cheque(int a)
{
    system("cls");
    printf("\n\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("\t$                             *                                     $\n");
    printf("\t$                           ****                                    $\n");
    printf("\t$                         ********                                  $\n");
    printf("\t$                       ************                                $\n");
    printf("\t$                   ****AXIS   BANK****           Date :12/11/18    $\n");
    printf("\t$                                                                   $\n");
    printf("\t$   PAY:   Mr  Username          %s              OR ORDER         $\n", d.username);
    printf("\t$                                                                   $\n");
    printf("\t$                                                                   $\n");
    printf("\t$   RUPEES   %d                                                 $\n", a);
    printf("\t$                                                                   $\n");
    printf("\t$   A/C No:3246634582652    A/C Payee : _________________           $\n");
    printf("\t$                                                                   $\n");
    printf("\t$                                                                   $\n");
    printf("\t$  [MULTY CITY CHEQUE: Payable at par at All branches of AB ]       $\n");
    printf("\t$                                                                   $\n");
    printf("\t$                                          __________________       $\n");
    printf("\t$                                          Please sign above        $\n");
    printf("\t$              *950020*   *695002032*: 002060*                      $\n");
    printf("\t$                                                                   $\n");
    printf("\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
    Beep(1000, 400);
    Beep(500, 400);
    Beep(1200, 400);
    printf("\n\n\t\t\tPress any key to continue......");
    getch();
}
