#include <stdio.h>

int main() {
    int array[100], loop, to_be_added = 2, position, inp;
    array[0] = 1;
    for (loop = 1; loop < 100; ++loop, ++to_be_added) {
        array[loop] = array[loop - 1] + to_be_added;
    }
    printf("Sequence:\n1 , 3 , 6 , 10 , 15 , 21\nGuess the next element: ");
    position = 6;
    scanf("%d", &inp);
    while (position < 100 && inp == array[position]) {
        printf("Very Good\nGuess the next element: ");
        ++position; scanf("%d", &inp);
    }
    if (position == 100)
        printf("You successfully cracked the game!\n");
    else
        printf("Ooopss! You lost!\n");
}