sample `.env`

```
P2_ROOT_DIR="/home/ashutosh/HDD/SteamLibrary/steamapps/common/Portal 2"
STEAMAPPS_DIR="/home/ashutosh/.steam/root/steamapps/sourcemods"
```

after you've installed the mod using `bash install_mod.sh`, it is recommended to:

1) keep Steam in offline mode (cloud saves are annoying)
2) add `-dev -insecure -console -novid -high -vulkan -sw -w 640 -h 480` to the launch options for your mod in Steam. also launch it once using these options to confirm everything works
3) then assign a bind to your windowmanager for launching it `steam steam://rungameid/<MOD_APPID>`

finding `MOD_APPID`

1) confirm that the mod works by launching it from Steam
2) right-click p2agent in Steam → Properties → Updates and note down the App ID (`APPID`)
3) now do `steam steam://open/console` in terminal
4) run `app_status <APPID>` and note down the gameid from that

sample output:

```
] app_status 2147483650 <-- APPID i got from the "Updates" tab
AppID 2147483650 (): 
 - release state: unknown (No License)
 - install state: uninstalled
 - user config: ""
{
 "name"  "p2agent"
 "gameid"  "15573379835664269932" <-- MOD_APPID to be used for keybinds
 "installed"  "1"
 "gamedir"  "p2agent"
 "serverbrowsername"  "p2agent"
}
```
