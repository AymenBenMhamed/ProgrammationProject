title mminiprojet2

.model small

.stack 100h


.data 
msg1 db  0dh,0ah,"SUCCES DE DEROULEMENT DE L INTERRUPTION int 20h ",'$' 
msg3 db  0dh,0ah,"verifier votre choix svp!!!!",'$'
msg4 db  0dh,0ah," programme va se fermer ",'$'
break db 10,13,"appuyer sur une touche pour sortir","$"
message2 DB 0dh,0ah," appuyer sur  (y) pour continuer (n) pour quitter :  ","$"

.code

fin_propre macro 
       
       ;restaurer l'ancien vecteur d'interruption     
       pop es     ;qui permettent des transferts d'emplacements en mémoire contigus (« en chaîne »).;Adresse de l’unique segment(es) , c’est à Adresse de segment du PSP  , 
       ;le PSP (« Program Segment Prefix ») est une zone de 256 (= 100h) octets qui
       ;contient des informations diverses au sujet du programme   
       
       pop bx
       
       mov al,20h   ;exit to operating system
       mov ah,25h   ;Cette interruption permet d'effectuer une lecture de façon absolue sur une unité de disque logique géré par le système d'exploitation.;définir CS:IP pour nouvelle interruption 
       int 21h      ;Cette interruption offre un regroupement de tous les services offert par le système d'exploitation DOS;interruption entré/sortie MS-Dos
                    
       mov dx,bx
       int 21h

       mov bx,es
       int 21h

       ;appel systeme de l'interruption 20h
      
       int 20h



endm fin_propre

routine_detournement proc

debut:

MOV AH,9

LEA DX,message2

int 21h

Mov AH,1

Int 21h

cmp al,'n'

jne continue
fin_propre


iret

continue:

cmp al,'y'

jne debut
call aff_msg



ret

routine_detournement endp

aff_msg proc 
          ;enregistrer ds cx le nombre de fois a repeter le msg 
          mov cx,5

          boucle:

          mov ah,09
          mov dx,offset msg4     ; l’Offset est un terme anglais qui désigne une adresse de manière relative
          int 21h

          loop boucle    ;loop : Décrémente CX, puis, si CX <> 0, fait un saut à MonLabel
          
          ret

aff_msg endp







success_det macro msg

        mov ah,09
        mov dx,offset msg1
        int 21h

endm




new_routine proc
        
        success_det msg
        call routine_detournement 
       
        
        ret

new_routine endp



redirect_int macro new_routine
       
       ;lecture du vecteur d'interruption        
       
       mov al,20h       ;exit to operating system
       mov ah,35h       ;charger CS:IP pour l interruption
       
       ;sauvgarder les vecteur reels de l'int 20h
       
       push bx
       push es
       
       lea dx,new_routine
       mov al,20h       ;exit to operating system
       mov ah,25h       ;définir CS:IP pour nouvelle interruption
       int 21h
       

endm 

main proc 
        
        mov ax,@data
        mov ds,ax
       
        redirect_int new_routine 
        call new_routine
         
        int 21h
        
               
mov ah,09h
mov dx,offset break
int 21h

mov ah,1
int 21h 
mov ax,4c00h  ;Il nous faut également terminer le programme par un appel de la fonction 4ch(4c00h) de l’interruption

int 21h


.exit 
main endp 
end main



;Une interruption n'est rien d'autre que l'appel d'une routine spéciale présente en mémoire
;appelée ISR (" Interrupt Service Routine ").
;  --> Les interruptions se divisent en trois catégories :

;   * les interruptions électroniques, par exemple : le clavier
;   * les interruptions du BIOS, par exemple : l'accès aux disques
;   * les interruptions du DOS, par exemple : l'accès aux systèmes de fichiers 



;l'interruption 21h est
;l'interruption du DOS par excellence


;Une faute se pro
;duit quand le processeur détecte une erreur durant le traitement d’une instruction.