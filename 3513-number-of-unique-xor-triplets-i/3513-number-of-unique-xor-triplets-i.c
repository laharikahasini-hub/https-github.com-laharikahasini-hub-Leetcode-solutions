int uniqueXorTriplets(int* nums, int numsSize)
{
    int n=numsSize;
    if(n==1) return 1;
    if(n==2) return 2;
    int bitLength=0;
    int temp=n;
    while(temp>0)
    {
      bitLength++;
      temp>>=1;
    }
    return 1<<bitLength;
}
