#include<stdio.h>

void main(){
	int n,nz=0;
	printf("Enter the size of matrix : ");
	scanf("%d",&n);
	int a[n][n],i,j;

    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &a[i][j]);
            if(a[i][j]!=0)
            	nz++;
		}
    }

    printf("The entered matrix is:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    
    int az[nz+1][3],k=1;
    az[0][0] = n;
    az[0][1] = n;
    az[0][2] = nz;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if(a[i][j]!=0)
			{
            	az[k][0] = i+1;
    			az[k][1] = j+1;
    			az[k][2] = a[i][j];
    			k++;
            }          
        }
    }
    
    printf("The sparse matrix is:\n");
    for (i = 0; i < nz+1; i++) {
        for (j = 0; j < 3; j++) {
        	printf("%d ", az[i][j]);
        }
        printf("\n");
    }
    
    
    int azt[nz+1][3];
    for (i = 0; i < nz+1; i++) {
        for (j = 0; j < 3; j++) {
		azt[i][j]  = az[i][j];
        }
    }
    
    for (i = 0; i < nz+1; i++) {
        k=azt[i][0];
        azt[i][0] = azt[i][1];
        azt[i][1]=k;
    }
    
    printf("The transpose sparse matrix is:\n");
    for (i = 0; i < nz+1; i++) {
        for (j = 0; j < 3; j++) {
        	printf("%d ", azt[i][j]);
        }
        printf("\n");
    }
    
    for (i = 1; i < nz + 1; i++) {
        for (j = i + 1; j < nz + 1; j++) {
            if (azt[i][0] > azt[j][0] || (azt[i][0] == azt[j][0] && azt[i][1] > azt[j][1])) {
                int temp0 = azt[i][0];
                int temp1 = azt[i][1];
                int temp2 = azt[i][2];

                azt[i][0] = azt[j][0];
                azt[i][1] = azt[j][1];
                azt[i][2] = azt[j][2];

                azt[j][0] = temp0;
                azt[j][1] = temp1;
                azt[j][2] = temp2;
            }
        }
    }

    printf("The sorted transpose sparse matrix is:\n");
    for (i = 0; i < nz + 1; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", azt[i][j]);
        }
        printf("\n");
    }
}