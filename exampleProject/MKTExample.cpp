#include "../singleInclude/MKTFileManager.h"

int main()
{
    char a = 'M';
    char b = 'A';
    char c = 'K';
    char d = 'i';
    char e = 'T';
    char f = 69;
    char justForFun = 152;
    bool trueBool = true;
    bool falseBool = false;
    char hexValue = 8;
    char hexValuesecond = 10;
    int firstInt = 2000;
    int secondInt = 10931472;

    MKT::Writing MKTW;
    MKT::Reading MKTR;
    MKTRawDataComputed myRawData;
    int errorCode = 0;
    char file[] = "./subscribe.MKT";

    MKTW.writeValue(&a,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&b,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&c,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&d,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&e,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&f,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&justForFun,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&trueBool,file,errorCode,MKT_VALUETYPE_BOOL);
    MKTW.writeValue(&falseBool,file,errorCode,MKT_VALUETYPE_BOOL);
    MKTW.writeValue(&hexValue,file,errorCode,MKT_VALUETYPE_HEX);
    MKTW.writeValue(&hexValuesecond,file,errorCode,MKT_VALUETYPE_HEX);
    MKTW.writeValue(&firstInt,file,errorCode,MKT_VALUETYPE_INT|MKT_SMALLER_THAN65536);
    MKTW.writeValue(&secondInt,file,errorCode,MKT_VALUETYPE_INT);
    
    myRawData = MKTR.readFile(file,errorCode);
    char taken;
    taken = *(char*)MKTR.dissectValue(myRawData,1,errorCode);
    printf("\ndissected %c",taken);
    taken = *(char*)MKTR.dissectValue(myRawData,2,errorCode);
    printf("\ndissected %c",taken);
    taken = *(char*)MKTR.dissectValue(myRawData,3,errorCode);
    printf("\ndissected %c",taken);
    taken = *(char*)MKTR.dissectValue(myRawData,4,errorCode);
    printf("\ndissected %c",taken);
    taken = *(char*)MKTR.dissectValue(myRawData,5,errorCode);
    printf("\ndissected %c",taken);

    // taken = *(char*)MKTR.dissectValue(myRawData,2,errorCode);
    // printf("\nValue: %c",taken);
    /*
    B - Boolean
    C - Char
    */
    printf("\nerrorCode: %d\n",errorCode);
    return 0;
}