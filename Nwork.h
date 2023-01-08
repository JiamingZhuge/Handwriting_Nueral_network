#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
//训练数据集、测试数据集、权重保存 路径，务必修改 
#define FP_TRAIN "C:\\Users\\zhuge\\Desktop\\Nueral network\\Nueral Matrix\\train.csv"
#define FP_TEST "C:\\Users\\zhuge\\Desktop\\Nueral network\\Nueral Matrix\\test.csv"
#define WEIGHT_STORAGE "C:\\Users\\zhuge\\Desktop\\Nueral network\\Nueral Matrix\\LAY.txt"
//输入节点，视MNIST集而定 
#define IN 28*28
//输出节点，判断0~9数字 
#define OUT 10
//中间节点数 
#define HIDDEN 200 
//中间节点层 
#define LAY 1
//运行进度条速度控制 
#define SPEED 200 
//学习率设置 
#define Learning_rate 0.1
struct node_i{
	double ob[IN];
	double weight[HIDDEN][IN];
}in;
struct node_h{
	double ob[HIDDEN];
	double weight[HIDDEN][HIDDEN];
	double error[HIDDEN];
}hidden[LAY-1];
struct node_ho{
	double ob[HIDDEN];
	double weight[OUT][HIDDEN];
	double error[HIDDEN];
}hidout;
struct node_o{
	double ob[OUT];
	double error[OUT];
}out;
//每行对应每步要用到的参数 
int i,j,u;FILE*f;char ch='/';
char c;int account,temp,object;FILE*fp;
int right,wrong,object_cul;double rate;double in_change[HIDDEN][IN],hidden_change[HIDDEN-1][HIDDEN][HIDDEN],out_change[OUT][HIDDEN];
//函数 
double sigmoid(double x){
	return 1/(1+exp(-x));
}
double rand_weight(void){
	double r;
	r=rand()%199-99;
	r=r/100.00/sqrt(IN);
	if(r==0)r=0.01;
	return r;
}
double range(double in){
	return in/255*0.99+0.01;
}
void weight_cul(int out_hang,int in_lie,double weight[out_hang][in_lie],double in_T[],double out_T[]){//简单矩阵的乘法 含激活函数 
	double temp;int i,j;
	for(i=0;i<out_hang;i++){
		temp=0;
		for(j=0;j<in_lie;j++)temp+=weight[i][j]*in_T[j];
		out_T[i]=sigmoid(temp);
		//if(out_T[i]==0)out_T[i]=0.01;
		//if(out_T[i]==1)out_T[i]=0.99;
	}
}
int result(double ob[]){
	int i,max;
	max=0;
	for(i=1;i<OUT;i++){
		if(ob[i]>ob[max])max=i;
	}
	return max;
}
void error_cul(int hang,int lie,double weight[hang][lie],double in_T[],double out_T[]){//简单转置矩阵的乘法 无激活函数 
	double temp;int i,j;
	for(i=0;i<lie;i++){
		temp=0;
		for(j=0;j<hang;j++){
			temp+=weight[j][i]*in_T[j];
		}
		out_T[i]=temp;
	}
}
void read_weight(void){
	FILE*p;char b;
	if((p=fopen(WEIGHT_STORAGE,"r"))==NULL){
		printf("please check the document\n");
		exit(0);
	}
	for(i=0;i<HIDDEN;i++){
		for(j=0;j<IN;j++){
			fscanf(p,"%lf",&in.weight[i][j]);
			fscanf(p,"%c",&b);
		}
	}
	fscanf(p,"\n");
	for(u=0;u<LAY-1;u++){
		for(i=0;i<HIDDEN;i++){
			for(j=0;j<HIDDEN;j++){
				fscanf(p,"%lf",&hidden[u].weight[i][j]);
				fscanf(p,"%c",&b);
			}
		}
	}
	for(i=0;i<OUT;i++){
		for(j=0;j<HIDDEN;j++){
			fscanf(p,"%lf",&hidout.weight[i][j]);
			fscanf(p,"%c",&b);
		}
	}
	fclose(p);
} 
void write_weight(void){
	FILE*p;
	if((p=fopen(WEIGHT_STORAGE,"w"))==NULL){
	 	printf("cannot write weight document");
	 	exit(0);
	}
	for(i=0;i<HIDDEN;i++){
		for(j=0;j<IN;j++){
			fprintf(p,"%lf",in.weight[i][j]);
			fprintf(p,"%c",ch);
		} 
		fprintf(p,"\n");
	}
	for(u=0;u<LAY-1;u++){
		for(i=0;i<HIDDEN;i++){
			for(j=0;j<HIDDEN;j++){
				fprintf(p,"%lf",hidden[u].weight[i][j]);
				fprintf(p,"%c",ch);
			} 
		}
		fprintf(p,"\n");
	}
	for(i=0;i<OUT;i++){
		for(j=0;j<HIDDEN;j++){
			fprintf(p,"%lf",hidout.weight[i][j]);
			fprintf(p,"%c",ch);
		} 
	}
	fprintf(p,"\n");
	fclose(p);
}
