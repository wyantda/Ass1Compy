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

int main(/*int argc, char *argv[]*/) {

    int argc = 50;
    char *argv = "C:\\Users\\DAW\\CLionProjects\\Ass1\\Shakespere.txt";
    char *ofp = "C:\\Users\\DAW\\CLionProjects\\Ass1\\output-50.txt";
    FILE *fp;
    FILE *op;
    clock_t begin_time, end_time;
    double time_used;

    if (argc < 3) {
        fprintf(stderr,"Not enough arguments\n");
        exit(1);
    }

    if (!(fp = fopen(argv,"r"))) {
        fprintf(stderr,"Cannot open file %s\n",argv);
        exit(1);
    }

    if (!(op = fopen(ofp,"w"))) {
        fprintf(stderr,"Cannot open file %s\n",argv[2]);
        exit(1);
    }

    begin_time = clock();
    formatter( fp, op, argc);
    end_time = clock();
    time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
    fprintf( stderr, "Time usage = %17.13f\n", time_used );
    return 0;
}

void formatter(FILE *ifp, FILE *ofp, int w) {
    int width = w - 1;
    char *text = readFile(ifp);
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

        if((wLen + lLen) > width && lLen != 0){
            do{
                int x;
                for (x = 0; x < lLen; ++x) {
                    if(line[x] == ' '){
                        int z;
                        for (z = lLen - 1; z > x - 1; --z) {
                            line[z + 1] = line[z];
                        }
                        lLen++;
                        x++;
                        if(lLen >= width){
                            break;
                        }
                    }
                }
            }while(lLen < width);
            line[lLen] = '\n';
            fputs(line, ofp);
            line = calloc((size_t) (width * 3), sizeof(char));
            lLen = 0;
        }
        if(lLen == 0 || (wLen + 1 + lLen) < width){
            if(lLen != 0){
                line[lLen++] = ' ';
            }
            int i;

            for (i = 0; i < wLen; ++i) {
                line[lLen++] = word[i];
            }
        }
        memset(word, 0, sizeof(word));
        pos++;
    }

    fputs(line, ofp);

}



char *readFile(FILE *in) {

    char *text;
    fseek(in, 0, SEEK_END);
    //fprintf(stderr,"God Why\n");
    int len = ftell(in) + 1;
    rewind(in);
    text = malloc(len * 2 * (sizeof(char)));
    //fprintf(stderr,"HOW ABOUT HERE\n");
    fread(text, sizeof(char), (size_t) len, in);
    text[len] = '\0';

    return text;

}