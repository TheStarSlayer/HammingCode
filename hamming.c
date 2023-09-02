#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void hammingset(char*, char*, int*, int, int);
void parityset(char*, int);

int main()
{
    char *binstr;
    binstr = (char*) malloc (50*sizeof(char));

    if (binstr != NULL)
    {    
        printf("Enter binary number: ");
        scanf("%s", binstr);

        int i;

        int ini_lenbin = strlen(binstr);
        for (i = 0; i < ini_lenbin; i++)
        {
            if (binstr[i] != '0' && binstr[i] != '1')
            {
                printf("Entered data bits are not binary. Try again..\n");
                return -1;
            }
        }
        int fin_lenbin = ini_lenbin;

        int j = 0;
        for (i = 0; i < fin_lenbin; i++)
        {
            if (pow(2,j) == i)
            {
                fin_lenbin++;
                j++;
            }
        }
        
        int n_parity = (fin_lenbin - ini_lenbin);
        int paritybits[n_parity];

        // At this point, we have found the final length of hamming code, and the number of parity bits
        // We have also created an array to store parity bits

        for (i = 0; i < n_parity; i++)
        {
            paritybits[i] = pow(2,i) - 1;
            paritybits[i] = fin_lenbin - paritybits[i] - 1;
        }

        char *hammingcode = (char*) malloc ((fin_lenbin+1)*sizeof(char));
        if (hammingcode != NULL)
        {
            hammingcode[fin_lenbin] = '\0';
            hammingset(binstr, hammingcode, paritybits, n_parity, ini_lenbin);   
            parityset(hammingcode, fin_lenbin);    

            printf("\nThe Hamming code of the given binary number is %s", hammingcode);
        }
        else
        {
            printf("hammingcode not created..please try again\n");
        }
    }
    else
    {
        printf("malloc failed. Please try again.\n");
    }
    return 0;
}

// Hamming code generated successfully!!

void hammingset(char ogdata[], char hammingcode[], int parity[], int n_parity, int length)
{
    int i,j;
    for (j = 0; j < n_parity; j++)
            {
                hammingcode[parity[j]] = '2';
            }
            j = 0;

            for (i = 0; i < length;)
            {
                if (hammingcode[j] == '2')
                {
                    j++;
                }
                else
                {
                    hammingcode[j] = ogdata[i];
                    j++;
                    i++;
                }
            }
}

void parityset(char hammingcode[], int length)
{
    int count = 0, sc = 0, skip=0, k,j,i;

    for (i = length-1; i >= 0; i--)
    {
        if (hammingcode[i] == '2')
        {
            j = pow(2,skip);
            k = i;
            while (k >= 0)
            {
                if (hammingcode[k] == '1')
                {
                    count++;
                }
                sc++;

                if (sc != j)
                {
                    k--;
                }
                else
                {
                    k = k - (j+1);
                    sc = 0;
                }     
            }
                    
            if (count%2 == 0)
            {
                hammingcode[i] = '0';
            }
            else
            {
                hammingcode[i] = '1';
            } 
            count = 0;
            sc = 0;        
            skip++;
        }
    }
}
