/*
*Richard Coffey
*Bill Reid
*ECE-222
*Program 4
*
*Purpose: Performs convolution operations on two .txt files
*
*Bugs: None
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void num_line(char *filename, int *linecount) {
    
    FILE *fpt;
    int count;
    size_t len;
    char *line = NULL;
    ssize_t bytesread;

    //gets # of lines for points 
    if ((fpt = fopen(filename, "r")) == NULL) {
        printf("Cannot Read from File \"%s\"\n", filename);
        exit (1);
    }

    count = 0;
    while ((bytesread = getline(&line, &len, fpt)) != -1) {
        count++;
    }

    *linecount = count;

    fclose(fpt);

}

int read_min(char *filename, int *linecount) {

    FILE *fpt;
    int min;
    float fl;
    
    //reads in min index with a single fscanf
    if ((fpt = fopen(filename, "r")) == NULL) {
        printf("Cannot Read from File \"%s\"\n", filename);
        exit (1);
    }

    fscanf(fpt,"%d %f",&min, &fl);

    fclose(fpt);

    return min;
}

int read_max(char *filename, int *linecount) {

    FILE *fpt;
    int count;
    int max;
    float fl;

    count = *linecount;
    //scans in max index by reading all lines until the last and breaking
    if ((fpt = fopen(filename, "r")) == NULL) {
        printf("Cannot Read from File \"%s\"\n", filename);
        exit (1);
    }

    count = 0;
    while (fscanf(fpt,"%d %f",&max, &fl)) {
        if (count == *linecount) {
            break;
        }
        count++;
    }

    fclose(fpt);

    return max;
}

float *read_file(char *filename, int *linecount) {

    FILE *fpt;
    int count;
    float *ptrtoData;
    float fl;
    int in;

    count = *linecount;

    //malloc memory for pvalue
    ptrtoData = (float *)malloc (count * sizeof(float));

 
    if ((fpt = fopen(filename, "r")) == NULL) {
        printf("Cannot Read from File \"%s\"\n", filename);
        exit (1);
    }

    count = 0;
    //scans in data for ptr
    while (fscanf(fpt,"%d %f",&in, &fl)) { 
            
        ptrtoData[count] = fl;
        count++;
        if (count >= *linecount) {
            break;
        }
    }
    fclose(fpt);

    return ptrtoData;
} 


int main(int argc, char *argv[]) {

  //  int indexarray[];
    char *filename1;
    char *filename2;
    int fn_len1;
    int fn_len2; 
   // char *file1;
   // char *file2;
    int linecount1;
    int linecount2;
    int mIndex = 0; 
    int nIndex = 0;
    int i;
    int outputcount;
    float tempVal;

    //preparing files
    fn_len1 = strlen(argv[1]);
    fn_len2 = strlen(argv[2]);

    filename1 = (char *) malloc((fn_len1 + 1) * sizeof(char)); 
    filename2 = (char *) malloc((fn_len2 + 1) * sizeof(char));

    strcpy(filename1, argv[1]);
    strcpy(filename2, argv[2]);

    struct TData {
        int MinIndex, MaxIndex, Points;
        float *pValue;
    } Input[2], Output;

    //calcs lines for Min/Max index, points
    num_line(filename1, &linecount1);
    num_line(filename2, &linecount2);

    Input[0].Points = linecount1;
    Input[1].Points = linecount2;

    Input[0].MinIndex = read_min(filename1, &linecount1);
    Input[1].MinIndex = read_min(filename2, &linecount2);

    Input[0].MaxIndex = read_max(filename1, &linecount1);
    Input[1].MaxIndex = read_max(filename2, &linecount2);
    
    Input[0].pValue = read_file(filename1, &linecount1);
    Input[1].pValue = read_file(filename2, &linecount2);

    //At this point, all values are read into the struct

    //shifting pValue over by MinIndex to maintain index labels
    Input[0].pValue -= Input[0].MinIndex;
    Input[1].pValue -= Input[1].MinIndex;

    //malloc Output Min/Max/Points
    //not completely necessary but good to check for the output file
    Output.MinIndex = Input[0].MinIndex + Input[1].MinIndex;
    Output.MaxIndex = Input[0].MaxIndex + Input[1].MaxIndex;

    //malloc Output array
    for (i = Output.MinIndex; i <= Output.MaxIndex; i++) {
        outputcount++;
    }
    
    Output.pValue = (float *)malloc ((outputcount+1) * sizeof(float));
   
    //zeroing Output 
    Output.pValue -= Output.MinIndex;
    for (i = Output.MinIndex; i <= Output.MaxIndex; i++) {
        Output.pValue[i] = 0;
    }


    //convolution
    //convolve across index range (MinX+MinH) to (MaxX+MaxH)
    //mIndex = m in the convolution
    //M controls the range across which the two values will by convolved
    //nIndex = n in the convolution
    //N controls the tranlation constant for the X file (remember X must also be reflected)
    //
    
    for (nIndex = Output.MinIndex; nIndex <= Output.MaxIndex; nIndex++) {
        for (mIndex = Output.MinIndex; mIndex <=Output.MaxIndex; mIndex++) {
            if (((nIndex - mIndex) < Output.MinIndex) || ((nIndex - mIndex) >= Output.MaxIndex)) { 
            // if ((mIndex < Input[0].MinIndex || mIndex < Input[0].MaxIndex || mIndex < Input[1].MinIndex || mIndex > Input[1].MaxIndex) {
                tempVal += 0;
            }
            else {
                tempVal += (Input[0].pValue[nIndex - mIndex] * Input[1].pValue[mIndex]);
            }
        }
        Output.pValue[nIndex] = tempVal;
        tempVal = 0;
    }

    //writing to file
    FILE *out;
    if ((out = fopen("Output.txt", "w")) == NULL) {
        printf("Cannot Write File\n");
        exit (1);
    }
    
    for (i = Output.MinIndex; i <= Output.MaxIndex; i++) {
       fprintf(out,"%d\t%f\n", i, Output.pValue[i]);
    }

    fclose(out);

    //free
    free(Input[0].pValue + Input[0].MinIndex);
    free(Input[1].pValue + Input[1].MinIndex);
    free(filename1);
    free(filename2);
    free(Output.pValue + Output.MinIndex);

return 0;

}

