<h2> Generate Symbol table, Literal table, Pool table & Intermediate code of a two-pass Assembler for the given source code. Display Errors</h2>


<h3> Assembly Program  given as input to program.cpp</h3>

```assembly
  		START 100
A 		DC		01		;sample program
		LOAD A
		LOAD C     		;c variable
		ADD ='5'
		ADD D
		ORIGIN A+2
		MULT ='10'
		ADD L
		LTORG 
				='5'
				='10'
L  		ADD ='5'
		ADD B 
B       DS 1
C 		EQU B
A 		DS 1
		END
  ```
  
<h2> Output Generated</h2>

<p> <h3> Pool Table File </h3> 

```cpp

 Pool Table
  1 1 2
  2 3 1
```
</p>

<p> <h3> Symbol Table File </h3> 

```cpp

 Symbol Table
1 A 100 
2 C 108 
3 D -1 
4 L 106 
5 B 108 
```
</p>

<p> <h3> MOT Table  File</h3> 

```assembly
AREG 	RG 	01 
BREG 	RG 	02 
CREG 	RG 	03 
DREG 	RG 	04 
EQ 	CC 	01 
LT 	CC 	02 
GT 	CC 	03 
LE 	CC 	04 
GE 	CC 	05 
ANY 	CC 	06 
STOP 	IS 	00 
ADD 	IS 	01 
SUB 	IS 	02 
MULT 	IS 	03 
MOVER 	IS 	04 
MOVEM 	IS 	05 
COMP 	IS 	06 
BC 	IS 	07 
DIV 	IS 	08 
READ 	IS 	09 
PRINT 	IS 	10 
LOAD 	IS 	11 
START 	AD 	01 
END 	AD 	02 
ORIGIN 	AD 	03 
EQU 	AD 	04 
LTORG 	AD 	05 
DS 	DL 	01 
DC 	DL 	02 
```
</p>

<p> <h3> Literal Table File</h3> 

```cpp


 Literal Table
1 ='5' 104
2 ='10' 105
3 ='5' 110

```

</p>

<p> <h3> Result File</h3>  

```assembly
  
	:- START 100 	LC = 0	( C,100 )
	:- A DC 01 	---- (DL,02) ---------- *LC = 100	( C,1 )	
	:- LOAD A 	---- (IS,11) ---------- *LC = 101	( S,1 )	
	:- LOAD C 	---- (IS,11) ---------- *LC = 102	( S,2 )	
	:- ADD ='5' 	---- (IS,01) ---------- *LC = 103	( L,6 )	
	:- ADD D 	---- (IS,01) ---------- *LC = 104	( S,3 )	
	:- ORIGIN A+2 	---- (AD,03) 
	:- MULT ='10' 	---- (IS,03) ---------- *LC = 102	( L,11 )	
	:- ADD L 	---- (IS,01) ---------- *LC = 103	( S,4 )	
	:- LTORG 	---- (AD,05) 
	:- ='5' 
	:- ='10' 
	:- L ADD ='5' 	---- (IS,01) ---------- *LC = 106	( L,6 )	
	:- ADD B 	---- (IS,01) ---------- *LC = 107	( S,5 )	
	:- B DS 1 	---- (DL,01) ---------- *LC = 108	( C,1 )	
	:- C EQU B 	---- (AD,04) 
	:- A DS 1  Error Case 	---- (DL,01)  ERROR: Duplicate Declaration---------- *LC = 109	( C,1 )	
	:- END 	---- (AD,02) 
	:- 
  ```
  </p>
  
<p> <h3> Error File</h3> 

  ```cpp
  
 Error File
1	Duplicate Declaration of A at location 109
2	No declaration of D
  ```
  </p>
  

