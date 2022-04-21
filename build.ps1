param (
    [switch]$DEBUG = $false,
    [switch]$ERASE = $false
)
if($DEBUG) {
$DEBUGS = "-DMKT_DEBUG"
} else {
$DEBUGS = ""  
}
if($ERASE)
{
del ./subscribe.MKT
}
g++ $DEBUGS -fpermissive ./exampleProject/MKTExample.cpp -o ./build/MKT.exe