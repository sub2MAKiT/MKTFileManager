# MKTFileManager
A Read/Write single header cpp library used to manage MKT files.

## Usage:
There are two ways to use my code, first one is shorter and simpler, whilst the second one is faster and more complex.
### Writing:
#### Simple way:
```cpp
    MKT_SMART_WRITING_TO_FILE(69, 'C', "./subscribe.mkt");
```
> Yup, just one function, simple as it is. The first parameter is the value that you want to save, the second one is the data type,
> ```
> 'B' - Bool
> 'C' - Char / hex
> 'I' - Int
> ```
> and the third one is the path to the file. The function returns an error code so it is recommended to have a variable to check for errors.
#### Fast way:
```cpp
    MKT::Reading MKTR;
    char a = 69;
    char file[] = "./subscribe.mkt";
    int errorCode = 0;

    MKTW.writeValue(&a,file,errorCode,MKT_VALUETYPE_CHAR);
```
> Now this is a little bit more complicated. The first parameter is an adress of a variable, which basically means just giving it a variable with an **&** before it.
> 
> Second parameter is a path, you can use the
> ```"./subscribe.mkt"```, but it is recommended to make a char array like you can see in the example.
> 
> Third one is an errorCode.
>
> Fourth parameter is a MKT valueType for descriptor, which might sound scary, but it just means you need to give the function the correct flag. You can concat main flags with optimization by using **|**, like so ```MKT_VALUETYPE_INT|MKT_SMALLER_THAN65536|MKT_UNSIGNED```
### Reading:
#### Simple way:
```cpp
MKT_SMART_READING_FROM_FILE(&value,6, 'C',MKT_VALUETYPE_CHAR,"./subscribe.mkt");
```
> once again, just a simple function that is returning an error code.
> First parameter is an adress to a variable that you want to save the value in.
> Second parameter is the number of the variable in the file (if you saved a char, then an int and then a hex then 1 = char, 2 = int, 3 = hex)
> Third parameter is the variable type, once again C - char, I - int, B - bool
> Fourth are the flags used in writing
> And the fifth one is the path to the file
#### Fast way:
```cpp
    int errorCode = 0;

    char file[] = "./subscribe.mkt";

    MKT::Reading MKTR;
    MKTRawDataComputed myRawData;

    myRawData = MKTR.readFile(file,errorCode);

    char taken;
    taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,1,MKT_VALUETYPE_CHAR,errorCode);
    free(myRawData.MKTRD);
```
> Now this is a bit more problematic. First the obvious the
> ```cpp
>     int errorCode = 0;
> 
>     char file[] = "./subscribe.mkt"
> ```
> all we can see here is the errorCode and the ```file[]``` which is just there to save the path as a char array.
> Then the
> ```cpp
>     MKT::Reading MKTR;
>     MKTRawDataComputed myRawData;
> ```
> is there to get a nonstatic member reference relative to a specific object, and the ```MKTRawDataComputed``` is there so that the script can get an array as a mallocated pointer.
> Now if you didn't understand a thing, that means you are a sane person, and it's all right because you don't need to understand it, in order to use it.
> After that the
> ```cpp
>   myRawData = MKTR.readFile(file,errorCode);
> ```
> is there to read the file into the previously meantioned struct.
> And the final part.
> ```cpp
>   char taken;
>   taken = RETURN_MKT_CHAR MKTR.dissectValue(myRawData,1,MKT_VALUETYPE_CHAR,errorCode);
> ```
> and in here we are just creating the variable and using the ```dissectValue()``` function to split the myRawData struct. ```dissectValue()``` function may be described as unmanoeuvrable, unmanageable or even a little bit fiddly. But this is how to use it
```
taken - your own variable
= - value assigning
RETURN_MKT_CHAR - a macro for value returning
MKTR. - class
dissectValue - the dissecting function
myRawData - the MKTRawDataComputed struct
1 - the which value should be read (if you saved a char, then an int and then a hex then 1 = char, 2 = int, 3 = hex)
MKT_VALUETYPE_CHAR - flags used whilst saving
errorCode - error code int
```
> Remember to free your mallocated struct with ```free(myRawData.MKTRD);``` :DDDD
## Returning Macros:

- RETURN_MKT_BOOL - return for bool

- RETURN_MKT_HEX - return for bool

- RETURN_MKT_CHAR - return for bool

- RETURN_MKT_INT - return for bool

## Flags:

### MAIN
- MKT_VALUETYPE_BOOL - used for a boolean

- MKT_VALUETYPE_HEX - used for char values smaller than 15 and bigger than 0

- MKT_VALUETYPE_CHAR - used for char values

- MKT_VALUETYPE_INT - used for int values

### OPTIONAL

- MKT_SMALLER_THAN256 - if unsigned int is smaller than 256

- MKT_SMALLER_THAN65536 - if unsigned int is smaller than 65536

- MKT_SMALLER_THAN16777216 - if unsigned int is smaller than 16777216

- MKT_SMALLER_THAN4294967296 - if unsigned int is smaller than 4294967296

- MKT_UNSIGNED - when int is unsigned

## Error Codes:
    0 - No errors
    1 - File didn't open
    2 - No data read from the file
    3 - File is not an ```.MKT``` file
    4 - Read Value type not supported (used an newer version of MKTFileManager to create a file that is being read, or file that is being read is corrupted)
    5 - Array size not provided
    6 - Hex provided bigger than 15
    7 - Tried to create a hex array
    8 - Malloc failed

# Versions
## Pre Full Release:
1. v0.0.0
    - Created a project.
2. v0.1.0
    - Added the function to write chars into ```.MKT``` files
3. v0.5.0
    - Added fully functional char saving/reading
4. v0.6.0
    - Added fully functional hex saving/reading
5. v0.7.0
    - Added fully functional bool saving/reading
5. v0.7.1
    - Added simpler functions for writing and reading
    - Upgraded readme
6. v0.8.0
    - Added fully functional int saving/reading
    - Fixed int flags