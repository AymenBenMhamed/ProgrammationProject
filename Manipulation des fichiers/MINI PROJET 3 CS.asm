title MINI PROJET 3
.model small
.stack 100h
.386
.data 



  msg10 db '                       Mini Projet Assembleur no 3 (Manipulation de fichiers)        ',13,10,'$'
  msg11 db '                              developpe par             ',13,10,'$'
  msg12 db '                     AYMEN BEN MHAMED && AYDA REKAYA  ',13,10,'   $'   
nom_fichier db 9,8 dup(?)
refuse DB 0ah,"Access IMPOSSIBLE$"
msg2 db "fichier inexistant!!! $"
msg3 db "fichier doit etre existe dans le repartoire contenant l excutable !!! $" 
nomfichier db "*Donner le nom de fichier � ouvrir $"
msg1 db "====>saisie 5 entier cod� en binaire: $"  
msg15 db "fichier est ouvert avec succes $"
message_entier db 10,13,'!!chaque bit d entier en binaire doit etre soit 0 ou 1 !!$'
mesg_err db 10,13,'**veuillez entrer un entier en binaire code sur 4 bits**',10,13,'$'
handle2 dw ? 
entier db 9,8 dup(?)
alaligne db 13,10,'$'
entier2 db 9,8 dup(?) 
somme db ? 
msg8 db 13,10,' Si vous voulez sortir, appuyez sur n"importe qu"elle touche du clavier$'
msg5 db "l'entier recherche existe dans la ligne$"
msg55 db "Element existe dans le fichier $"
msg6 db "*Veuillez saisir un nombre,SVP : $", 0Dh,0Ah 
msg7 db 0Dh,0Ah, "Le nombre en binaire est:       $" 
y db ? 
.code   

;===============================================
;==================================
;trois macro:couleur et affichage de l'ent�te
;==================================
;=============================================== 
attente macro 
mov ah,7
int 21h
endm


aff_msg macro chn          ;fonction pour afficher les messages
  push dx
  push ax
  lea dx,chn
  mov ah,9
  int 21h
  pop ax                                                       
  pop dx
endm  

estitique macro  a,c,b       ;fonction permet d'afficher les titres et les ent�tes
mov bx,c
xor al,al
mov ah,9
mov cx,b
int 10h 
lea dx,a
int 21h
endm 

;===================================
;ROUTINE:saisie le nom de fichier
;=================================== 
saisie_nom_fichier proc
mov al,nom_fichier[1]
add al,2
xor ah,ah
mov bx,ax

mov nom_fichier[bx],00h
mov al,2  
mov ah,3dh                ;3dh sert a ouvrir un fichier
mov dx,(offset nom_fichier)+2
int 21h

mov handle2,ax           ;handle2 :on l utilise pour acc�der au fichier(m�thodes pour acc�der aux fichiers)
jc erreur1
jmp suivant

erreur1:                 ;cas d erreur d ouverture de fichier

aff_msg msg2
aff_msg alaligne  
aff_msg msg3
JMP EXIT
suivant:

ret
saisie_nom_fichier endp


;=====================================
;MACRO:lecture de fichier
;=====================================
                
ecrirfichier macro handle2,entier
push cx
mov ah,40h                 ; 40f :Ecriture dans un fichier
mov bx,handle2
mov cx,6
mov dx,offset entier 
int 21h
pop cx
endm  

;=====================================
;MACRO:lecture de fichier
;=====================================

lecturefichier macro handle2,entier
push cx
mov ah,3fh                 ; 40f :Ecriture dans un fichier
mov bx,handle2
mov cx,6
mov dx,offset entier 
int 21h
pop cx
endm

;=================================================
;MACRO:remplissage de fichier par de code binaire
;=================================================
remplir macro handle2,entier
mov cx,0
lectur: 
aff_msg alaligne
mov ah,0ah               ; 0ah(aussi 0ch) fait appel � une saisie au clavier.
mov dx,offset entier 
int 21h  


cmp entier[1],4 ; '4:Taille effective de le chaine /ENtier sera ecrit sur 4 bits..
jne message_erreur



cmp entier[2],'0'
je passe


cmp entier[2],'1'
je condit



condit:
cmp entier[3],'0'
jne erreur

cmp entier[4],'0'
jne erreur

cmp entier[5],'0'
jl erreur

cmp entier[5],'1'
jg erreur


passe:
cmp entier[3],'0'
jl erreur

cmp entier[3],'1'
jg erreur

cmp entier[4],'0'
jl erreur

cmp entier[4],'1'
jg erreur

cmp entier[5],'0'
jl erreur 

cmp entier[5],'1'
jg erreur

ecrir:
ecrirfichier handle2,entier

jmp suivant1


erreur:                    ;err si le chiffre de chaque entier est diff de 1 ou 0
aff_msg message_entier


message_erreur:            ;err si la taille de l entier est diff de 4 bit
aff_msg mesg_err

suivant1:



endm

;========================================== 
;MACRO: saisie de l'entier cod� en decimal
;========================================== 
saisir macro somme,msg6

aff_msg msg6
faire:
mov ah,1
int 21h                            ;entier decimal entre O et 9 
mov [somme],al                     ;   car le fichier comporte que entre 0 et 9
cmp al,'9'
jg faire
cmp al,'0'
jl faire
aff_msg alaligne
endm


;=================================================
;MACRO: La trasformation en binaire                      
;=================================================
transforme macro entier,somme,entier2,msg7
mov cl,somme


                                   ;macro de tranforamtion decimale-binaire
mov si,offset entier2

mov bx,4
mov ax,cx
;sub ax,48
mov cx,4 
calcul: 
mov bl,2                            ; 2 est la base de calcul 
div bl 
push ax
add ah,48                           
mov byte ptr[si],ah                 ;byte ptr:la taille(1 octet=1 bit) de la variable dans
inc si                              ;     laquelle on a stock� le nombre
dec cx 
pop ax
cmp cx,0 
jne calcul
mov byte ptr[si],'$' 

mov bx,3
mov cx,0
mov si,offset entier
saisi:
mov al,entier2[bx]


mov byte ptr[si],al
inc si
dec bx
inc cx
cmp cx,4
jne saisi
mov byte ptr[si],'$'
aff_msg msg7 

mov ah,9
mov dx,offset entier
int 21h

endm 

;============================================================
;MACRO: comparaison de l entier saisie avec celle de fichier
;============================================================
comparaison macro entier, entier2,msg5 

mov si,offset entier           ;on compare notre entier � celle dan le fichier 
mov bx ,0
compare:
mov al,byte ptr[si]            ;byte ptr:la taille(1 octet=1 bit) de la variable dans
;mov ah,chaine2[bx]            ;     laquelle on a stock� le nombre

cmp al,entier2[bx]
jne suivant2
inc si
inc bx
cmp bx,4
je suivant11
jne compare
suivant11:
aff_msg msg5
mov al,cl
add al,48
mov dl,al
mov ah,6
int 21h
suivant2:
endm
;======================================================
;MACRO: recherche dans le fichier
;====================================================== 
recherche macro handle2,entier2,entier,y
mov ah,42h
mov al,0
mov bx,handle2
mov cx,0                                
mov dx,0
int 21h
mov cx,1
rech:
push cx 
mov ah,3fh
mov bx,handle2
mov cx,4 
mov dx,offset entier
int 21h 
pop cx 
comparaison entier,entier2 ,msg5  
push cx 
mov ah,42h
mov al,1
mov bx,handle2
mov cx,0
mov dx,2
int 21h
pop cx
inc cx
mov al,cl
cmp al,y
jne rech
aff_msg msg55
endm



;===============================================
;===============================================
;====PROGRAMME PRINCIPALE=======================
;===============================================
;===============================================

main  proc      
    
mov ax,@data
mov ds,ax



estitique  msg10,85h,77
aff_msg alaligne
estitique  msg11,6,70
aff_msg alaligne
estitique  msg12,4,70
aff_msg alaligne 


aff_msg nomfichier    
aff_msg alaligne
mov ah,0ah
lea dx,nom_fichier
int 21h 
call saisie_nom_fichier     ;appel � la routine saisie_nom_fichier
aff_msg alaligne
aff_msg msg15
aff_msg alaligne
aff_msg alaligne
aff_msg msg1
mov si,0
pour:
cmp si,5   
je saut
remplir handle2,entier,@y
inc si
jmp pour  
saut: 
aff_msg alaligne
lecturefichier handle2,entier
aff_msg alaligne
saisir somme,msg6
transforme entier,somme,entier2,msg7
aff_msg alaligne
recherche handle2,entier2,entier,y    



EXIT:
aff_msg alaligne
estitique msg8,0ch,70
attente

main endp
end main