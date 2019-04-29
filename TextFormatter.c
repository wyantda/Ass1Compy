#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

char *readFile(FILE *);
void formatter(FILE *, FILE *, int);
/*
//main(int argc, char *argv[])
//{

	////FILE *ifp, *ofp;
	
	
	////clock_t begin_time, end_time;
	////double time_used;

	////if (argc < 3) {
	////  fprintf(stderr,"Not enough arguments\n");
	////  exit(1);
	////}
	////if (!(ifp = fopen(argv[1],"r"))) {
	////  fprintf(stderr,"Cannot open file %s\n",argv[1]);
	////  exit(1);
	////}
	
	/if (!(ofp = fopen(argv[2],"w"))) {
	/  exit(1);
	/}
	/  fprintf(stderr,"Cannot open file %s\n",argv[2]);

	////begin_time = clock();
	/formatter( ifp, ofp, atoi(argv[3]));
	////end_time = clock();
	////time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
	////fprintf( stderr, "Time usage = %17.13f\n", time_used );
  	fclose(ifp);
  	fclose(ofp);
        */
//}
int main(int argc, char *argv[]) {

	fprintf(stderr, "%d\n", argc);
   FILE *fp;
   FILE *op;
   char buff[255];
   char * sp; //string pointer
   clock_t begin_time, end_time;
   double time_used;

   if (argc < 3) {
   	fprintf(stderr,"Not enough arguments\n");
   	exit(1);
   }
   if (!(fp = fopen(argv[1],"r"))) {
   	fprintf(stderr,"Cannot open file %s\n",argv[1]);
   	exit(1);
   }
   if (!(op = fopen(argv[2],"w"))) {   
        fprintf(stderr,"Cannot open file %s\n",argv[2]);
	exit(1);
   }

   int lw = atoi(argv[2]);       
   begin_time = clock();         
   //     //           YOUR CODE HERE .....
   fprintf(stderr,"ERROR: LIU IS BAD\n");
   formatter( fp, op, lw);
   //     //            
   end_time = clock();
   time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
   fprintf( stderr, "Time usage = %17.13f\n", time_used );
   return 0;
}
void formatter(FILE *ifp, FILE *ofp, int w) {
    int width = w - 1;
    fprintf(stderr, "WTF\n");
    char *text = readFile(ifp);
    fprintf(stderr, "IM SERIOUS\n");
    size_t len;
    len = strlen(text);
    char *word = calloc(50, sizeof(char));
    char *line = calloc((size_t) (width * 3), sizeof(char));
    int pos = 0;
    int lLen = 0;
    while (pos < len) {
        int wLen = 0;
        while(!isspace(text[pos]) && pos < len){
            word[wLen++] = text[pos++];
        }
	fprintf(stderr, "WOWIE ZOW\n");
        if((wLen + lLen) > width && lLen != 0){
            do{
		fprintf(stderr,"NOLANNN\n");
		int x;
                for (x = 0; x < lLen; ++x) {
                    if(line[x] == ' '){
			int z;
                        for (z = lLen - 1; z > x - 1; --z) {
                            line[z + 1] = line[z];
                        }
			fprintf(stderr,"%d %d\n", lLen, x);
			fprintf(stderr, "NOOOOO\n");
                        lLen++;
                        x++;
                        if(lLen >= width){
			    fprintf(stderr,"NOOOOWW\n");
                            break;
                        }
                    }
                }
            }while(lLen < width);	
            fprintf(stderr,"NOOWWEEWW\n");
            line[lLen] = '\n';
            fprintf(stderr,"JUST CHECKING\n");
            //fputs(line, ofp);
	    fprintf(stderr,"E\n");
            line = calloc((size_t) (width * 3), sizeof(char));
            lLen = 0;
	    fprintf(stderr,"WHAT NOW\n");
        }
        if(lLen == 0 || (wLen + 1 + lLen) < width){
            if(lLen != 0){	
		fprintf(stderr, "%*c\n",line[lLen]);
                line[lLen++] = ' ';
            }
	    int i;
            for (i = 0; i < wLen; ++i) {
                line[lLen++] = word[i];
		fprintf(stderr, "%*c\n",line[i]);
            }
        }
        memset(word, 0, sizeof(word));
	pos++;
    }
    fprintf(stderr,"WE MADE IT BOIS\n");
    //fputs(line, ofp);
}

char *readFile(FILE *in) {
    char *text;
    fseek(in, 0, SEEK_END);
    fprintf(stderr,"God Why\n");
    int len = ftell(in) + 1;
    rewind(in);
    text = malloc(len * 2 * (sizeof(char)));
	fprintf(stderr,"HOW ABOUT HERE\n");
    fread(text, sizeof(char), (size_t) len, in);
    text[len] = '\0';
    return text;
}
