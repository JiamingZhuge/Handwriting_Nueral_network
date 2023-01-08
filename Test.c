#include"Nwork.h"
main(){
	//测试 
	read_weight();
	printf("start test\n");
	account=0;
	if((fp=fopen(FP_TEST,"r"))==NULL){
	 	printf("cannot test");
	 	exit(0);
	 }
	c=fgetc(fp);
	u=right=wrong=0;
	printf("please wait");
	while(c!=EOF){
		object=(int)(0-'0'+c);
		c=fgetc(fp); 
		i=0;
		while(c!='\n'){//行提取 
			temp=0;
			c=fgetc(fp);
			while(c!=','&&c!='\n'){//数字提取 
				temp=temp*10+(int)(0-'0'+c);
				c=fgetc(fp);
			}
			in.ob[i]=range((double)temp);
			i++;
		} 
		//(运行)
		if(LAY==1){
			weight_cul(HIDDEN,IN,in.weight,in.ob,hidout.ob);
			weight_cul(OUT,HIDDEN,hidout.weight,hidout.ob,out.ob);
		}
		else if(LAY>=2){
			weight_cul(HIDDEN,IN,in.weight,in.ob,hidden[0].ob);
			for(i=0;i<LAY-2;i++)weight_cul(HIDDEN,HIDDEN,hidden[i].weight,hidden[i].ob,hidden[i+1].ob);
			weight_cul(HIDDEN,HIDDEN,hidden[LAY-2].weight,hidden[LAY-2].ob,hidout.ob);
			weight_cul(OUT,HIDDEN,hidout.weight,hidout.ob,out.ob);
		}
		// 
		object_cul=result(out.ob);
		if(object_cul==object)right++;
		else wrong++;
		c=fgetc(fp);
		account++;
		if(account==SPEED){
			printf("/");
			account=0;
		}
	}
	printf("\n");
	rate=100*(right+0.00)/(right+wrong);
	printf("accomplish test 识别正确率为%0.4f%%\n\n",rate);
	fclose(fp);
	getch(); 
}
