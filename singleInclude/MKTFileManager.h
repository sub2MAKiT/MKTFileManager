#include <stdio.h>
#include <stdlib.h>

#ifdef MKT_DEBUG
#define MKT_DEBUGVALUE true
#else
#define MKT_DEBUGVALUE false
#endif


struct MKTData
{
    void * value;
    unsigned char type;
};

typedef unsigned char * MKTRawData;

struct MKTRawDataComputed {

    MKTRawData MKTRD;
    size_t sizeOfData;

};

typedef MKTData * MKTDataCluster;

struct MKTDataClusterComputed {
    MKTDataCluster MKTDC;
    size_t sizeOfCluster;
};

class MKT
{
public:
    class Writing
    {
        private:
        char createDescriptor(char type, char option);
        public:
        void writeValue(void * Value,char ValueType, char filePath[]);
    };
    class Reading
    {
        public:
        MKTRawDataComputed readFile(char filePath[]);
        MKTDataClusterComputed dissectValue(MKTRawData MKTRD,long value);
    };
};

MKTDataClusterComputed MKT::Reading::dissectValue(MKTRawData MKTRD,long value)
{

}

MKTRawDataComputed MKT::Reading::readFile(char filePath[])
{

}



void MKT::Writing::writeValue(void * Value, char ValueType, char filePath[])
{
    FILE *MKTDATA;
    char typeDescriptor;
    char optionDescriptor;

    if(ValueType == 'C')
    {
        optionDescriptor = 0;
        typeDescriptor = 2;
    }
    if(MKT_DEBUGVALUE)
        printf("startedWriting");


    char *descriptor;
    *descriptor = createDescriptor(typeDescriptor,optionDescriptor);

    if( fopen_s( &MKTDATA, filePath, "ab" ) == 0 )
    {
        // Write a descriptor
        fwrite( descriptor,1, 1, MKTDATA );

        // Write the value
        if(ValueType == 'C')
        {
            fwrite(Value,1,1,MKTDATA);
        }


        fclose( MKTDATA );
    }
    else
        if(MKT_DEBUGVALUE)
            printf( "File could not be opened\n" );
}

char MKT::Writing::createDescriptor(char type, char option)
{
    char finalDescriptor;
    char optionAND = option&15;
    unsigned char typeAND = type&15;
    typeAND = typeAND<<4;
    finalDescriptor = typeAND|optionAND;
    return finalDescriptor;
}