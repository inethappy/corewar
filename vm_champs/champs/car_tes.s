.name "one"
.comment    "This city needs me"

loop: #11
        sti  r9, %:live,%1
live: live%0
        ld %0, r2
        zjmp %:loop
