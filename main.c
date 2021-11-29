#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

unsigned long long c1_x, c2_x, c1_y, c2_y;
unsigned long long G_x, G_y, Pa_x, Pa_y;
void encrypt(unsigned long long p)
{
    unsigned long long r = rand() % p;
	unsigned long long m;
	printf("\nEnter the message \n");
	scanf("%lld",&m);

	c1_x = r*G_x;
	c1_y = r*G_y;

	printf("\nEncrypted message : \n");
	printf("\tValue of C1: (%lld,%lld) \n",c1_x,c1_y);

	c2_x = m + r*Pa_x;
	c2_y = m + r*Pa_y;

	printf("\tValue of C2: (%lld,%lld) \n",c2_x,c2_y);
}

void decrypt(unsigned long long sk)
{
    unsigned long long c1_x_dec, c2_x_dec, c1_y_dec, c2_y_dec;
    printf("\nEnter the cipher text C1 (x,y) one below another\n");
	scanf("%lld",&c1_x_dec);
	scanf("%lld",&c1_y_dec);
	printf("\nEnter the cipher text C2 (x,y) one below another\n");
	scanf("%lld",&c2_x_dec);
	scanf("%lld",&c2_y_dec);
    unsigned long long decr = c2_x_dec-sk*c1_x_dec;
	printf("\nDecrypted message : %lld\n",decr);
}

int main()
{

    unsigned long long p;
	printf("Implementation of ElGamal Elliptic Curve Cryptography\n\n");
	printf("Elliptic Curve General Form \t y^2 mod p = (x^3  + A*x + B) mod p \n");
	printf("\nEnter the value of P: \n");
	scanf("%lld",&p);

    unsigned long long left[2][p],right[2][p];
    int i,j;
    unsigned long long a,b;
    printf("\nEnter the Value of a: \n");
    scanf("%lld",&a);
	printf("\nEnter the Value of b: \n");
	scanf("%lld",&b);
	printf("\nCurrent Elliptic Curve ---> y^2 mod %lld = (x^3  + %lld*x + %lld) mod p\n",p,a,b);


	for(i=0;i<p;i++)
	{
		left[0][i] = i;
		right[0][i] = i;
		left[1][i] = ((i*i*i) + a*i + b) % p;
		right[1][i] = (i*i) % p;
	}

	// Generating Base Points
    int in_c = 0;

	for(i=0;i<p;i++)
	{
		for(j=0;j<p;j++)
		{
			if(left[1][i] == right[1][j])
			{
                    in_c++;
			}
		}
	}
    unsigned long long message_x[in_c];
	unsigned long long message_y[in_c];

	int k=0;
	for(i=0;i<p;i++)
	{
		for(j=0;j<p;j++)
		{
			if(left[1][i] == right[1][j])
			{
                message_x[k] = left[0][i];
                message_y[k] = right[0][j];
                k++;
			}
		}
	}
    printf("\nOrder of the generator is %d\n",in_c);
	printf("\nGenerated Points are:\n");
	for(i =0; i < in_c; i++)
	{
        printf("%d. \t (%lld,%lld) \n",(i+1),message_x[i],message_y[i]);
	}

	G_x = message_x[0];
	G_y = message_y[0];
	printf("\nBase Point: (%lld,%lld) \n",G_x, G_y);

	srand (time(NULL));
	unsigned long long sk = rand() % p;
	printf("\nSecret key is %lld \n",sk);

    Pa_x=sk*G_x;
	Pa_y=sk*G_y;

	printf("\nPublic key is (%lld,%lld) \n",Pa_x,Pa_y);

    int choice;
    while(1){
    printf("\nEnter your choice:\t1.Encrypt\t2.Decrypt\t3.Exit\n");
    scanf("%d",&choice);
    switch(choice) {
      case 1: {
          encrypt(p);
          break;
        }
      case 2: {
        decrypt(sk);
        break;
      }
      case 3: {
          break;
        }
      default: {
          printf("\nInvalid choice,Enter valid choice.\n");
        }
    }
    if(choice==3)
      break;
    }
    getch();
    return 0;
}
