
int isPrime(int n)
{
    if(n<2) return 0;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0) return 0;
    }
    return 1;    
}
int countPrimeSetBits(int left,int right)
{
    int count=0;
    for(int num=left;num<=right;num++)
    {
       int setBits=0;
       int n=num;
       while(n>0)
       {
         setBits+=(n&1);
         n>>=1;
       }
       if(isPrime(setBits))
        {    
                count++;
        }
    }    
    return count;
}
