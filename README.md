# ks2ePrecharge

## Basic operation

utlizes four states

    STATE_STANDBY: 
        state used when prechare is not active and SDC is open
        Airs are open
        Precharge is Open


    STATE_PRECHARGE:
        used then the prcharge circut is connected and SDC value is above minum
        Air is open
        Prechagre is closed

    STATE_ONLINE:
        used when the pregharge is complete
        Airs are closed
        Precharge is open

    STATE_ERROR:
        any error state
        airs are open
        precharge is open

## imputs
    the preharge responds only to the voltage on the SDC, Voltage on the tractive system, and Voltage on the Accumulator bus.



## Error managemnt

    this code has 5 possable errors

    None "ERR_NONE:

    Undefined "ERR_UNDEFINED"

    Prechare too fast "ERR_PRECHARGE_TOO_FAST"


    Prechare too slow "ERR_PRECHARGE_TOO_SLOW"



glocery:

SDC: shutdown circut


credit:

https://github.com/michaelruppe/FSAE/tree/master/Precharge