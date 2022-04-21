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
    unsigned int firstInt = 16639;// 16639 - 16640
    unsigned int secondInt = 10931472;

    MKT::Writing MKTW;
    MKT::Reading MKTR;
    MKTRawDataComputed myRawData;

    char file[] = "./subscribe.mkt";

    int errorCode = 0;
    
    // errorCode = MKT_SMART_WRITING_TO_FILE(69, 'C', "./subscribe.mkt");

    MKTW.writeValue(&a,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&b,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&c,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&d,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&e,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&justForFun,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&trueBool,file,errorCode,MKT_VALUETYPE_BOOL);
    MKTW.writeValue(&f,file,errorCode,MKT_VALUETYPE_CHAR);
    MKTW.writeValue(&falseBool,file,errorCode,MKT_VALUETYPE_BOOL);
    MKTW.writeValue(&hexValue,file,errorCode,MKT_VALUETYPE_HEX);
    MKTW.writeValue(&hexValuesecond,file,errorCode,MKT_VALUETYPE_HEX);
    MKTW.writeValue(&firstInt,file,errorCode,MKT_VALUETYPE_INT|MKT_SMALLER_THAN65536|MKT_UNSIGNED);
    MKTW.writeValue(&secondInt,file,errorCode,MKT_VALUETYPE_INT|MKT_UNSIGNED|MKT_UNSIGNED);
    
    myRawData = MKTR.readFile(file,errorCode);
    char taken;
    printf("\n\nCHAR:");
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,1,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %c",taken);
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,2,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %c",taken);
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,3,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %c",taken);
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,4,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %c",taken);
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,5,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %c",taken);
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,8,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %c",taken);
    printf("\n\nHEX:");
    char takenHex;
    takenHex = RETURN_MKT_HEX MKTR.dissectValue(myRawData,10,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected: %d",takenHex);
    takenHex = RETURN_MKT_HEX MKTR.dissectValue(myRawData,11,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected: %d",takenHex);
    printf("\n\nBOOL:");
    bool takenBool;
    takenBool = RETURN_MKT_BOOL MKTR.dissectValue(myRawData,7,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %d",takenBool);
    takenBool = RETURN_MKT_BOOL MKTR.dissectValue(myRawData,9,MKT_VALUETYPE_CHAR,errorCode);
    printf("\ndissected %d",takenBool);
    int intTaken;
    printf("\n\nINT:");
    intTaken = RETURN_MKT_INT MKTR.dissectValue(myRawData,12,MKT_VALUETYPE_INT|MKT_SMALLER_THAN65536,errorCode);
    printf("\ndissected %d",intTaken);
    intTaken = RETURN_MKT_INT MKTR.dissectValue(myRawData,13,MKT_VALUETYPE_INT,errorCode);
    printf("\ndissected %d",intTaken);

    free(myRawData.MKTRD);

    // taken = *(char*)MKTR.dissectValue(myRawData,2,errorCode);
    /*
    B - Boolean
    C - Char
    */
    printf("\nerrorCode: %d\n",errorCode);
    return 0;
}