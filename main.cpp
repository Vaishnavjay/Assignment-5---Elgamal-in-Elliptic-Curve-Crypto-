#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include "bignum.h"
#include <time.h>

using namespace std;

BigNum Pa_x, Pa_y, c1_x, c1_y, c2_x, c2_y, G_x, G_y;
void encrypt(BigNum p)
{
    BigNum r;
	BigNum One;
	One.Num[0] = 1;
	r = PwrMod(StringToArray(to_string(rand())),One,p);
	string m_str;
	BigNum m;
	cout<<"\nEnter the message \n";
	cin>>m_str;
	m = StringToArray(m_str);

	c1_x = Mul(r,G_x);
	c1_y = Mul(r,G_y);

	string c1_x_str, c1_y_str, c2_x_str, c2_y_str;

	c1_x_str = value_number(c1_x);
	c1_y_str = value_number(c1_y);

	if(c1_x_str.compare("")==0)
		c1_x_str = "0";
	if(c1_y_str.compare("")==0)
		c1_y_str = "0";

	cout<<"\nEncrypted message : \n";
	cout<<"\tValue of C1: ("<<c1_x_str<<","<<c1_y_str<<") \n";

	c2_x = Add(m,Mul(r,Pa_x));
	c2_y = Add(m,Mul(r,Pa_y));

	c2_x_str = value_number(c2_x);
	c2_y_str = value_number(c2_y);

	if(c2_x_str.compare("")==0)
		c2_x_str = "0";
	if(c2_y_str.compare("")==0)
		c2_y_str = "0";

	cout<<"\tValue of C2: ("<<value_number(c2_x)<<","<<value_number(c2_y)<<") \n";
}

void decrypt(BigNum sk)
{
    BigNum c1_x_dec, c2_x_dec, c1_y_dec, c2_y_dec;
	string c1_x_dec_str, c2_x_dec_str, c1_y_dec_str, c2_y_dec_str;

    cout<<"\nEnter the cipher text C1 (x,y) one below another\n";
	cin>>c1_x_dec_str;
	cin>>c1_y_dec_str;
	cout<<"\nEnter the cipher text C2 (x,y) one below another\n";
	cin>>c2_x_dec_str;
	cin>>c2_y_dec_str;

	c1_x_dec = StringToArray(c1_x_dec_str);
	c1_y_dec = StringToArray(c1_y_dec_str);
	c2_x_dec = StringToArray(c2_x_dec_str);
	c1_y_dec = StringToArray(c2_y_dec_str);

	BigNum decr;
	decr = Sub(c2_x_dec,Mul(sk,c1_x_dec));

	cout<<"\nDecrypted message : "<<value_number(decr)<<"\n";
}

int main()
{
    string p_str,a_str,b_str;
	cout<<"Implementation of ElGamal Elliptic Curve Cryptography\n\n";
	cout<<"Elliptic Curve General Form \t y^2 mod p = (x^3  + A*x + B) mod p \n";
	cout<<"\nEnter the value of P: \n";
	cin>>p_str;

	BigNum p = StringToArray(p_str);
	BigNum a,b;

    BigNum i,j;
	i.Num[0] = 0;
	j.Num[0] = 0;
	BigNum One;
	One.Num[0] = 1;

	a_str = "-1";
	b_str = "188";

	a = StringToArray(a_str);
	b = StringToArray(b_str);

	cout<<"\nCurrent Elliptic Curve ---> y^2 mod"<<value_number(p)<<" = (x^3  + "<<value_number(a)<<"*x + "<<value_number(b)<<") mod"<<value_number(p)<<"\n";


	G_x.Num[0] = 0;
	G_y.Num[0] = 0;
	string add_str = "376";
	BigNum add_big;
	add_big = StringToArray(add_str);
	G_y = Add(G_y,add_big);

	string G_x_str, G_y_str;
	G_x_str = value_number(G_x);
	G_y_str = value_number(G_y);

	if(G_x_str.compare("")==0)
		G_x_str = "0";
	if(G_y_str.compare("")==0)
		G_y_str = "0";

	cout<<"\nBase Point: ("<<G_x_str<<","<<G_y_str<<")"<<"\n";

	srand (time(NULL));
	BigNum sk;
	sk = PwrMod(StringToArray(to_string(rand())),One,p);

	cout<<"\nSecret key is "<<value_number(sk)<<"\n";

    Pa_x=Mul(sk,G_x);
	Pa_y=Mul(sk,G_y);

	string Pa_x_str, Pa_y_str;

	Pa_x_str = value_number(Pa_x);
	Pa_y_str = value_number(Pa_y);

	if(Pa_x_str.compare("")==0)
		Pa_x_str = "0";
	if(Pa_y_str.compare("")==0)
		Pa_y_str = "0";
	cout<<"\nPublic key is ("<<Pa_x_str<<","<<Pa_y_str<<") \n";

    int choice;
    while(1){
    cout<<"\nEnter your choice:\t1.Encrypt\t2.Decrypt\t3.Exit\n";
    cin>>choice;
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
          cout<<("\nInvalid choice,Enter valid choice.\n");
        }
    }
    if(choice==3)
      break;
    }
    return 0;
}
