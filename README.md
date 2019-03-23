# sys-ftpd

Put the contents of the sd_card folder in the root of your sd-card or else the Module won't work!

This is a nintendo-switch sysmodule which runs an ftpd-server in the background (on port 5000 with no auth).

The ftpd is basically copy paste from [this](https://github.com/DavidBuchanan314/ftpd) ftpd-fork.

Put the contents of the sd_card folder in the root of your sd-card or else the sound effects won't work!

Hotkeys: To help with security while there is are no login credentials, debugging, or otherwise, you can toggle the state of the server using the (+) + (-) + (X) button combination.

Sound effects from:
https://freesound.org/people/jens.enk/sounds/434610/  
https://freesound.org/people/jens.enk/sounds/434611/  
https://freesound.org/people/rhodesmas/sounds/322897/
https://freesound.org/people/rhodesmas/sounds/322895/


---

Config Example (`/ftpd/config.ini`):

"""
[User]
user:=ftpd
[Password]
password:=12345

[Anonymous]
anonymous:=1
;if anonymous:=1 no login and password are needed!
;if anonymous:=0 must set user:= and Password!
"""