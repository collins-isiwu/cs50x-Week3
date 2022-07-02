#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int j = 0; j < candidate_count; j++) //iterate over candidate_count
    {
        //check if the name given at line 73 is same as the candidate we are currently iterating over
        if (strcmp(candidates[j].name, name) == 0)  
        {
            //update the preferences array by assigning the current verified candidate to the current index of the preference array eg: preferences[voter][rank] = 3;
            preferences[voter][rank] = j;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == 0)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int maj = ((voter_count / 2) + 1);   //the winner in a runoff is always a majority (i.e half the vote plus one, more than 50%)
    //iterate over candidate_count only because candidates votes array already has the election results stored in it from line 151
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes >= maj)  //if any candidate has more votes than half + 1 or equal to maj
        {
            if (candidates[j].votes == candidates[j].votes)  //if by any chance it ends in a tie
            {
                printf("%s", candidates[j].name);  //print the name of the candidate(s) that passed the above test
                printf("\n");
                return true;
            }
        }
    }
    return false;
}
// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = candidates[0].votes;   //assign the first element to min
    for (int m = 0; m < candidate_count; ++m)
    {
        if (candidates[m].eliminated == 0)
        {
            if (candidates[m].votes < min)
            {
                min = candidates[m].votes; //swap
            }
        }
    }
    return min;
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (candidates[x].eliminated == 0)
        {
            if (candidates[x].votes != min)
            {
                return false;
            }
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    bool n = true;
    for (int z = 0; z < candidate_count; z++)
    {
        if (candidates[z].eliminated == false)
        {
            if (candidates[z].votes == min)
            {
                candidates[z].eliminated = n;
            }
        }
    }
    return;
}



uint8_t head[HEADER_SIZE];
    fread(head, HEADER_SIZE, 1, input);
    
    fwrite(head, HEADER_SIZE, 1, output);
