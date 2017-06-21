# ardu_lock
Locks and unlocks KDE lockscreen with Arduino micro and MFRC522
#setup
Currently this only works only with KDE but im sure you can adapt this to work with other Desktops,
you only have to edit the lockpc function to wjatever key-combination is needed to lock your pc.

What you'll need:
Arduino micro or Leonardo, i used the micro bc its smaller.
An NFC Shield like[ this one: ](https://www.banggood.com/RC522-Chip-IC-Card-Induction-Module-RFID-Reader-p-81067.html)

At first you have to read the uid from your tag, you can do this by running the DumpInfo Example from the
library. You can also use 2 tags, just adapt VALID_UIDand VALID1_UID
Second put your password in the MY_PASSWORD String. But be careful: The micro and
 leonardo have both an english keyboard layout, so if you're using like a german 
 keyboard, this won't work with some characters.
