#include <stdio.h>
#include <stdlib.h>

#ifdef MKT_DEBUG
#define MKT_DEBUGVALUE true
#else
#define MKT_DEBUGVALUE false
#endif

// value type defines

#define MKT_VALUETYPE_ARRAY 128

// types
#define MKT_VALUETYPE_BOOL 0
#define MKT_VALUETYPE_HEX 16
#define MKT_VALUETYPE_CHAR 32
#define MKT_VALUETYPE_INT 48

// optimisation
#define MKT_SMALLER_THAN256 12
#define MKT_SMALLER_THAN65536 8
#define MKT_SMALLER_THAN16777216 4
#define MKT_SMALLER_THAN4294967296 0

#define MKT_UNSIGNED 2

// for data retrieval because I'm not a psychopath
#define RETURN_MKT_BOOL *(bool*)
#define RETURN_MKT_HEX *(char*)
#define RETURN_MKT_CHAR *(char*)
#define RETURN_MKT_INT *(int*)


long long MKT;

struct MKTData
{
    unsigned char type;
    char *value;
};

typedef char * MKTRawData;

struct MKTRawDataComputed {

    MKTRawData MKTRD;
    size_t sizeOfData;

};

class MKT
{
public:

    typedef char MKT_BOOL_TYPE;

    class ErrorChecking
    {
        public:
        int fileNotMKT(char filePath[],int &errorCode);
    };
    class Writing
    {
        private:
        public:
        void writeValue(void * Value, char filePath[],int &errorCode,char ValueType, size_t arraySize = NULL);
    };
    class Reading
    {
        private:
        long long ANDMKT(int a, int b, int c);
        void addValueToComputedMKT(char *MKTDC,long long tempValue, int sizeOfValue);
        void readDescriptor(char current, char &sizeOfValue,int &errorCode);
        public:
        MKTRawDataComputed readFile(char filePath[], int &errorCode);
        void * dissectValue(MKTRawDataComputed MKTRDC,int valueToTake,char ValueType,int &errorCode);
    };
};

void * MKT::Reading::dissectValue(MKTRawDataComputed MKTRDC,int valueToTake,char ValueType,int &errorCode)
{
    if(MKTRDC.sizeOfData < 1)
        errorCode = 2;
    size_t finalSize = 0;
    long long finalValue = 0;
    bool isDescriptor = true;
    char sizeOfValue;
    for(int i = 0; i < MKTRDC.sizeOfData;i++)
    {
        readDescriptor(MKTRDC.MKTRD[i],sizeOfValue,errorCode);
        if(finalSize == valueToTake)
        {
            if((ValueType&112) == MKT_VALUETYPE_CHAR)
                return ((char*)MKTRDC.MKTRD + i);
            else if((ValueType&112) == MKT_VALUETYPE_INT)
            {
                if((ValueType&12) == MKT_SMALLER_THAN256)
                {
                    int finalReturnInt = *((char*)MKTRDC.MKTRD+i);
                    int *finalReturn = &finalReturnInt;
                    return finalReturn;
                } else if((ValueType&12) == MKT_SMALLER_THAN65536) {
                    int finalReturnInt = *((char*)MKTRDC.MKTRD+i) + *((char*)MKTRDC.MKTRD+i+1) * 256;
                    int *finalReturn = &finalReturnInt;
                    return finalReturn;
                } else if((ValueType&12) == MKT_SMALLER_THAN16777216) {
                    int finalReturnInt = *((char*)MKTRDC.MKTRD+i) + (*((char*)MKTRDC.MKTRD+i + 1) * 256) + (*((char*)MKTRDC.MKTRD+i + 2) * 256 * 256);
                    int *finalReturn = &finalReturnInt;
                    return finalReturn;
                } else if((ValueType&12) == MKT_SMALLER_THAN4294967296) {
                    int finalReturnInt = *((int*)MKTRDC.MKTRD+i);
                    int *finalReturn = &finalReturnInt;
                    return finalReturn;
                }
            }
        } else {
            if(sizeOfValue == 0 || sizeOfValue == 127)
            {
                if(finalSize + 1 == valueToTake)
                {
                    char finalReturnChar = (*((char*)MKTRDC.MKTRD+i))&15;
                    char *finalReturn = &finalReturnChar;
                    return finalReturn;
                }
            } else {
                if(finalSize + 1 != valueToTake)
                    i += sizeOfValue;
            }
        }
        finalSize++;
    }

}

MKTRawDataComputed MKT::Reading::readFile(char filePath[],int &errorCode)
{
    FILE *MKTFILE;
    MKTRawDataComputed MKTRDC;
    if( fopen_s( &MKTFILE, filePath, "rb" ) == 0 )
    {
        char *list;
        fseek(MKTFILE, 0L, SEEK_END);
        long sizeOfFile = ftell(MKTFILE);
        rewind(MKTFILE);
        list = (char*)malloc(sizeOfFile);
        if(list == NULL)
            errorCode = 8;
        MKTRDC.sizeOfData = fread( list,1, sizeOfFile, MKTFILE );
        fclose( MKTFILE );
        MKTRDC.MKTRD = list;
    }
    else
    {
        errorCode = 1;
        if(MKT_DEBUGVALUE)
            printf( "File could not be opened\n" );
    }
    return MKTRDC;
}

// fseek(fp, 0L, SEEK_END);
// sz = ftell(fp);

void MKT::Writing::writeValue(void * Value, char filePath[],int &errorCode,char ValueType, size_t arraySize = NULL)
{
    MKT::ErrorChecking MKTE;
    MKTE.fileNotMKT(filePath,errorCode);

    FILE *MKTDATA;

    if( fopen_s( &MKTDATA, filePath, "ab" ) == 0 )
    {
        if((ValueType&MKT_VALUETYPE_ARRAY) == MKT_VALUETYPE_ARRAY && arraySize == NULL)
        {
            errorCode = 5;
        }else if((ValueType&MKT_VALUETYPE_ARRAY) == MKT_VALUETYPE_ARRAY && (ValueType&112) == MKT_VALUETYPE_HEX) {
            errorCode = 7;
        } else {
            // Write a descriptor
            if((ValueType&MKT_VALUETYPE_ARRAY )== MKT_VALUETYPE_ARRAY)
            {
                for(int i = 0; i < arraySize;i++)
                {
                    if((ValueType&112) == MKT_VALUETYPE_BOOL)
                    {
                        for(int i = 0; i < arraySize; i++)
                        {
                            char tempBool = (*((bool*)Value+i)<<1) + (i != arraySize - 1);
                            fwrite(&tempBool,1,1,MKTDATA);
                        }
                    } else if((ValueType&122) == MKT_VALUETYPE_CHAR) {
                        for(int i = 0; i < arraySize; i++)
                        {
                            char tempdescriptor = ValueType|(i != arraySize - 1);
                            fwrite(&tempdescriptor,1,1,MKTDATA);
                            char tempValue = *((char*)Value+i);
                            fwrite(&tempValue,1,1,MKTDATA);
                        }
                    } else if((ValueType&122) == MKT_VALUETYPE_INT) {
                        for(int i = 0; i < arraySize; i++)
                        {
                            char tempdescriptor = ValueType|(i != arraySize - 1);
                            fwrite(&tempdescriptor,1,1,MKTDATA);
                            int tempValue = *((int*)Value+i);
                            fwrite(&tempValue,4,1,MKTDATA);
                        }
                    }
                }
            } else { 
                if((112&ValueType) == MKT_VALUETYPE_BOOL)
                {
                    char ValueBool = ValueType|*(bool*)Value;
                    fwrite( &ValueBool,1, 1, MKTDATA );
                } else if((112&ValueType) == MKT_VALUETYPE_HEX) {
                    if(*(char*)Value > 15)
                        errorCode = 6;
                    char ValueHex = ValueType|*(char*)Value;
                    fwrite( &ValueHex,1, 1, MKTDATA );
                } else {
                    fwrite( &ValueType,1, 1, MKTDATA );
                    char howManyBytes;
                    if((ValueType&112) == MKT_VALUETYPE_CHAR)
                    {
                        howManyBytes = 1;
                    }
                    else if((ValueType&112) == MKT_VALUETYPE_INT)
                    {
                        if((ValueType&12) == MKT_SMALLER_THAN16777216)
                            howManyBytes = 4;
                        else if((ValueType&12) == MKT_SMALLER_THAN4294967296)
                            howManyBytes = 3;
                        else if((ValueType&12) == MKT_SMALLER_THAN65536)
                            howManyBytes = 2;
                        else if((ValueType&12) == MKT_SMALLER_THAN256)
                            howManyBytes = 1;
                    }
                    fwrite(Value,howManyBytes,1,MKTDATA);
                }
            }
        }
        fclose( MKTDATA );
    }
    else
    {
        if(MKT_DEBUGVALUE)
            printf( "File could not be opened\n" );
        errorCode = 1;
    }
}

int MKT::ErrorChecking::fileNotMKT(char filePath[],int &errorCode)
{
    int errorcode = errorCode;
    int sizeOfPath = sizeof(filePath) * 2;
    if(filePath[sizeOfPath-2] == 'T' || filePath[sizeOfPath-2] == 't')
    {
        if(filePath[sizeOfPath-3] == 'K' || filePath[sizeOfPath-3] == 'k')
        {
            if(filePath[sizeOfPath-4] == 'M' || filePath[sizeOfPath-4] == 'm')
            {
                if(filePath[sizeOfPath-5] == '.')
                {
                    return errorcode;
                } else {
                    errorCode = 3;
                }
            } else {
                errorCode = 3;
            }
        } else {
            errorCode = 3;
        }
    } else {
        errorCode = 3;
    }


    return errorcode;
}

void MKT::Reading::readDescriptor(char current, char &sizeOfValue,int &errorCode)
{
    if((current&240)>>4 == 0)
        sizeOfValue = 127;
    else if ((current&240)>>4 == 1)
        sizeOfValue = 0;
    else if ((current&240)>>4 == 2)
        sizeOfValue = 1;
    else if ((current&240)>>4 == 3)
    {
        if((current&12)>>2 == 0)
            sizeOfValue = 4;
        else if((current&12)>>2 == 1)
            sizeOfValue = 3;
        else if((current&12)>>2 == 2)
            sizeOfValue = 2;
        else if((current&12)>>2 == 3)
            sizeOfValue = 1;
    }
    else
        errorCode = 4;
    if(MKT_DEBUGVALUE)
        printf("\nValue type: %d, %d", sizeOfValue, (current&240)>>4);
}

void MKT::Reading::addValueToComputedMKT(char *MKTDC,long long tempValue, int sizeOfValue)
{
    if(sizeOfValue == 0)
    {
        MKTDC[0] = (tempValue&15);
    } else if(sizeOfValue == 1) {
        MKTDC[0] = tempValue;
    } else if(sizeOfValue == 4) {
        for(int i = 0; i < 4; i++)
        {
            MKTDC[i] = ANDMKT(i+8,i,tempValue);
        }
    }
}
long long MKT::Reading::ANDMKT(int a, int b, int c)
{
    long long returnValue;
    int powerOfTwoA = 1;
    int powerOfTwoB = 1;
    int finalPower = 0;
    for(int B = 0; B < b; B++)
    {
        powerOfTwoB *= 2;
    }
    for(int A = 0; A < a; A++)
    {
        powerOfTwoA *= 2;
        if(powerOfTwoB - A < 1)
            finalPower += powerOfTwoA;
    }
    returnValue = (c&finalPower)>>b;
    return returnValue;
}

// For easier use
int MKT_SMART_WRITING_TO_FILE(long long value, char valueType, char filename[])
{
    int errorCode;
    MKT::Writing MKTW;
    if(valueType == 'I')
    {
        int IntValue = value;
        MKTW.writeValue(&IntValue,filename,errorCode,MKT_VALUETYPE_INT);
    } else if(valueType == 'C') {
        char CharValue = value;
        MKTW.writeValue(&CharValue,filename,errorCode,MKT_VALUETYPE_CHAR);
    } else if(valueType == 'B') {
        bool BoolValue = value;
        MKTW.writeValue(&BoolValue,filename,errorCode,MKT_VALUETYPE_BOOL);
    }
    return errorCode;
}

int MKT_SMART_READING_FROM_FILE(void * value,int number, char valueType,char flags, char filename[])
{
    int errorCode;
    MKT::Reading MKTR;
    MKTRawDataComputed myRawData;
    myRawData = MKTR.readFile(filename,errorCode);
    if(valueType == 'I')
    {
        *(int*)value = RETURN_MKT_INT MKTR.dissectValue(myRawData,number,flags,errorCode);
    } else if(valueType == 'C') {
        *(char*)value = RETURN_MKT_INT MKTR.dissectValue(myRawData,number,flags,errorCode);
    } else if(valueType == 'B') {
        *(bool*)value = RETURN_MKT_INT MKTR.dissectValue(myRawData,number,flags,errorCode);
    }
    
    free(myRawData.MKTRD);
    return errorCode;
}