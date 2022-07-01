#include <cs50.h>
#include <stdio.h>
#include <string.h>

//MAX NUMBER OF CANDIDIATES
#define MAX 9

void print_winner(void);
bool vote(string name);



//CREATING THE CUSTOMARY DATA TYPE
typedef struct
{
    string name;
    int votes;
}
//WE CALL THIS DATA TYPE...
candidate;

//CREATING AN ARRAY OF DATA TYPE candidate...
candidate candidates[MAX];

//NUMBER OF CANDIDATES
int candidate_count;


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    //POPULATE ARRAY OF CANDIDATE
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    //PROMPT USER FOR THR NUMBER OF VOTERS
    int voters_count = get_int("Number of voters: ");

    //ITERATE OVER THE NUMBER OF VOTERS
    for (int i = 0; i < voters_count; i++)
    {
        //PROMPT USER FOR THE CANDIDATES THEY WISH TO VOTE FOR
        string name = get_string("vote: ");

        //CHECK FOR VALIDLITY IN THE VOTE; if the vote function retuns true, !vote will invert it to false thereby making the print "invalid code not to execute".
        //this is a smart way to avoid an "else if" condition in the if condition below when you want a negative condition.
        //FUNCTION "VOTE" WAS CALLED INSIDE THE IF CONDITION
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }


    //DISPLAY THE WINNER
    print_winner();

}

//FUNCTION TO VALIDATE THE CANDIDATE VOTED FOR, UPDATE THE VOTERS COUNT
bool vote(string name)
{
    //iterate over the number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0) //compare names at command line prompt & line 58 name
        {
            candidates[i].votes++; //add one vote to the votes of the verified candidates' vote
            return true; //this signifies that the code is done here
        }
    }
    return false;
}

//FUNCTION TO PRINT THE WINNER
void print_winner(void)
{
    int max = 0; //variable where the max vote of a candidate will be stored
    for (int i = 0; i < candidate_count; i++)
    {
        if (max < candidates[i].votes)
        {
            max = candidates[i].votes; //swap
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (max == candidates[i].votes) //if both variables are equal print them out
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
