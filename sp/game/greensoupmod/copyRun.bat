del "C:\greensoupmod-src\sp\game\greensoupmod\bin\client.dll"
del "C:\greensoupmod-src\sp\game\greensoupmod\bin\server.dll"
copy "C:\greensoupmod-src\sp\src\game\client\Debug_mod_sdk2013ce\client.dll" "C:\greensoupmod-src\sp\game\greensoupmod\bin\"
copy "C:\greensoupmod-src\sp\src\game\server\Debug_mod_sdk2013ce\server.dll" "C:\greensoupmod-src\sp\game\greensoupmod\bin\"
start "" "C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Singleplayer\hl2.exe" -allowdebug -sw -condebug -toconsole -game "C:\greensoupmod-src\sp\game\greensoupmod" +map gs_structure