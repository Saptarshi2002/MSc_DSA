#include <stdio.h>
#include <string.h>

#define MAX 100

void printLCS(char X[], char Y[], int m, int n, int dp[MAX][MAX]) {
    int index = dp[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';
    
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    printf("LCS: %s\n", lcs);
}

int LCS(char X[], char Y[], int m, int n) {
    int dp[MAX][MAX];
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }
    
    printLCS(X, Y, m, n, dp);
    return dp[m][n];
}

int main() {
    char X[MAX], Y[MAX];
    printf("Enter first string: "); 
    scanf("%s", X);
    printf("Enter second string: ");
    scanf("%s", Y);
    
    int m = strlen(X);
    int n = strlen(Y);
    
    int length = LCS(X, Y, m, n);
    printf("Length of LCS: %d\n", length);
    
    return 0;
}
