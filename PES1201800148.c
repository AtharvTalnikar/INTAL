#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "intal.h"

static void merge(char**, int, int, int);
static void mergeSort(char**,int,int);
static int binarySearch(char**, int, int,const char*);

char* intal_add(const char* intal1, const char* intal2)
{
    char *result = (char*)malloc(1001*sizeof(char));

    if(0 == (intal1[0]-'0'))
    {
        strcpy(result,intal2);
        return result;
    }
    else if(0 == (intal2[0]-'0'))
    {
        strcpy(result,intal1);
        return result;
    }

    int larger = strlen(intal1);
    int smaller = strlen(intal2);
    char *larger_intal = (char*)malloc(1001*sizeof(char));
    char *smaller_intal = (char*)malloc(1001*sizeof(char));
    strcpy(larger_intal,intal1);
    strcpy(smaller_intal,intal2);
    if(smaller > larger)
    {
        int temp = larger;
        larger = smaller;
        smaller = temp;
        strcpy(larger_intal,intal2);
        strcpy(smaller_intal,intal1);
    }
    
    int diff = larger-smaller;

    for(int i=larger-1;i>=diff;i--)
    {
        int num1 = larger_intal[i]-'0';
        int num2 = smaller_intal[i-diff]-'0';
        result[i] = (num1+num2)+'0';
    }
    for(int i=diff-1;i>=0;i--)
    {
        result[i] = larger_intal[i];
    }

    for(int i=larger-1;i>0;i--)
    {
        int num = result[i]-'0';
        if(num>9)
        {
            result[i] = (num-10)+'0';
            int temp = result[i-1]-'0';
            result[i-1] = (temp+1)+'0';
        }
    }

    if((result[0]-'0')>9)
    {
        int temp=result[0]-'0';
        for(int i=larger;i>=1;i--)
            result[i] = result[i-1];
        result[1] = (temp-10)+'0';
        result[0] = '1';
        result[larger+1] = '\0';
    }
    else
        result[larger]='\0';

    free(larger_intal);
    free(smaller_intal);
    return result;
}

int intal_compare(const char* intal1, const char* intal2)
{
    if(strlen(intal1) > strlen(intal2))
        return 1;
    if(strlen(intal1) < strlen(intal2))
        return -1;

    int flag = 0;
    for(int i=0;i<strlen(intal1);i++)
    {
        int num1 = intal1[i]-'0';
        int num2 = intal2[i]-'0';

        if(num1 > num2)
        {
            flag = 1;
            break;
        }
        else if(num1 < num2)
        {
            flag = -1;
            break;
        }
    }
    
    return flag;
}

char* intal_diff(const char* intal1, const char* intal2)
{
    char *result = (char*)malloc(1001*sizeof(char));
    int larger;
    int smaller;
    char *larger_intal = (char*)malloc(1001*sizeof(char));
    char *smaller_intal = (char*)malloc(1001*sizeof(char));
    int flag = 0;
    if(0 == (intal1[0]-'0'))
    {
        strcpy(result,intal2);
        return result;
    }
    else if(0 == (intal2[0]-'0'))
    {
        strcpy(result,intal1);
        return result;
    }

    flag = intal_compare(intal1,intal2);

    if(flag == 1)
    {
        larger = strlen(intal1);
        smaller  = strlen(intal2);
        strcpy(larger_intal,intal1);
        strcpy(smaller_intal,intal2);
    }
    else if(flag == -1)
    {
        larger = strlen(intal2);
        smaller  = strlen(intal1);
        strcpy(larger_intal,intal2);
        strcpy(smaller_intal,intal1);
    }
    else
    {
        result[0] = '0';
        result[1] = '\0';
        free(larger_intal);
        free(smaller_intal);
        return result;
    }
    
    int borrow = 0;
    int diff = larger - smaller;
    for(int i=larger-1;i>=diff;i--)
    {
        int num1 = larger_intal[i]-'0';
        int num2 = smaller_intal[i-diff]-'0';
        int term = num1-num2-borrow;
        if(term < 0)
        {
            result[i] = (10+term)+'0';
            borrow = 1;
        }
        else
        {
            result[i] = term+'0';
            borrow = 0;
        }
    }
    
    for(int i=diff-1;i>=0;i--)
    {
        int num1 = larger_intal[i]-'0';
        int term = num1-borrow;
        if(term < 0)
        {
            result[i] = (10+term)+'0';
            borrow = 1;
        }
        else
        {
            result[i] = term+'0';
            borrow = 0;
        }
    }

    int pos = larger;
    while(0 == (result[0]-'0'))
    {
        --pos;
        for(int i=0;i<pos;i++)
            result[i] = result[i+1];
    }
    result[pos] = '\0';
    free(larger_intal);
    free(smaller_intal);
    return result;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    char *result = (char*)calloc(1001,sizeof(char));
    if(0 == (intal1[0]-'0'))
    {
        strcpy(result,"0");
        return result;
    }
    else if(0 == (intal2[0]-'0'))
    {
        strcpy(result,"0");
        return result;
    }
    int pos = 0;
    for(int i=strlen(intal2)-1;i>=0;i--)
    {
        int k;
        char *temp = (char*)calloc(1001,sizeof(char));
        temp[1000] = '\0';
        for(k=999;k>999-pos;k--)
        {
            temp[k] = '0';
        }
        int next = 0;
        for(int j=strlen(intal1)-1;j>=0;j--)
        {
            int prod = (intal1[j]-'0')*(intal2[i]-'0');
            int term = next+prod;
            if(term>9)
            {
                temp[k--] = (term%10)+'0';
                next = (term/10);
            }
            else
            {
                temp[k--] = term+'0';
                next = 0;
            }
        }
        if(next != 0)
            temp[k] = next+'0';
        else
            ++k;
        for(int i=0;k<1001;i++)
            temp[i] = temp[k++];
        
        strcpy(result,intal_add(result,temp));
        free(temp);
        ++pos;
    }

    return result;
}

char* intal_mod(const char* intal1, const char* intal2)
{
    char *result = (char*)malloc(1001*sizeof(char));
    if(intal_compare(intal1,intal2) == -1)
    {
        strcpy(result,intal1);
        return result;
    }
    int diff;
    strcpy(result,intal1);
    while(intal_compare(result,intal2) == 1 || intal_compare(result,intal2) == 0)
    {
        diff = strlen(result)-strlen(intal2);
        char *temp = (char*)malloc(1001*sizeof(char));
        strcpy(temp,intal2);
    
        for(int i=1;i<diff;i++)
        {
            strcpy(temp,intal_multiply(temp,"10"));
        }
        if(intal_compare(intal_multiply(temp,"10"),result) == -1)
            strcpy(temp,intal_multiply(temp,"10"));

        while(intal_compare(result,temp) != -1)
        {
            char *difference = intal_diff(result,temp);
            free(difference);
            strcpy(result,difference);
        }
        free(temp);
    }    

    return result;
}

char* intal_pow(const char* intal1, unsigned int n)
{
    char *result = (char*)malloc(1001*sizeof(char));
    char *temp1;
    char *temp2;
    if(n == 0)
    {
        strcpy(result,"1");
        return result;
    }
    if(0 == (intal1[0]-'0'))
    {
        strcpy(result,"0");
        return result;
    }
    
    char *temp = (char*)malloc(1001*sizeof(char));
    strcpy(result,"0");

    temp = intal_pow(intal1, n/2); 
    if (n%2 == 0)
    { 
        temp1 = intal_multiply(temp,temp);
        strcpy(result,temp1);
        free(temp1);
        free(temp);
        return result; 
    }
    else
    {
        temp1 = intal_multiply(temp,temp);
        temp2 = intal_multiply(intal1,temp1);
        strcpy(result,temp2);
        free(temp1);
        free(temp2);
        free(temp);
        return result;
    }
}

char* intal_gcd(const char* intal1, const char* intal2)
{
    char *result = (char*)malloc(1001*sizeof(char));
    if((strcmp(intal1,"0")==0) && (strcmp(intal2,"0")==0))
    {
        strcpy(result,"0");
        return result;
    }
    if(strcmp(intal1,"0")==0)
    {
        strcpy(result,intal2);
        return result;
    }
    if(strcmp(intal2,"0")==0)
    {
        strcpy(result,intal1);
        return result;
    }
    char *a = (char*)malloc(1001*sizeof(char));
    char *b = (char*)malloc(1001*sizeof(char));
    strcpy(a,intal1);
    strcpy(b,intal2);
    while(intal_compare(b,"0")!=0)
    {
        char *r = intal_mod(a,b);
        strcpy(a,b);
        strcpy(b,r);
        free(r);
    }
    strcpy(result,a);
    free(a);
    free(b);
    return result;
}

char* intal_fibonacci(unsigned int n)
{
    char *result = (char*)malloc(1001*sizeof(char));
    if(n == 0)
    {
        strcpy(result,"0");
        return result;
    }
    if(n == 1 | n == 2)
    {
        strcpy(result,"1");
        return result;
    }
    char *a = (char*)malloc(1001*sizeof(char));
    char *b = (char*)malloc(1001*sizeof(char));
    strcpy(a,"1");
    strcpy(b,"1");
    char *c = (char*)malloc(1001*sizeof(char));
    for(int i=2;i<n;i++)
    {
        c = intal_add(a,b);
        strcpy(a,b);
        strcpy(b,c);
    }

    strcpy(result,c);
    free(a);
    free(b);
    free(c);
    return result;
}

char* intal_factorial(unsigned int n)
{
    char *result = (char*)calloc(1001,sizeof(char));
    char *temp = (char*)calloc(1001,sizeof(char));
    char *multiply = (char*)calloc(1001,sizeof(char));
    strcpy(result,"1");
    for(int i = 2;i<=n;i++)
    {
        sprintf(temp, "%d", i);
        strcpy(multiply,intal_multiply(result,temp));
        strcpy(result,multiply);
    }

    free(temp);
    free(multiply);
    return result;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    char *result = (char*)malloc(1001*sizeof(char));
    char **temp = (char**)malloc((k+1)*sizeof(char*)); 
    for(int i=0;i<k+1;i++)
    {
        temp[i] = (char*)malloc(1001*sizeof(char));
        strcpy(temp[i],"0");
    }
    
    strcpy(temp[0],"1");
  
    for (int i = 1; i <= n; i++) 
    { 
        int min;
        if(i<k)
            min = i;
        else
            min = k;

        for (int j = min; j > 0; j--) 
        {
            char *sum = (char*)malloc(1001*sizeof(char));
            strcpy(sum,intal_add(temp[j],temp[j-1]));
            strcpy(temp[j],sum);
            free(sum); 
        }
    } 

    strcpy(result,temp[k]);
    for(int i=0;i<k+1;i++)
    {
        free(temp[i]);
    }
    free(temp);
    return result;
}

int intal_max(char **arr, int n)
{
    char *result = (char*)calloc(1001,sizeof(char));
    strcpy(result,arr[0]);
    int max = 0; 
    for(int i=1;i<n-1;i++)
    {
        int ans = intal_compare(arr[i],result);
        if(ans == 1)
        {
            strcpy(result,arr[i]);
            max = i;
        }
    }

    return max;
}

int intal_min(char **arr, int n)
{
    char *result = (char*)calloc(1001,sizeof(char));
    strcpy(result,arr[0]);
    int min = 0; 
    for(int i=1;i<n-1;i++)
    {
        int ans = intal_compare(arr[i],result);
        if(ans == -1)
        {
            strcpy(result,arr[i]);
            min = i;
        }
    }

    return min;
}

int intal_search(char **arr, int n, const char* key)
{
    for(int i=0;i<n;i++)
    {
        if(0 == intal_compare(arr[i],key))
            return i;
    }

    return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{ 
    int result = -1;
    result = binarySearch(arr,0,n-1,key);
    return result;
}

static int binarySearch(char **arr, int l, int r,const char* key)
{
    if (r >= l) 
    { 
        int mid = l + (r - l) / 2; 
  
        if (intal_compare(arr[mid],key) == 0) 
        {
            while(intal_compare(arr[mid],key) == 0 && mid >= 0)
            {
                mid-=1;
            }
            return mid+1;
        } 
  
        if (intal_compare(arr[mid],key) == 1) 
            return binarySearch(arr, l, mid - 1, key); 
   
        return binarySearch(arr, mid + 1, r, key); 
    }

    return -1;
}

void intal_sort(char **arr, int n)
{
    mergeSort(arr,0,n-1);
}

static void merge(char **arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    char **L = (char**)malloc(n1 * sizeof(char*));
    char **R = (char**)malloc(n2 * sizeof(char*));
    for(int r = 0; r < n1; r++) 
    {
		L[r] = (char*)malloc(1001 * sizeof(char));
        strcpy(L[r],arr[l + r]);
	}
    for(int r = 0; r < n2; r++) 
    {
		R[r] = (char*)malloc(1001 * sizeof(char));
        strcpy(R[r],arr[m + 1 + r]);
	}
    
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (intal_compare(L[i],R[j]) == -1 || intal_compare(L[i],R[j]) == 0) 
        { 
            strcpy(arr[k],L[i]); 
            i++; 
        } 
        else
        { 
            strcpy(arr[k],R[j]); 
            j++; 
        } 
        k++; 
    } 

    while (i < n1) 
    { 
        strcpy(arr[k],L[i]); 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        strcpy(arr[k],R[j]); 
        j++; 
        k++; 
    }

    for(int r=0;r<n1;r++)
    {
        free(L[r]);
    }
    for(int r=0;r<n2;r++)
    {
        free(R[r]);
    }
    free(L);
    free(R); 
} 
  
static void mergeSort(char **arr,int l,int r) 
{ 
    if (l < r)
    { 
        int m = l+(r-l)/2; 
  
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
}

char* coin_row_problem(char **arr, int n)
{
    char *result = (char*)malloc(sizeof(char));
    char *a = (char*)malloc(sizeof(char));
    char *b = (char*)malloc(sizeof(char));

    strcpy(a,"0");
    strcpy(b,arr[0]);

    for(int i=1;i<n;i++)
    {
        strcpy(result,arr[i]);
        int compare = intal_compare(intal_add(result,a),b);
        if(compare == 1)
        {
            strcpy(result,intal_add(result,a));
        }
        else if(compare == -1)
        {
            strcpy(result,b);
        }
        
        strcpy(a,b);
        strcpy(b,result);
    }

    return result;
}