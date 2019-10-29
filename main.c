#include <stdio.h>

#define NO_FOOD_TYPE 3
#define NO_FOOD_SUBTYPE 4
#define NO_DRINKS 4

int main() {

    char username[20], password[20];
    char foodTypes[NO_FOOD_TYPE][20] = {"Pizza", "Pasta", "Salad"};
    int foodTypeChoice = -1;
    int foodSubtypePrices[NO_FOOD_TYPE][4] = {
            {21, 23, 19},
            {23, 21},
            {23, 22, 19, 21}
    };
    int noFoodSubtypes[NO_FOOD_TYPE] = {3, 2, 4};
    char foodSubtypes[NO_FOOD_TYPE][NO_FOOD_SUBTYPE][20] = {
            {"Pizza con Pollo", "Pizza Diavola", "Pizza Margherita"},
            {"Chicken alfredo", "Mac&cheese"},
            {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"}
    };
    int foodSubtypeChoice = -1;
    char drinkOptions[NO_DRINKS][20] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    int drinkOptionPrices[NO_DRINKS] = {5, 5, 5, 4};
    int drinkChoice = -1;
    int cutleryChoice = -1;
    char additionalInfo[100];
    char choice;
    int state = 0;
    int isOrderConfirmed = 0;

    while(isOrderConfirmed == 0) {
        switch (state) {
            //log in
            case 0: {
                printf("Welcome to Food Thingies!\n");
                printf("Please sign in to continue!\n");
                printf("---Username:\n");
                gets(username);
                printf("---Password:\n");
                gets(password);
                state++;
                break;
            }
            //choose food
            case 1: {
                printf("Please choose your meal:\n");
                int i;
                for (i = 0; i < NO_FOOD_TYPE; i++) {
                    putchar('a'+i); printf(") %s\n", foodTypes[i]);
                }
                i = NO_FOOD_TYPE;
                putchar('a'+i); printf(") Go back\n");
                choice = getchar();
                getchar();
                if (choice - 'a' == i) {
                    state--;
                    break;
                }
                if ((choice-'a'<0) || (choice-'a' >i)) {
                    printf("Invalid answer, please select again.\n");
                    break;
                }
                foodTypeChoice = choice - 'a';
                state++;
                break;
            }
            //choose food subtype
            case 2: {
                int i;
                printf("Please choose the type of %s:\n", foodTypes[foodTypeChoice]);
                for (i = 0; i < noFoodSubtypes[foodTypeChoice]; i++) {
                    putchar('a'+i); printf(") %s: %d\n", foodSubtypes[foodTypeChoice][i], foodSubtypePrices[foodTypeChoice][i]);
                }
                i = noFoodSubtypes[foodTypeChoice];
                putchar('a'+i); printf(") Go back\n");
                choice = getchar();
                getchar();
                if (choice - 'a'==i) {
                    state--;
                    break;
                }
                if ((choice-'a'<0) || (choice-'a' >i)) {
                    printf("Invalid answer, please select again.\n");
                    break;
                }
                foodSubtypeChoice = choice - 'a';
                state++;
                break;
            }
            //choosing drink
            case 3: {
                printf("Please choose a drink to go with your %s:\n", foodTypes[foodTypeChoice]);
                int i;
                for ( i = 0; i < NO_DRINKS; i++) {
                    putchar('a'+i); printf(") %s: %d\n", drinkOptions[i], drinkOptionPrices[i]);
                }
                i = NO_DRINKS;
                putchar('a'+i); printf(") No, thanks!\n");
                i++;
                putchar('a'+i); printf(") Go back\n");
                choice= getchar();
                getchar();
                if(choice - 'a' == i) {
                    state--;
                    break;
                }
                if ((choice-'a'<0) || (choice-'a' >i)) {
                    printf("Invalid answer, please select again.\n");
                    break;
                }
                drinkChoice = choice - 'a';
                state++;
                break;
            }
            //cutlery
            case 4: {
                printf("Do you want cutlery?\n");
                printf("a) Yes\n");
                printf("b) No\n");
                printf("c) Go back\n");
                choice = getchar();
                getchar();
                int choiceInt;
                choiceInt = choice - 'a';
                switch (choiceInt) {
                    case 0: {
                        cutleryChoice = 1;
                        state++;
                        break;
                    }
                    case 1: {
                        cutleryChoice = 0;
                        state++;
                        break;
                    }
                    case 2: {
                        state--;
                        break;
                    }
                    default: {
                        printf("Invalid answer, please select again.\n");
                        break;
                    }
                }
                break;
            }
            //additional info
            case 5: {
                printf("Any additional information?\n");
                gets(additionalInfo);
                printf("a) Confirm additional information\n"
                       "b) Go back\n");
                choice = getchar();
                getchar();
                int choiceInt;
                choiceInt = choice - 'a';
                switch (choiceInt) {
                    case 0: {
                        state++;
                        break;
                    }
                    case 1: {
                        state--;
                        break;
                    }
                    default: {
                        printf("Invalid answer, please select again.\n");
                        break;
                    }
                }
                break;
            }
            //confirmation
            case 6: {
                printf("-----------------\n"
                       "This is your order:\n"
                       "Name: %s\n"
                       "Food items:\n"
                       "--%s: %d\n", username, foodSubtypes[foodTypeChoice][foodSubtypeChoice], foodSubtypePrices[foodTypeChoice][foodSubtypeChoice]);
                if (drinkChoice != NO_DRINKS) {
                    printf("--%s: %d\n", drinkOptions[drinkChoice], drinkOptionPrices[drinkChoice]);
                }
                printf("Cutlery: ");
                if (cutleryChoice == 0) printf("no\n");
                else printf("yes\n");
                printf("Additional information: %s\n", additionalInfo);
                printf("Payment amount: %d\n", foodSubtypePrices[foodTypeChoice][foodSubtypeChoice] + drinkOptionPrices[drinkChoice]);
                printf("-----------------\n");
                printf("a) Confirm order\n"
                       "b) Go back\n");
                choice = getchar();
                getchar();
                int choiceInt;
                choiceInt = choice - 'a';
                switch (choiceInt) {
                    case 0: {
                        printf("Order confirmed! Thank you for buying from us, %s!", username);
                        isOrderConfirmed = 1;
                        break;
                    }
                    case 1: {
                        state--;
                        break;
                    }
                    default: {
                        printf("Invalid answer, please select again.\n");
                        break;
                    }
                }
                break;
            }
        }
    }

    return 0;
}