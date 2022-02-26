<h2>
  
[ Design suitable data structures & implement FIRST pass of a two-pass Macro processor. ](https://github.com/toaryangupta/LPCC/blob/main/Assignment%2002/program.cpp)

</h2>

<h3> Assembly Program  given as input to program.cpp</h3>

```assembly
LOAD A
STORE B
MACRO ABC
    LOAD p
    SUB q
MEND
MACRO ADD1 ARG
    LOAD X
    STORE ARG
MEND
MACRO ADD5 A1, A2, A3
    STORE A2
    ADD1 5
    ADD1 10
    LOAD A1
    LOAD A3
MEND
ABC
ADD5 D1, D2, D3
END
  ```

<h2> Output Generated</h2>

<p> <h3> Intermediate File </h3> 

```assembly
LOAD A
STORE B
ABC
ADD5 D1, D2, D3
END
```
</p>

<p> <h3> MNT Table </h3> 

```assembly
ABC 0 1
ADD1 1 4
ADD5 3 7
```
</p>

<p> <h3> MDT Table</h3> 

```assembly
LOAD p 
SUB q 
MEND
LOAD X 
STORE #1 
MEND
STORE #2 
LOAD X 
STORE 5 
LOAD X 
STORE 10 
LOAD #1 
LOAD #3 
MEND
```
</p>

<p> <h3> Actual vs Positional Parameter</h3> 

```assembly
....ADD1....
5 #1
....ADD1....
10 #1
....ABC....
....ADD5....
D1 #1
D2 #2
D3 #3
```

</p>

<p> <h3> Formal vs Positional Parameter</h3>  

```assembly
  .....ADD1.....
ARG #1
.....ADD5.....
A1 #1
A2 #2
A3 #3

  ```
  </p>

<p> <h3> Expanded Code</h3> 

  ```assembly
  LOAD A
STORE B
LOAD p 
SUB q 
STORE D2 
LOAD X 
STORE 5 
LOAD X 
STORE 10 
LOAD D1 
LOAD D3 
END

  ```
  </p>

