param (
    [switch]$DEBUG = $false
)
if($DEBUG) {
$DEBUGS = "-DMKT_DEBUG"
} else {
$DEBUGS = ""  
}
g++ $DEBUGS -fpermissive ./exampleProject/MKTExample.cpp -o ./build/MKT.exe