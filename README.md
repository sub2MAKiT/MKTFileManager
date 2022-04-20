# MKTFileManager
A Read/Write single header cpp library used to manage MKT files

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