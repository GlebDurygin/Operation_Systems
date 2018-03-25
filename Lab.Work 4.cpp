#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 6969
#define BUFSIZE 16
int sock1, sock2;
char buf[BUFSIZE];
struct sockaddr_in addr1,addr2;
bool sumB, sqrB, diffB, divB;
pthread_t sumT, divT, diffT, sqrT;

void* sum(void*)
{
  while(1)
  {
   float a,b,c;
   while(sumB);
    recvfrom(sock2, &a, sizeof(float), 0, NULL, NULL);
    recvfrom(sock2, &b, sizeof(float), 0, NULL, NULL);
    recvfrom(sock2, &c, sizeof(float), 0, NULL, NULL);
   float res = a+b+c;
   send(sock1, &res, sizeof(res), 0);
   sumB = true;
  }
}


void* sqr(void*)
{
      float a;
  while(1)
  { 
  while(sqrB);
   // printf("SQR READING\n");
     recvfrom(sock2, &a, sizeof(float), 0, NULL, NULL);
	 float res = a*a;
	 send(sock1, &res, sizeof(res), 0);
     sqrB=true;
  }
}


void* diff(void*)
{
  float a,b;
  while(1)
    {    
  while(diffB);
  //   printf("Reading differences\n");
   recvfrom(sock2, &a, sizeof(float), 0, NULL, NULL);
   recvfrom(sock2, &b, sizeof(float), 0, NULL, NULL);
 //    printf("Read %f",a);
//printf("Read %f",b);
  float res = a-b;
    //cout << "Writing differences to sock\n";
  // printf("Writing differences to sock\n");
   send(sock1, &res, sizeof(res), 0);
    diffB=true;
 }
}


void* divide(void*)
{
float a,b;
  while(1)
  {
  while(divB);
 recvfrom(sock2, &a, sizeof(float), 0, NULL, NULL);
  recvfrom(sock2, &b, sizeof(float), 0, NULL, NULL);
   float res = a/b;
  //cout << "DIV RES: " << res << endl;
 //printf("DIV res %f",res);
   send(sock1, &res, sizeof(res), 0);
    divB=true;
  }
}


int main()

{
  sumB=divB=diffB=sqrB=true;
  int sumId, sqrId, diffId, divId;
  sock2 = socket(AF_INET, SOCK_DGRAM, 0);
 addr2.sin_family = AF_INET;
 addr2.sin_port = htons(PORT);
addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
 
 bind(sock2, (struct sockaddr *)&addr2, sizeof(addr2));

  sock1 = socket(AF_INET, SOCK_DGRAM, 0); 
  
connect(sock1, (struct sockaddr *)&addr2, sizeof(addr2));  
pthread_create(&sumT, NULL, sum, &sumId);
  
pthread_create(&diffT, NULL, diff, &diffId);
 
 pthread_create(&divT, NULL, divide, &divId);
 
 pthread_create(&sqrT, NULL, sqr, &sqrId);
 
 float num1, num2, num3;
  
printf("INPUT 3 NUMBERS\n");
  //cin >> num1 >> num2 >> num3;
printf("1 numb:\n");
scanf("%f",&num1);
printf("2 numb:\n");
scanf("%f",&num2);
printf("3 numb:\n");
scanf("%f",&num3);
 printf("NUMBER1 %f",num1);
printf("\nNUMBER2 %f",num2);
printf("\nNUMBER3 %f",num3);
 float diff1, diff2, diff3;
  float med;
//printf("FINDING MEDIUM:");
  send(sock1, &num1, sizeof(float), 0);
 send(sock1, &num2, sizeof(float), 0);
 send(sock1, &num3, sizeof(float), 0);
sumB=false; 
while(!sumB);
recvfrom(sock2, &med, sizeof(float), 0, NULL, NULL);
  float three = 3;
  send(sock1, &med, sizeof(float), 0);
  send(sock1, &three, sizeof(float), 0);
  divB=false;
 while(!divB);
  recvfrom(sock2, &med, sizeof(float),0, NULL, NULL);
printf("\nMedium %f",med);
//  printf("Writing differences 1-med\n");  
  send(sock1, &num1, sizeof(float), 0);
  send(sock1, &med, sizeof(float), 0);
  diffB=false;
 while(!diffB);
  recvfrom(sock2, &diff1, sizeof(float),0, NULL, NULL);
//printf("Writing differences 3-med\n");
  send(sock1, &med, sizeof(float), 0);
  send(sock1, &num3, sizeof(float), 0);
  diffB=false;
  while(!diffB);
  recvfrom(sock2, &diff2, sizeof(float),0, NULL, NULL);
  //printf("Writing differences 2-med\n");
  send(sock1, &med, sizeof(float), 0);
  send(sock1, &num2, sizeof(float), 0);
  diffB=false;
 while(!diffB);
 recvfrom(sock2, &diff3, sizeof(float),0, NULL, NULL);
 //printf("FINDING SQUARES: \n");
 send(sock1, &diff1, sizeof(float), 0);
  sqrB=false; while(!sqrB);
 recvfrom(sock2, &diff1, sizeof(float),0, NULL, NULL);
  send(sock1, &diff2, sizeof(float), 0);
  sqrB=false; 
while(!sqrB);
 recvfrom(sock2, &diff2, sizeof(float),0, NULL, NULL);
  send(sock1, &diff3, sizeof(float), 0);
sqrB=false; 
while (!sqrB);
  recvfrom(sock2, &diff3, sizeof(float),0, NULL, NULL);
  float sum;
 //printf("FINDING SUM: \n");
  send(sock1, &diff1, sizeof(float), 0);
 send(sock1, &diff2, sizeof(float), 0);
 send(sock1, &diff3, sizeof(float), 0);
 sumB=false; 
 while (!sumB);
  recvfrom(sock2, &sum, sizeof(float),0, NULL, NULL);
 //printf("Sum %f",sum);
 send(sock1, &sum, sizeof(float), 0);
float two = 2; 
 send(sock1, &two, sizeof(float), 0);
  divB=false; 
while(!divB);
  recvfrom(sock2, &sum, sizeof(float),0, NULL, NULL);
   printf("\nResult %f",sum);
printf("\n");
}
