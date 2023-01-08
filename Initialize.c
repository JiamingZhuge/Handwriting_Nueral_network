#include"Nwork.h"
main(){
	//≥ı ºªØ 
	if((f=fopen(WEIGHT_STORAGE,"w"))==NULL){
	 	printf("cannot write weight document");
	 	exit(0);
	}
	printf("initialization...\n");
	srand((unsigned)time(NULL));
	for(i=0;i<HIDDEN*IN;i++){
		fprintf(f,"%lf",rand_weight());
		fprintf(f,"%c",ch);
	}
	fprintf(f,"\n");
	for(u=0;u<LAY-1;u++){
		for(i=0;i<HIDDEN*HIDDEN;i++){
			fprintf(f,"%lf",rand_weight());
			fprintf(f,"%c",ch);
		}
		fprintf(f,"\n");
	}
	for(i=0;i<OUT*HIDDEN;i++){
		fprintf(f,"%lf",rand_weight());
		fprintf(f,"%c",ch);
	}
	fprintf(f,"\n");
	fclose(f);
	printf("accomplish initialization\n\n");
} 
