# sys-ftpd ++ fs_mitm
this version updated to support INI configuration file from root of the SD Card "sys-ftpd-config.ini

INI Example:

[User]
user:=guest

[Password]
Password:=guest

============================================================================================================

This is a nintendo-switch sysmodule which runs an ftpd-server in the background (on port 5000 with no auth).

The ftpd is basically copy paste from [this](https://github.com/DavidBuchanan314/ftpd) ftpd-fork.

Put the contents of the sd_card folder in the root of your sd-card or else the sound effects won't work!

Hotkeys: To help with security while there is are no login credentials, debugging, or otherwise, you can toggle the state of the server using the (+) + (-) + (X) button combination.

Sound effects from:
https://freesound.org/people/jens.enk/sounds/434610/  
https://freesound.org/people/jens.enk/sounds/434611/  
https://freesound.org/people/rhodesmas/sounds/322897/
https://freesound.org/people/rhodesmas/sounds/322895/
