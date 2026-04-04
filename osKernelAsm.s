.section .text
.cpu cortex-m4
.syntax unified
.global currentPt
.global SysTick_Handler
.global nnOsSchedulerLaunch
.thumb
.type SysTick_Handler, function
.word SysTick_Handler

.type nnOsSchedulerLaunch, function
.word nnOsSchedulerLaunch


; Context Switcher
SysTick_Handler:                ; save r0, r1, r2, r3, r12, LR, PC, PSR
                CPSID       I
                PUSH        {R4 - R11}      ; save r4, r5, r6, r7, r8, r9, r10, r11

                ; Odczytaj aktualny wskaznik pod ktorym nalezy umiescic stack pointer
                LDR         R0, =currentPt  ; r0 points to currentPt
                LDR         R1, [R0]        ; dereference

                ; 2. zapisz aktualny stack pointer do zmiennej "tcbs[i].stackPt"
                STR         SP, [R1]

                ; odczytaj tcbs[i].stackPt.nextPt
                LDR         R1, [R1, #4]    ; r1 = currentPt -> next

                ; przypisz nextPointer jako obecny
                STR         R1, [R0]        ; currentPt = r1

                ; zaladuj SP z nextPointer / Aktualny stackPt
                LDR         SP, [R1]        ;SP = currentPt -> stackPt

                ; przywroc pozostaly kontekst
                POP         {R4 - R11}
                CPSIE       I

                ; reszte zrobi HW
                BX          LR






nnOsSchedulerLaunch:
            LDR     R0, =currentPt      ; load to R0 pointer to current task
            LDR     R2, [R0]            ; load currentPt to R2
            LDR     SP, [R2]            ; dereference of ptr end load to SP

            POP     {R4-R11}            ; pop 8 registers
            POP     {R0-R3}             ; pop 4 registers
            POP     {R12}               ; pop 1 registers
            ADD     SP, SP, #4          ; overjump 1 register (R14 - (LR))
            POP     {LR}                ; assign to LR previously assigned PC
            ADD     SP, SP, #4          ; back to defined area of stack

            CPSIE   I                   ; probably enable interrupt
            BX      LR                  






; nnOsSchedulerLaunch:
;     LDR     R0, =currentPt     ; Adres wskaźnika
;     LDR     R2, [R0]           ; R2 = currentPt (adres TCB)
;     LDR     SP, [R2]           ; SP = stackPt (ładujemy stos wątku)
    
;     POP     {R4-R11}           ; Wyciągamy R4-R11 (część software)
;     POP     {R0-R3}            ; Wyciągamy R0-R3
;     POP     {R12}              ; Wyciągamy R12
;     POP     {LR}               ; Wyciągamy LR (Link Register)
;     POP     {R1}               ; Wyciągamy PC (adres funkcji) do R1
;     ADD     SP, SP, #4         ; Omijamy xPSR (zdejmujemy go ze stosu)
    
;     CPSIE   I                  ; Włączamy przerwania
;     BX      R1                 ; SKOK DO FUNKCJI WĄTKU (task0)