#include "../singleInclude/MKTFileManager.h"

int main()
{
    char a = 'M';
    char b = 'A';
    char c = 'K';
    char d = 'i';
    char e = 'T';
    MKT::Writing MKTW;
    MKT::Reading MKTR;
    MKTDataClusterComputed myDataClusterComputed;
    MKTRawDataComputed myRawData;
    MKTW.writeValue(&a,'C',"./subscribe.MKT");
    MKTW.writeValue(&b,'C',"./subscribe.MKT");
    MKTW.writeValue(&c,'C',"./subscribe.MKT");
    MKTW.writeValue(&d,'C',"./subscribe.MKT");
    MKTW.writeValue(&e,'C',"./subscribe.MKT");
    // myRawData = MKTR.readFile("./subscribe.MKT");
    // printf("\n%d",myRawData.sizeOfData);
    // MKTR.dissectValue(myRawData.MKTRD,myRawData.sizeOfData);
    /*
    B - Boolean
    C - Char
    */
    int x = 0;
    printf("%d",x);
    return 0;
}