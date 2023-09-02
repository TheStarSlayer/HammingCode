#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    char *binstr;
    binstr = (char*) malloc (50*sizeof(char));

    printf("Enter binary number: ");
    scanf("%s", binstr);

    int ini_lenbin = strlen(binstr);
    int fin_lenbin = ini_lenbin;

    int i, j = 0;
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
    hammingcode[fin_lenbin] = '\0';

    for (j = 0; j < n_parity; j++)
    {
        hammingcode[paritybits[j]] = '2';
    }
    j = 0;

    for (i = 0; i < ini_lenbin;)
    {
        if (hammingcode[j] == '2')
        {
            j++;
        }
        else
        {
            hammingcode[j] = binstr[i];
            j++;
            i++;
        }
    }

    // We have successfully generated hamming code --partially, but good job nonetheless
    // Should have taken lesser time, but it's okay
    // We put 2s in the position of parity bits
    // Now we need to associate the bits to each parity bit    

    int count, sc, skip=0, k;

    for (i = fin_lenbin-1; i >= 0; i--)
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

    printf("\nThe Hamming code of the given binary number is %s", hammingcode);

    return 0;
}

// Hamming code generated successfully!!
// Now the code requires refactoring!!