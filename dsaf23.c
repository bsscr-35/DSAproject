#include <stdio.h>
#include <stdlib.h>

struct Match {
    int player1;
    int player2;
    int winner;
    struct Match* next;
};

struct Match* head = NULL;

void recordResult(int player1, int player2, int winner) {
    struct Match* newMatch = (struct Match*)malloc(sizeof(struct Match));
    newMatch->player1 = player1;
    newMatch->player2 = player2;
    newMatch->winner = winner;
    newMatch->next = NULL;


    if (head == NULL) {
        head = newMatch;
    } else {
        struct Match* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newMatch;
    }
}


void getPlayerPath(int playerId) {
    struct Match* temp = head;
    int found = 0;

    printf("Match history for Player %d:\n", playerId);
    while (temp != NULL) {
        if (temp->player1 == playerId || temp->player2 == playerId) {
            printf("  %d vs %d -> Winner: %d\n",
                   temp->player1, temp->player2, temp->winner);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("  No matches found for player %d.\n", playerId);
}


int main() {
    recordResult(1, 2, 1);
    recordResult(3, 4, 4);
    recordResult(1, 4, 1);
    recordResult(2, 3, 3);

    getPlayerPath(1);
    getPlayerPath(3);
    getPlayerPath(5);

    return 0;
}