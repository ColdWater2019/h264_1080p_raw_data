#include <stdio.h>
#define FILE_SIZE 12793953
void main() {

   FILE *in = fopen("1080p.h264","rb");
   FILE *out = fopen("1080p.out","wb+");
   char *in_buffer = (char*)malloc(FILE_SIZE);
   char head[4] = {0,0,0,1};
   fread(in_buffer,1,FILE_SIZE,in);
   char *tmp = in_buffer,*tmp_end = in_buffer;
   char *tmp_in = in_buffer;
   int size = 0;

   while(tmp = strstr(tmp_in,head)) {
       tmp_end = tmp + 4;
       while(1) {
           if(*tmp_end == 0 && *(tmp_end+1) == 0 && *(tmp_end+2) == 0 && *(tmp_end+3) == 1) {
               break;
           } else {
               tmp_end++;
           }
       }
       //tmp_end = strstr(tmp + 4,head);
       size = tmp_end - tmp;
       printf("frame size:%d\n",size);
       fwrite(&size,1,4,out);
       fwrite(tmp,1,size,out); 
       tmp_in = tmp_end;
   }
   fclose(out);
   fclose(in);
}
